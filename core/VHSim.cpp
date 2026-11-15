#include "VHSim.h"

#include <algorithm>
#include <cmath>
#include <cstdio>

namespace vh {

// ---------- names (Turkish UI text, UTF-8) ----------

const char* SeasonName(Season s) {
    switch (s) {
        case Season::Spring: return "İlkbahar";
        case Season::Summer: return "Yaz";
        case Season::Autumn: return "Sonbahar";
        default: return "Kış";
    }
}
const char* CropName(Crop c) {
    switch (c) {
        case Crop::Wheat: return "Buğday";
        case Crop::Potato: return "Patates";
        default: return "Safran";
    }
}
const char* BuildingName(Building b) {
    switch (b) {
        case Building::Field: return "Tarla";
        case Building::School: return "Okul";
        case Building::Barracks: return "Kışla";
        case Building::Shrine: return "İnanç Evi";
        default: return "Boş";
    }
}
const char* CardName(Card c) {
    switch (c) {
        case Card::Vine: return "Sarmaşık";
        case Card::Gossip: return "Dedikodu";
        case Card::GranaryFire: return "Ambar Yangını";
        case Card::TaxRelief: return "Vergi Affı";
        case Card::Mobilize: return "Seferberlik";
        default: return "Vaaz";
    }
}
const char* CardText(Card c) {
    switch (c) {
        case Card::Vine: return "Rakibin en değerli tarlasını sarar. Bir sonraki hasadı yok olur.";
        case Card::Gossip: return "Rakip köyde fısıltılar dolaşır. Psikolojisi 10 düşer.";
        case Card::GranaryFire: return "Rakibin ambarı tutuşur. Gıdasının dörtte biri yanar.";
        case Card::TaxRelief: return "8 altın karşılığında halkın yükü hafifler. Psikoloji +10.";
        case Card::Mobilize: return "Bu tur 3 ek savaşçı. Ordu nüfuzu +5.";
        default: return "Halk sakinleşir, ordu yumuşar. Psikoloji +6, ordu nüfuzu -10, tarikat +8.";
    }
}
const char* EndingName(Ending e) {
    switch (e) {
        case Ending::HeadmanKilled: return "Muhtar öldürüldü";
        case Ending::Famine: return "Açlık isyanı";
        case Ending::Revolt: return "Halk ayaklandı";
        case Ending::Coup: return "Ordu muhtarı devirdi";
        case Ending::Cult: return "Tarikat köyü ele geçirdi";
        default: return "";
    }
}

static std::string Fmt(const char* f, double a = 0, double b = 0, double c = 0) {
    char buf[256];
    std::snprintf(buf, sizeof buf, f, a, b, c);
    return buf;
}

// ---------- Village helpers ----------

int Village::CountBuildings(Building b) const {
    int n = 0;
    for (const Slot& s : slots) n += s.type == b;
    return n;
}
float Village::ChildCount() const {
    float n = 0;
    for (const ChildCohort& c : children) n += c.count;
    return n;
}

// ---------- Game ----------

Game::Game(uint64_t seed, Tuning t) : t_(t), rng_(seed ? seed : 0x9E3779B97F4A7C15ull) {
    v_[0].name = "Batı Köyü";
    v_[1].name = "Doğu Köyü";
    for (Village& v : v_) {
        v.hallHp = t_.hallMaxHp;
        v.slots.assign(t_.slotsPerLevel[0], Slot{});
        v.slots[0].type = Building::Field;   // every village starts with one wheat field
        v.slots[0].crop = Crop::Wheat;
        DealOffer(v);
    }
}

float Game::Rand01() {
    rng_ ^= rng_ >> 12; rng_ ^= rng_ << 25; rng_ ^= rng_ >> 27;
    return (float)((rng_ * 0x2545F4914F6CDD1Dull) >> 40) / (float)(1ull << 24);
}
int Game::RandInt(int n) { return std::min(n - 1, (int)(Rand01() * n)); }

void Game::DealOffer(Village& v) {
    v.offer.clear();
    for (int i = 0; i < 3; ++i) v.offer.push_back((Card)RandInt((int)Card::Count));
}

int Game::DarkYears() const {
    return turn_ >= t_.darkYearsStart ? (turn_ - t_.darkYearsStart) / 4 + 1 : 0;
}

int Game::Winner() const {
    bool a = v_[0].ending != Ending::None, b = v_[1].ending != Ending::None;
    if (a && !b) return 1;
    if (b && !a) return 0;
    return -1;
}

int Game::PendingCultDemand(int side) const {
    static const int kThresholds[3] = {30, 50, 70};
    int i = demandsMet_[side];
    if (i < 3 && v_[side].cult >= kThresholds[i]) return kThresholds[i];
    return 0;
}

bool Game::CanBuild(int side, int slot, Building b) const {
    const Village& v = v_[side];
    if (slot < 0 || slot >= v.SlotCount() || b == Building::Empty) return false;
    return v.gold >= t_.buildGold[(size_t)b] && v.ep >= t_.buildEp[(size_t)b];
}
bool Game::CanUpgrade(int side) const {
    const Village& v = v_[side];
    if (v.hallLevel >= 4) return false;
    return v.ep >= t_.upgradeEp[v.hallLevel - 1] && v.gold >= t_.upgradeGold[v.hallLevel - 1];
}
int Game::MaxRecruit(int side) const {
    const Village& v = v_[side];
    int civilians = (int)std::floor(v.adults) - v.soldiers;
    return std::max(0, std::min((int)(v.gold / t_.recruitGold), civilians - 2));
}

// ---------- turn resolution ----------

void Game::Resolve(const Orders& a, const Orders& b) {
    if (Over()) return;
    log_.clear();
    const Orders* o[2] = {&a, &b};

    // 1. Cards (played from the hand held at the start of the turn)
    for (int s = 0; s < 2; ++s) {
        Village& v = v_[s];
        int i = o[s]->playCard;
        if (i >= 0 && i < (int)v.hand.size()) {
            Card c = v.hand[i];
            v.hand.erase(v.hand.begin() + i);
            PlayCard(s, c);
        }
    }
    // 2. Orders: draft, builds, recruits, hall
    for (int s = 0; s < 2; ++s) ApplyOrdersPre(s, *o[s]);
    // 3. Fields and schools
    for (int s = 0; s < 2; ++s) Produce(s, *o[s]);
    // 4. Battles (simultaneous)
    std::array<int, 2> att{{std::clamp(o[0]->attackWith, 0, v_[0].soldiers), std::clamp(o[1]->attackWith, 0, v_[1].soldiers)}};
    Fight(att);
    // 5. Food, wages, mood
    for (int s = 0; s < 2; ++s) Consume(s, *o[s]);
    // 6. Cult
    for (int s = 0; s < 2; ++s) CultStep(s, *o[s]);
    // 7. Births and growth
    for (int s = 0; s < 2; ++s) Grow(s);
    // 8. Endings
    for (int s = 0; s < 2; ++s) CheckEnd(s);

    for (Village& v : v_) v.mobilized = false;
    ++turn_;
    // A new draft every 3 turns keeps cards special instead of constant.
    for (Village& v : v_) { if ((turn_ - 1) % t_.draftEvery == 0) DealOffer(v); else v.offer.clear(); }
}

void Game::PlayCard(int s, Card c) {
    Village& me = v_[s];
    Village& en = v_[1 - s];
    switch (c) {
        case Card::Vine: {
            int best = -1; float bestVal = -1;
            for (int i = 0; i < en.SlotCount(); ++i) {
                const Slot& sl = en.slots[i];
                if (sl.type != Building::Field || !sl.planted || sl.vined) continue;
                const CropSpec& cs = t_.crops[(size_t)sl.crop];
                float val = cs.yield * (cs.price + cs.food);
                if (val > bestVal) { bestVal = val; best = i; }
            }
            if (best >= 0) {
                en.slots[best].vined = true;
                Log(s, std::string("Sarmaşık, rakibin ") + CropName(en.slots[best].crop) + " tarlasını sardı.");
            } else {
                Log(s, "Sarmaşık boşa gitti: rakibin ekili tarlası yok.");
            }
            break;
        }
        case Card::Gossip: en.psych = std::max(0.f, en.psych - 10); Log(s, "Dedikodu yayıldı. Rakibin psikolojisi düştü."); break;
        case Card::GranaryFire: en.food *= 0.75f; Log(s, "Rakibin ambarı yandı."); break;
        case Card::TaxRelief:
            if (me.gold >= 8) { me.gold -= 8; me.psych = std::min(100.f, me.psych + 10); Log(s, "Vergi affı ilan edildi."); }
            else Log(s, "Vergi affı için hazinede altın yok.");
            break;
        case Card::Mobilize: me.mobilized = true; me.armyPower = std::min(100.f, me.armyPower + 5); Log(s, "Seferberlik ilan edildi."); break;
        case Card::Sermon:
            me.psych = std::min(100.f, me.psych + 6);
            me.armyPower = std::max(0.f, me.armyPower - 10);
            me.cult = std::min(100.f, me.cult + 8);
            Log(s, "Vaaz verildi. Halk sakinleşti, tarikat güçlendi.");
            break;
        default: break;
    }
}

void Game::ApplyOrdersPre(int s, const Orders& o) {
    Village& v = v_[s];
    if (o.draftPick >= 0 && o.draftPick < (int)v.offer.size() && (int)v.hand.size() < t_.handLimit)
        v.hand.push_back(v.offer[o.draftPick]);

    for (const Orders::Build& bd : o.builds) {
        if (!CanBuild(s, bd.slot, bd.type)) continue;
        v.gold -= t_.buildGold[(size_t)bd.type];
        v.ep -= t_.buildEp[(size_t)bd.type];
        Slot sl;
        sl.type = bd.type;
        sl.crop = bd.crop;
        v.slots[bd.slot] = sl;
        Log(s, std::string(BuildingName(bd.type)) + " kuruldu.");
    }

    int r = std::clamp(o.recruit, 0, MaxRecruit(s));
    if (r > 0) {
        v.gold -= r * t_.recruitGold;
        v.soldiers += r;
        Log(s, Fmt("%.0f köylü askere alındı.", r));
    }

    if (o.upgradeHall && CanUpgrade(s)) {
        v.ep -= t_.upgradeEp[v.hallLevel - 1];
        v.gold -= t_.upgradeGold[v.hallLevel - 1];
        ++v.hallLevel;
        v.slots.resize(t_.slotsPerLevel[v.hallLevel - 1]);
        v.hallHp = std::min(t_.hallMaxHp, v.hallHp + 20);
        Log(s, Fmt("Muhtarlık %.0f. seviyeye çıktı.", v.hallLevel));
    }
    v.martialLaw = o.martialLaw;
}

void Game::Produce(int s, const Orders& o) {
    Village& v = v_[s];
    const Season season = CurrentSeason();
    const float tempoMul = o.tempo == Tempo::Light ? 0.8f : o.tempo == Tempo::Heavy ? 1.3f : 1.f;
    const float dark = (float)DarkYears();

    float civilians = std::max(0.f, v.adults - v.soldiers);
    const int fields = v.CountBuildings(Building::Field);
    const int schools = v.CountBuildings(Building::School);
    const float fieldNeed = (float)(fields * t_.workersPerField);
    const float fieldLabor = fieldNeed > 0 ? std::min(1.f, civilians / fieldNeed) : 0.f;
    civilians = std::max(0.f, civilians - fieldNeed);
    const float schoolNeed = (float)(schools * t_.workersPerSchool);
    const float schoolLabor = schoolNeed > 0 ? std::min(1.f, civilians / schoolNeed) : 0.f;

    const float sell = std::clamp(o.sellPercent, 0, 100) / 100.f;

    for (Slot& sl : v.slots) {
        if (sl.type != Building::Field) continue;
        const CropSpec& cs = t_.crops[(size_t)sl.crop];
        if (!sl.planted) {
            // Seed is bought with gold, or set aside from the granary (2 food per gold) when the purse is empty.
            const bool byGold = v.gold >= cs.cost, byFood = !byGold && v.food >= cs.cost * 2.f;
            if (season != Season::Winter && (byGold || byFood)) {
                if (byGold) v.gold -= cs.cost; else v.food -= cs.cost * 2.f;
                sl.planted = true;
                sl.growLeft = (float)cs.turns;
                sl.ripeFor = 0;
            }
            continue;
        }
        if (sl.growLeft > 0) {
            sl.growLeft -= season == Season::Summer ? 1.25f : 1.f;
            if (sl.growLeft > 0) continue;
        }
        // Ripe. Rotting crops need enough hands to be brought in at once.
        if (cs.rotTurns > 0 && fieldLabor < 0.6f) {
            if (++sl.ripeFor > cs.rotTurns) {
                sl.planted = false;
                Log(s, std::string(CropName(sl.crop)) + " vaktinde toplanamadı ve çürüdü.");
            }
            continue;
        }
        sl.planted = false;
        if (sl.vined) {
            sl.vined = false;
            Log(s, std::string(CropName(sl.crop)) + " hasadı sarmaşık yüzünden kayboldu.");
            continue;
        }
        float units = cs.yield * fieldLabor * tempoMul * (season == Season::Autumn ? 1.25f : 1.f) * std::max(0.f, 1.f - 0.1f * dark);
        float sold = units * sell;
        v.gold += sold * cs.price;
        v.food += (units - sold) * cs.food;
        Log(s, std::string(CropName(sl.crop)) + Fmt(" hasadı: %.0f gıda, %.0f altın.", (units - sold) * cs.food, sold * cs.price));
    }
    v.ep += t_.epPerSchool * schools * schoolLabor * tempoMul;
}

void Game::Fight(const std::array<int, 2>& att) {
    // Snapshot strengths first so both attacks resolve at the same moment.
    std::array<float, 2> atk{}, def{};
    std::array<int, 2> defenders{};
    for (int s = 0; s < 2; ++s) {
        const Village& v = v_[s];
        const float drill = 1.f + 0.1f * v.CountBuildings(Building::Barracks);
        const float morale = 0.5f + v.psych / 100.f;
        atk[s] = att[s] * drill * morale;
        defenders[s] = v.soldiers - att[s] + (v.mobilized ? 3 : 0);
        def[s] = defenders[s] * drill * 1.2f + 5.f;   // the hall's walls are worth 5
    }
    for (int s = 0; s < 2; ++s) {
        if (att[s] <= 0) continue;
        const int e = 1 - s;
        Village& me = v_[s];
        Village& en = v_[e];
        const float total = atk[s] + def[e];
        int myLoss = (int)std::round(att[s] * std::min(0.6f, def[e] / total * 0.8f));
        int enLoss = (int)std::round(std::max(0, defenders[e]) * std::min(0.6f, atk[s] / total * 0.6f));
        myLoss = std::min(myLoss, me.soldiers);
        enLoss = std::min(enLoss, en.soldiers);
        me.soldiers -= myLoss; me.adults -= myLoss; me.psych = std::max(0.f, me.psych - 2.f * myLoss);
        en.soldiers -= enLoss; en.adults -= enLoss; en.psych = std::max(0.f, en.psych - 2.f * enLoss);
        if (atk[s] > def[e]) {
            float dmg = (atk[s] - def[e]) * 4.f;
            en.hallHp = std::max(0.f, en.hallHp - dmg);
            Log(s, Fmt("Saldırı savunmayı yardı: muhtarlık %.0f hasar aldı. Kayıplar: %.0f bize, %.0f onlara.", dmg, myLoss, enLoss));
        } else {
            Log(s, Fmt("Saldırı püskürtüldü. Kayıplar: %.0f bize, %.0f onlara.", myLoss, enLoss));
        }
    }
}

void Game::Consume(int s, const Orders& o) {
    Village& v = v_[s];
    const Season season = CurrentSeason();
    const float dark = (float)DarkYears();
    const float civilians = std::max(0.f, v.adults - v.soldiers);
    const float need = (civilians * t_.eatAdult + v.soldiers * t_.eatSoldier + v.ChildCount() * t_.eatChild) *
                       (season == Season::Winter ? 1.25f : 1.f) * (1.f + 0.1f * dark);
    v.food -= need;
    float shortage = 0.f;
    if (v.food < 0) {
        shortage = need > 0 ? std::min(1.f, -v.food / need) : 0.f;
        v.food = 0;
        Log(s, Fmt("Gıda yetmedi: halkın %%%.0f'i aç kaldı.", shortage * 100));
    }
    v.starveStreak = shortage >= 0.99f ? v.starveStreak + 1 : 0;

    v.gold -= v.soldiers * t_.wagePerSoldier;
    if (v.gold < 0) {
        v.gold = 0;
        v.armyPower += 5;
        Log(s, "Askerlerin maaşı ödenemedi. Ordu huzursuz.");
    }

    float dPsych = (o.tempo == Tempo::Light ? 3.f : o.tempo == Tempo::Heavy ? -4.f : 0.f) - 8.f * shortage;
    dPsych += 4.f * v.CountBuildings(Building::Shrine);
    if (v.gold / std::max(1.f, v.Population()) < 1.f) dPsych -= 1.f;
    if (v.martialLaw) {
        dPsych = std::max(0.f, dPsych);
        v.armyPower += 8;
    }
    v.psych = std::clamp(v.psych + dPsych, 0.f, 100.f);

    const float share = v.adults > 0 ? v.soldiers / v.adults : 0.f;
    v.armyPower = std::clamp(v.armyPower + share * 12.f - 3.f, 0.f, 100.f);
    v.lowPsychStreak = v.psych < 25.f ? v.lowPsychStreak + 1 : 0;

    // Starvation kills the weakest.
    if (shortage > 0.5f) v.adults = std::max(0.f, v.adults - v.adults * shortage * 0.05f);
    v.soldiers = std::min(v.soldiers, (int)std::floor(v.adults));
}

void Game::CultStep(int s, const Orders& o) {
    Village& v = v_[s];
    const int demand = PendingCultDemand(s);
    if (demand) {
        ++demandsMet_[s];
        if (o.acceptCultDemand) {
            v.cult = std::min(100.f, v.cult + 10);
            if (demand == 30) { v.food *= 0.8f; Log(s, "Tarikatın talebi kabul edildi: ürünün beşte biri onlara verildi."); }
            else if (demand == 50) { v.gold = std::max(0.f, v.gold - 15); Log(s, "Tarikatın talebi kabul edildi: konseyde bir koltuk ve 15 altın."); }
            else { v.adults = std::max(0.f, v.adults - 1); Log(s, "Tarikatın talebi kabul edildi: bir köylü sürgün edildi."); }
        } else {
            const float hit = demand == 30 ? 5.f : demand == 50 ? 10.f : 15.f;
            v.psych = std::max(0.f, v.psych - hit);
            const float desert = demand == 30 ? 0.f : demand == 50 ? 0.1f : 0.2f;
            const int gone = (int)std::round(v.soldiers * desert);
            v.soldiers -= gone; v.adults -= gone;
            if (demand == 70) ++v.lowPsychStreak;
            Log(s, Fmt("Tarikatın talebi reddedildi. Psikoloji -%.0f, %.0f asker firar etti.", hit, gone));
        }
    }
    const int shrines = v.CountBuildings(Building::Shrine);
    if (shrines > 0) v.cult = std::min(100.f, v.cult + 3.f * shrines);
}

void Game::Grow(int s) {
    Village& v = v_[s];
    for (ChildCohort& c : v.children) ++c.age;
    while (!v.children.empty() && v.children.front().age >= t_.childGrowTurns) {
        v.adults += v.children.front().count;
        v.children.erase(v.children.begin());
    }
    const float couples = std::floor((v.adults - v.soldiers) / 2.f);
    const float births = v.psych > 55.f ? couples * 0.06f : v.psych > 40.f ? couples * 0.02f : 0.f;
    if (births > 0) v.children.push_back({births, 0});
}

void Game::CheckEnd(int s) {
    Village& v = v_[s];
    if (v.ending != Ending::None) return;
    if (v.hallHp <= 0) v.ending = Ending::HeadmanKilled;
    else if (v.starveStreak >= 2) v.ending = Ending::Famine;
    else if (v.lowPsychStreak >= 3) v.ending = Ending::Revolt;
    else if (v.armyPower >= 100) v.ending = Ending::Coup;
    else if (v.cult >= 100) v.ending = Ending::Cult;
    else if (v.adults < 2) v.ending = Ending::Famine;
    if (v.ending != Ending::None) Log(s, std::string(v.name) + ": " + EndingName(v.ending) + ".");
}

// ---------- bot ----------

Orders Game::BotOrders(int s, int profile) const {
    const Village& v = v_[s];
    const Village& en = v_[1 - s];
    Orders o;

    // Draft: favourite card per profile, else the first offered.
    static const Card kFav[3][3] = {
        {Card::Vine, Card::TaxRelief, Card::GranaryFire},
        {Card::Mobilize, Card::GranaryFire, Card::Gossip},
        {Card::Sermon, Card::Gossip, Card::TaxRelief}};
    o.draftPick = 0;
    for (int f = 0, done = 0; f < 3 && !done; ++f)
        for (int i = 0; i < (int)v.offer.size(); ++i)
            if (v.offer[i] == kFav[profile][f]) { o.draftPick = i; done = 1; break; }

    // Card play
    for (int i = 0; i < (int)v.hand.size() && o.playCard < 0; ++i) {
        switch (v.hand[i]) {
            case Card::TaxRelief: if (v.psych < 45 && v.gold >= 12) o.playCard = i; break;
            case Card::Sermon: if (v.armyPower > 65 || v.psych < 35) o.playCard = i; break;
            case Card::Mobilize: break;   // decided with the attack below
            default: o.playCard = i; break;
        }
    }

    // Food planning: how much food does one field make per turn on average?
    const float civilians = v.adults - v.soldiers;
    const float need = civilians * t_.eatAdult + v.soldiers * t_.eatSoldier + v.ChildCount() * t_.eatChild;
    const int fields = v.CountBuildings(Building::Field);
    const float perField = 5.f;
    const float seedReserve = 6.f;   // never spend the seed money
    float gold = v.gold - seedReserve, ep = v.ep;
    int freeSlot = -1;
    for (int i = 0; i < v.SlotCount(); ++i) if (v.slots[i].type == Building::Empty) { freeSlot = i; break; }
    if (freeSlot >= 0) {
        Building want;
        Crop crop = Crop::Wheat;
        if (fields * perField < need * 1.15f) { want = Building::Field; crop = fields % 2 ? Crop::Potato : Crop::Wheat; }
        else if (v.CountBuildings(Building::School) == 0) want = Building::School;
        else if (profile == 1 && v.CountBuildings(Building::Barracks) == 0) want = Building::Barracks;
        else if (profile == 2 && v.CountBuildings(Building::Shrine) == 0) want = Building::Shrine;
        else if (profile == 0) { want = Building::Field; crop = Crop::Saffron; }
        else { want = Building::Field; crop = Crop::Potato; }
        if (gold >= t_.buildGold[(size_t)want] && ep >= t_.buildEp[(size_t)want]) {
            o.builds.push_back({freeSlot, want, crop});
            gold -= t_.buildGold[(size_t)want];
            ep -= t_.buildEp[(size_t)want];
        }
    } else if (CanUpgrade(s)) {
        o.upgradeHall = true;
    }

    // Recruiting and attacking
    const float targetShare = profile == 1 ? 0.3f : 0.15f;
    if (v.armyPower < 65 && v.soldiers < v.adults * targetShare && gold > 10 + v.soldiers * 2)
        o.recruit = std::min({MaxRecruit(s), 2, (int)(gold / t_.recruitGold)});
    const bool eager = profile == 1 || turn_ > 12;
    if (eager && v.soldiers >= en.soldiers * 1.5f + 3) {
        o.attackWith = v.soldiers - 1;
        for (int i = 0; i < (int)v.hand.size(); ++i) if (v.hand[i] == Card::Mobilize && o.playCard < 0) o.playCard = i;
    }

    // Policy
    o.tempo = v.psych < 40 ? Tempo::Light : (v.food < need * 3 && v.psych > 60) ? Tempo::Heavy : Tempo::Normal;
    o.martialLaw = v.psych < 30 && v.armyPower < 55;
    o.sellPercent = v.food > need * 8 ? 60 : v.food > need * 4 ? 40 : 15;
    o.acceptCultDemand = profile == 2 ? v.cult < 80 : v.psych < 40;
    return o;
}

}  // namespace vh
