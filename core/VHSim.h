// Village Headman: game rules core.
// Plain C++17, no engine types, so it can be unit tested outside Unreal
// and then compiled unchanged inside an Unreal module.
#pragma once

#include <array>
#include <cstdint>
#include <string>
#include <vector>

namespace vh {

// ---------- enums ----------

enum class Season : uint8_t { Spring, Summer, Autumn, Winter };
enum class Crop : uint8_t { Wheat, Potato, Saffron, Count };
enum class Building : uint8_t { Empty, Field, School, Barracks, Shrine, Count };
enum class Tempo : uint8_t { Light, Normal, Heavy };
enum class Card : uint8_t { Vine, Gossip, GranaryFire, TaxRelief, Mobilize, Sermon, Count };
enum class Ending : uint8_t { None, HeadmanKilled, Famine, Revolt, Coup, Cult };

const char* SeasonName(Season s);
const char* CropName(Crop c);
const char* BuildingName(Building b);
const char* CardName(Card c);
const char* CardText(Card c);
const char* EndingName(Ending e);

// ---------- tuning (one place for every number) ----------

struct CropSpec {
    int cost;        // gold to plant
    int turns;       // turns to grow
    float yield;     // units at harvest
    float food;      // food per unit
    float price;     // gold per unit when sold
    int rotTurns;    // turns a ripe crop waits before rotting (0 = never rots)
};

struct Tuning {
    std::array<CropSpec, (size_t)Crop::Count> crops{{
        {2, 2, 8.f, 2.f, 2.f, 0},    // Wheat: fast, cheap, low gold
        {2, 4, 12.f, 3.f, 1.f, 0},   // Potato: slow, lots of food
        {3, 2, 4.f, 0.5f, 8.f, 1},   // Saffron: cheap, fast, rich, rots and draws sabotage
    }};
    std::array<int, (size_t)Building::Count> buildGold{{0, 4, 8, 8, 6}};
    std::array<int, (size_t)Building::Count> buildEp{{0, 0, 0, 2, 2}};
    int workersPerField = 2;
    int workersPerSchool = 2;
    float epPerSchool = 3.f;
    int recruitGold = 3;           // per soldier
    float wagePerSoldier = 1.f;    // gold per turn
    float eatAdult = 1.f, eatSoldier = 1.5f, eatChild = 0.5f;
    int childGrowTurns = 8;
    std::array<int, 4> slotsPerLevel{{3, 5, 7, 9}};
    std::array<int, 4> upgradeEp{{6, 12, 20, 0}};
    std::array<int, 4> upgradeGold{{10, 20, 30, 0}};
    float hallMaxHp = 100.f;
    int handLimit = 3;
    int draftEvery = 3;            // turns between card drafts
    int darkYearsStart = 29;       // first turn of the Dark Years
};

// ---------- state ----------

struct Slot {
    Building type = Building::Empty;
    Crop crop = Crop::Wheat;
    float growLeft = 0.f;   // > 0 growing, <= 0 ripe
    bool planted = false;
    int ripeFor = 0;        // turns spent ripe and unharvested
    bool vined = false;     // sabotaged: next harvest is lost
};

struct ChildCohort { float count; int age; };

struct Village {
    std::string name;
    float gold = 30.f, food = 60.f, ep = 0.f;
    float adults = 10.f;
    int soldiers = 2;
    std::vector<ChildCohort> children;
    float psych = 60.f;       // 0..100, revolt below 25 for 3 turns
    float armyPower = 10.f;   // 0..100, coup at 100
    float cult = 0.f;         // 0..100, cult takes over at 100
    float hallHp = 100.f;     // headman dies at 0
    int hallLevel = 1;
    std::vector<Slot> slots;
    std::vector<Card> hand;
    std::vector<Card> offer;  // this turn's draft (3 cards)
    bool martialLaw = false;
    int lowPsychStreak = 0, starveStreak = 0;
    Ending ending = Ending::None;
    bool mobilized = false;   // set for one turn by the Mobilize card

    int SlotCount() const { return (int)slots.size(); }
    int CountBuildings(Building b) const;
    float ChildCount() const;
    float Population() const { return adults + ChildCount(); }
};

// What a player decides in one turn. Both sides submit, then Resolve runs.
struct Orders {
    struct Build { int slot; Building type; Crop crop; };
    std::vector<Build> builds;
    int recruit = 0;              // adults -> soldiers
    int attackWith = 0;           // soldiers sent to the enemy hall
    int sellPercent = 40;         // share of each harvest that is sold
    Tempo tempo = Tempo::Normal;
    bool martialLaw = false;
    bool upgradeHall = false;
    int draftPick = -1;           // index into Village::offer
    int playCard = -1;            // index into Village::hand (before the draft pick is added)
    bool acceptCultDemand = false;
};

// One line of the turn report shown to the player.
struct LogLine { int side; std::string text; };

class Game {
public:
    explicit Game(uint64_t seed = 1, Tuning t = Tuning{});

    // Accessors
    const Village& Side(int i) const { return v_[i]; }
    Village& SideMut(int i) { return v_[i]; }
    int Turn() const { return turn_; }
    Season CurrentSeason() const { return (Season)((turn_ - 1) % 4); }
    int Year() const { return (turn_ - 1) / 4 + 1; }
    int DarkYears() const;
    bool Over() const { return v_[0].ending != Ending::None || v_[1].ending != Ending::None; }
    int Winner() const;   // 0, 1, or -1 for both fallen / not over
    const Tuning& Tune() const { return t_; }
    const std::vector<LogLine>& LastLog() const { return log_; }
    int PendingCultDemand(int side) const;   // 0, 30, 50 or 70

    // Rough "high / medium / low" view of the enemy for hidden information (0, 1, 2).
    static int Band(float v) { return v < 33.f ? 0 : v < 66.f ? 1 : 2; }

    // Validation used by both UI and bots.
    bool CanBuild(int side, int slot, Building b) const;
    bool CanUpgrade(int side) const;
    int MaxRecruit(int side) const;

    // Advance one turn with both sides' orders.
    void Resolve(const Orders& a, const Orders& b);

    // Rule-based opponent. Profile 0 farmer, 1 militarist, 2 zealot.
    Orders BotOrders(int side, int profile) const;

private:
    Tuning t_;
    std::array<Village, 2> v_;
    int turn_ = 1;
    uint64_t rng_;
    std::vector<LogLine> log_;
    std::array<int, 2> demandsMet_{{0, 0}};   // cult thresholds already raised

    float Rand01();
    int RandInt(int n);
    void DealOffer(Village& v);
    void Log(int side, std::string s) { log_.push_back({side, std::move(s)}); }
    void ApplyOrdersPre(int side, const Orders& o);
    void PlayCard(int side, Card c);
    void Produce(int side, const Orders& o);
    void Fight(const std::array<int, 2>& attackers);
    void Consume(int side, const Orders& o);
    void CultStep(int side, const Orders& o);
    void Grow(int side);
    void CheckEnd(int side);
};

}  // namespace vh
