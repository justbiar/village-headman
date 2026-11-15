# Village Headman · GDD (jam sürümü)

**Bu dosya tek doğru kaynaktır.** `docs/` klasöründeki eski notlarla çelişen bir şey varsa bu dosya geçerlidir.
Son güncelleme: 15 Kasım 2026, 19:50 (TR).

İşaretler: **[K]** kullanıcının kararı · **[Ö]** önerilen değer, oynarken değiştirilebilir.

---

## 0. Tek sayfada

| | |
|---|---|
| Tür | Tur bazlı köy yönetimi ve 1v1 strateji |
| Görünüm | İzometrik **2D pixel art**, tek ekran **[K]** |
| Motor | **Unreal Engine 5**, ortografik kamera **[K]** |
| Arayüz dili | **İngilizce [K]** (bu doküman Türkçe, oyundaki metinler İngilizce yazıldı) |
| Rakip | Kural tabanlı bot (jam). Jev ve iki kişilik mod sonra **[K]** |
| Maç süresi | Tur sınırı yok **[K]**. **Short match** varsayılan, hedef **12–15 dakika** (15–20 tur) **[K]**. Long match 25–40 dakika |
| Jam | Epic MegaJam 2026. Teslim **16 Kasım 04:59 TR**. Build zip'i **1 GB altı [K]** |
| Takım | **Arfdev [K]**: kullanıcı (tasarım), **maybeno2906** (Unreal yapımı) **[K]** |

**Oyunun özü:** köyü büyütmek değil, dengede tutmak. Her metriğin hem altında hem üstünde bir ölüm var. Zayıf ordu saldırı yer, güçlü ordu darbe yapar.

---

## 1. Hikaye ve ton

İki kardeş aynı köyün muhtarlığını paylaşıyordu. Yolda üzerinde tek rakam yazan bir para buldular. Biri "Six" dedi, öbürü "Nine". Tartışma bir gün sürdü, sonra bir ömür. Köy ikiye bölündü. **[K]**

- Köyler: **Six** ve **Nine**. Oyuncu Six'i yönetir, bot Nine'ı **[Ö]**.
- Para birimi: Six köyünde **six**, Nine köyünde **nine**. Arayüzde "14 six" yazar **[K]**.
- Ton: **kara mizah [K]**. Sebep gülünç, sonuçlar karanlık.
- Haritanın tam ortasında, iki köyün arasındaki taşın üstünde **o para** durur. Dekor, ama açılış ve kapanış sahnesinin merkezi **[Ö]**.

**Açılış sahnesi [Ö]** (3 kare, tıklayarak geçilir, en fazla 15 saniye):
1. "Two brothers. One village. One coin."
2. "'Six,' said one. 'Nine,' said the other."
3. "That was forty years ago. They are still arguing."

---

## 2. Oyun döngüsü

**1 tur = 1 mevsim. 4 tur = 1 yıl.** Oyuncu ve bot emirlerini aynı tur içinde verir, sonra tur birlikte çözülür. Oyuncu botun bu tur ne yaptığını tur raporunda görür.

### Tur akışı

1. **Planlama (oyuncu oynar):** inşa et, köylü ata, asker al, saldırı emri ver, kart oyna ya da seç, satış oranı ve tempo seç, düğün yap, tarikat talebi varsa cevapla.
2. **"End Turn"** düğmesine basılır. Bot da emirlerini verir.
3. **Çözümleme (sabit sıra, hep aynı):**
   1. Kartlar
   2. Emirler (inşaat başlar, askerler alınır, muhtarlık yükseltmesi başlar)
   3. İnşaatlar ilerler ve biten binalar açılır
   4. Üretim (tarla, orman, eğitim merkezi)
   5. Savaş (iki saldırı aynı anda)
   6. Satış ve depo (satış oranı, kapasite, bozulma)
   7. Tüketim ve metrikler (gıda, maaş, ısınma, psikoloji, ordu nüfuzu). Gıda yetmezse pazar eksik kısmı **bu adımda, tüketimden hemen sonra** otomatik satın alır (eksik ancak tüketimden sonra bilinir)
   8. Tarikat
   9. Nüfus (doğum, büyüme, açlıktan ölüm)
   10. Bitiş kontrolü
4. **Tur raporu:** en fazla 6 satır, önemli olandan önemsize. Örnek: "Wheat harvest: 13 food, 6 six."

Sabit sıra önemli: oyuncu "kartım savaştan önce çözülür" diye plan yapabilir. Satranç hissi buradan gelir.

---

## 2b. İlk 5 dakika **[K: önce tarla, sonra yol seçimi]**

Jüri oyunu birkaç dakika oynayacak. Oyun ilk kararları adım adım, tek satırlık ipuçlarıyla öğretir. İpuçları ekranın altında çıkar, tıklayınca kapanır. Ana menüde "Skip tutorial" seçeneği var.

| Tur | Ne olur | İpucu metni (oyunda) |
|---|---|---|
| Açılış | Para sahnesi (3 kare) | |
| 1 · Spring | Kamera köye iner. 10 köylü yürüyerek gelir. Sadece slotlar parlar | "Ten souls followed you here. Feed them first." |
| 1 | Oyuncu slota tıklar, sadece **Field** seçilebilir, ekin olarak Wheat önerilir | "Wheat grows fast and feeds many. It sells for almost nothing." |
| 1 | Orman parlar | "Idle hands can cut wood. Wood builds, warms, and sells." |
| 1 | End Turn parlar | "End the turn. Nine is doing the same." |
| 2 | Tarla biter, ekim başlar. **Yol seçimi penceresi** açılır | "How will Six be ruled?" |
| 2 | Seçimden sonra | "You can change your path. Not forever." |
| 3 · Autumn | Kış uyarısı | "Winter is coming. Nothing grows in winter, and people eat more." |
| 3–4 | İlk kart seçimi (Short match'te 3. tur) ve ilk hasat | "Every few seasons, fate offers you a card. Choose one." |
| 5 | Metrik çubukları açıklanır | "Keep the people calm, the army loyal, and the hooded ones small." |
| 6+ | İpuçları sadece ilk kez olan olaylarda çıkar (ilk sarmaşık, ilk tarikat talebi, ilk saldırı) | |

- **Botun ilk turları yumuşak** (Short match'te 4, Long match'te 6 tur): saldırmaz, sabotaj kartı oynamaz. Oyuncu sistemi öğrenirken cezalandırılmaz.
- İlk turdan sonraki her şey (ikinci tarla, odun satışı, okul) serbest. Oyun sadece ilk tarlayı ve yol seçimini zorunlu tutar.

---

## 2c. Maç türleri **[K: Short match varsayılan]**

Jüri 5–10 dakika oynayacak. Oyunun en güçlü anları (bitiş animasyonu, kardeşin sözü, Director's Cut) maç sonunda olduğu için jam sürümünde maç kısa tutulur.

| | **Short match** (varsayılan) | Long match |
|---|---|---|
| Hedef süre | 12–15 dakika (15–20 tur) | 25–40 dakika |
| Kara Yıllar başlangıcı | **9. tur** (3. yıl) | 29. tur (8. yıl) |
| Kara Yıllar etkisi (yıllık, birikimli) | **hasat -%15, tüketim +%15** | hasat -%5, tüketim +%5 |
| Botun yumuşak dönemi | **İlk 4 tur** | İlk 6 tur |
| Bot saldırganlığı | **8. turdan sonra** her kişilik, askeri oyuncununkinden 2 fazlaysa saldırır | Kişiliğe göre (bkz. 16) |
| Kart seçimi | **3. turda başlar, 2 turda bir** | 4. turda başlar, 3 turda bir |

- Ana menü: **"Short match"** büyük ve önde, "Long match" küçük ve altta.
- İpuçları (2b) Short match'te de aynı, sadece tur numaraları erkene kayar.
- **Simülasyon [Ö]:** Short match kurallarıyla rakipsiz, büyümeyen 4 tarlalı bir köy 25. turda düşüyor. Rakip baskısı ve kartlarla maçların 15–20 turda bitmesi bekleniyor. Turlar 40–50 saniye sürerse bu 12–15 dakika eder. İlk denemede maç 25 turu geçiyorsa Kara Yıllar 7. tura çekilir.

---

## 3. Ekran düzeni

Tek ekran, 16:9. **[Ö]**

```
+-----------------------------------------------------------------------+
| SIX  [######### hall 100 ]   Year 2 · Autumn   [ hall 85 ####### ] NINE |
| six 14  wood 12/40  food 30/60  EP 4     psych ▮▮▮  army ▮  cult ▯   |
+-----------------------------------------------------------------------+
|  trees trees                                         trees trees       |
|  trees [slot][slot]                         [slot][slot] trees         |
|        [ HALL ]          ( coin )            [ HALL ]                  |
|  trees [slot]                                     [slot] trees         |
|  trees trees                                         trees trees       |
+-----------------------------------------------------------------------+
| VILLAGERS (10)  farm 4 · wood 4 · teach 0 · idle 2  [Let the elders decide] |
| CARDS [Vine][Gossip][ ]     TEMPO (Light|Normal|Heavy)  SELL [40%]      |
| ATTACK [ 0 ]  RECRUIT [ 0 ]  [Martial law]                [ END TURN ] |
+-----------------------------------------------------------------------+
| Turn report: Wheat harvest: 13 food, 6 six. Nine built a Barracks.    |
+-----------------------------------------------------------------------+
```

- **Üst şerit:** iki muhtarlığın can barı, yıl ve mevsim. Kendi kaynakların ve 3 metrik çubuğu.
- **Metrik çubukları renkli bant:** yeşil, sarı, kırmızı. Sayı ancak üstüne gelince görünür. Tehlikeye giren çubuk titrer.
- **Rakibin metrikleri gizli**, sadece "High / Medium / Low" **[K]**. Rakibin binaları, inşaatları ve askerleri haritada görünür **[K]**.
- **Slota tıklamak** inşa menüsünü açar. Dolu slota tıklamak binanın bilgisini ve işçilerini gösterir.
- **Ormana tıklamak** oduncu sayısını gösterir.

---

## 4. Kaynaklar

| Kaynak | Gelir | Gider | Sınır |
|---|---|---|---|
| **six / nine** (para) | Ekin satışı, odun satışı | İnşa, tohum, asker alma, maaş, kartlar | Sınırsız |
| **Wood** (odun) **[K]** | Orman | İnşa, kışın ısınma, satış | Depo |
| **Food** (gıda) | Hasat | Nüfus, tohum (para yoksa) | Depo |
| **EP** (eğitim puanı) | İnşa tamamlamak, Eğitim Merkezi **[K]** | Gelişmiş binalar, muhtarlık | Sınırsız |

### Başlangıç **[K: sadece ilk tarlaya yetecek kadar]**

| six | wood | food | EP | Köylü | Slot |
|---|---|---|---|---|---|
| 14 | 12 | 50 | 0 | 10 (5 kadın, 5 erkek) | 3, hepsi boş |

### Satış **[Ö]**

- Her tur bir **satış oranı** seçilir (0, 20, 40, 60, 80, 100%). Hasadın o kadarı satılır, kalanı ambara girer. Varsayılan %40.
- **Odun satışı:** "Sell wood" düğmesi, **2 wood = 1 six**. Erken oyunda para kazanmanın tek güvenli yolu bu. Olmazsa ilk turlarda açlık sarmalı oluşuyor.
- **Gıda alımı:** "Buy food" düğmesi, **1 food = 1.25 six**. Ayrıca gıda tur sonunda yetmezse pazar eksik kısmı kendiliğinden **satın alır** (6 six tohum parası her zaman kesede kalır). Bu olmadan nakit ekinler (pancar, safran) anlamsızdı: zengin ama aç köyler ölüyordu.

### Vergi **[K]**

"**Collect taxes**" düğmesi. Paranın üçüncü kaynağı (satış ve odunun yanında).

| | Değer **[Ö]** |
|---|---|
| Gelir | Yetişkin başına **1 six** (askerler hariç) |
| Bedel | Köy psikolojisi **-5** |
| Sınır | **Üst üste iki tur toplanamaz** |
| Plough yolu | Vergi geliri +%20 (tüccar köy) |

- Sadece gıda eken köyün parasızlıktan darbe yemesine karşı çıkış yolu: maaşı vergiyle ödersin, bedelini psikolojiyle.
- Psikoloji zaten düşükse vergi isyanı hızlandırır. Arayüz psikoloji 35'in altındaysa uyarır: "They will not pay quietly."

### Depo **[Ö]**

| | Gıda | Odun |
|---|---|---|
| Muhtarlık (başlangıç) | 60 | 40 |
| Her Granary | +60 | +40 |

- Kapasiteyi aşan kaybolur ("The granary overflowed.").
- Her tur gıdanın **%4**'ü bozulur, köyde Granary varsa **%2**.

---

## 5. Orman **[K: köyün etrafında toplanabilir ağaçlar]**

- Her köyün çevresinde orman halkası. Slot kaplamaz.
- Stok **120 wood** (12 ağaç kümesi × 10) **[Ö]**.
- **Oduncu başına 3 wood/tur**, kışın 2. Yatkınlık verimiyle çarpılır.
- İlkbahar ve yazda orman **+4/tur** yenilenir, 120'yi geçmez.
- Stok düştükçe ağaç kümeleri kütüğe döner (her 10 wood bir küme).
- **Kışın ısınma:** her kış turunda 5 kişi başına 1 wood yanar. Odun yetmezse psikoloji **-3**.

---

## 6. Binalar ve slotlar

Her bina bir slot kaplar. **Tarlalar da slotlara dahil [K].** Maliyet ve süreler **[Ö]**.

| Bina | six | wood | EP | Süre | İşçi | Etkisi |
|---|---|---|---|---|---|---|
| **Field** | 10 | 10 | 0 | 1 tur | 2 çiftçi | Seçilen ekini yetiştirir |
| **Granary** | 8 | 15 | 0 | 1 tur | 0 | +60 gıda, +40 odun kapasite, bozulma yarıya |
| **School** (Eğitim Merkezi) | 15 | 20 | 0 | 2 tur | 2 öğretmen | Öğretmen başına 3 EP/tur × verim |
| **Barracks** | 20 | 25 | 5 | 2 tur | 0 | **Asker almayı açar** (tur başına en fazla 2), savaş gücü +%10 |
| **Shrine** | 15 | 15 | 5 | 2 tur | 1 rahip | Psikoloji +4/tur, tarikat +3/tur |

### Yola özel binalar (bkz. 6b. Yol seçimi)

| Bina | Yol | six | wood | EP | Süre | İşçi | Etkisi |
|---|---|---|---|---|---|---|---|
| **Seed Barn** | Plough | 12 | 15 | 0 | 1 tur | 0 | Tohum yarı fiyatına. Safran 1 tur daha geç çürür |
| **Fire Brigade** (itfaiye) **[K]** | Sword | 15 | 20 | 5 | 2 tur | 1 asker | Granary Fire'ın etkisi %25'ten %5'e düşer **[K: sadece savaş yolu]** |
| **Apothecary** (ilaç merkezi) **[K]** | Book | 15 | 15 | 8 | 2 tur | 1 eczacı | 2 turda bir **Remedy** üretir (verimle). Eczacı Education yatkınlığını kullanır **[K: eğitim kolunda]** |

- İnşaat sırasında slotta iskele görünür, bina çalışmaz.
- **Her bina tamamlandığında +2 EP [K].**
- Bina yıkılabilir ("Demolish"), maliyetin yarısı geri gelir.

### Muhtarlık (Hall)

| Seviye | six | wood | EP | Süre | Slot | Konsey koltuğu | Sur |
|---|---|---|---|---|---|---|---|
| 1 (başlangıç) | | | | | 3 | 1 | 5 |
| 2 | 25 | 20 | 10 | 2 | 5 | 2 | 10 |
| 3 | 40 | 40 | 25 | 3 | 7 | 3 | 15 |
| 4 | 60 | 60 | 45 | 3 | 9 | 3 | 20 |

Seviye atlayınca **+5 EP** ve can barı **+20** (en fazla 100).

**Repair hall [Ö]:** 5 six + 10 wood ile can barı +15, tur başına bir kez. Yoksa uzun maçta can barı sadece azalır.

---

## 6b. Yol seçimi **[K]**

Köye 10 kişi gelir. **Önce tarla kurulur, sonra köyün nasıl yönetileceğine karar verilir:** tarım mı, savaş mı, eğitim mi.

İlk tarla tamamlandığı turda (normalde 2. tur) bir pencere açılır: **"How will Six be ruled?"**

| Yol | Ad (oyunda) | Bonus | Açtığı özel bina | Tek cümle (oyunda) |
|---|---|---|---|---|
| **Tarım** | **The Plough** | Bütün hasatlar +%15 | Seed Barn | "Full bellies never started a war. Probably." |
| **Savaş** | **The Sword** | Barracks %30 ucuz, askerler +%10 güçlü | Fire Brigade | "Peace is a six. Strength is a nine. Or the other way." |
| **Eğitim** | **The Book** | Her bina tamamlanınca +3 EP (normalde 2), School %30 ucuz | Apothecary | "Learn enough and you'll know which way is up." |

İnanç bir yol değil. Shrine her yolda kurulabilir, çünkü inanç bir yönetim tercihi değil bir kriz cevabıdır.

### Yol değiştirmek: belli bir noktaya kadar **[K]**

| Muhtarlık seviyesi | Yol değiştirme bedeli **[Ö]** |
|---|---|
| 1 | 15 six + 10 EP |
| 2 | 30 six + 25 EP |
| 3 ve üstü | **Kilitli.** Köy artık ne olduysa o |

- Yol değişince eski yolun bonusu gider, eski yolun özel binası **durur** (yıkılmaz, ama çalışmaz). Geri dönülürse tekrar çalışır.
- Arayüzde: muhtarlığa tıklayınca "Change path" düğmesi ve bedeli. 3. seviyede düğme kilit ikonuyla gri.
- Bot da maç başında kişiliğine göre bir yol seçer (Farmer: Plough, Warlord: Sword, Zealot: Book).

---

## 7. Ekinler

### Üçlü kural **[K]**

Her ekin üç özellikten **en fazla ikisinde** iyi olabilir: **hız** (kaç turda büyür), **maliyet** (tohum parası), **getiri** (gıda ya da para). Üçünde birden iyi olan ekinin bedeli **risktir**.

| Ekin | Hız | Maliyet | Getiri | Bedeli |
|---|---|---|---|---|
| **Wheat** | ✓ hızlı | ✓ ucuz | ½ besleyici ama para etmez **[K]** | Satınca neredeyse hiç kazandırmaz |
| **Potato** | ✗ yavaş | ✓ ucuz | ✓ en çok gıda | Sabır ister, kışa stok |
| **Beet** (pancar) | ✓ hızlı | ✗ pahalı | ✓ çok para | Başta sermaye ister |
| **Saffron** | ✓ hızlı | ✓ ucuz | ✓ çok para | **Risk:** çürür, sarmaşığa ilk hedef, usta çiftçi ister |

**Wheat ile Beet'in farkı:** buğday doyurur, pancar zenginleştirir. Buğday gıda ekinidir (ucuz ve güvenli ama para getirmez). Pancar nakit ekindir (pahalı tohum, az gıda, ama satınca iyi para). Pancarın parası pazardan gıda almaya, bina dikmeye ya da asker beslemeye gider.

### Değerler **[Ö]**

| Ekin | Tohum (six) | Büyüme | Verim | Gıda/birim | Fiyat/birim | Hepsi yenirse gıda/tur | Hepsi satılırsa six/tur |
|---|---|---|---|---|---|---|---|
| **Wheat** | 2 | 2 tur | 8 | 2.5 | 0.75 | 10 | 2 |
| **Potato** | 2 | 4 tur | 16 | 3 | 1 | 12 | 3.5 |
| **Beet** | 7 | 2 tur | 6 | 1 | 4 | 3 | 8.5 |
| **Saffron** | 3 | 2 tur | 4 | 0.5 | 8 | 1 | 14.5 |

Hiçbir ekin bir başkasını her açıdan ezmiyor. Tasarım masası bunu her değişiklikte denetliyor.

- Tarlanın ekini inşa ederken seçilir. Hasattan sonra **aynı ekin kendiliğinden tekrar ekilir** (tohum parası düşer). Ekini değiştirmek için tarlaya tıklayıp "Change crop".
- **Para yoksa tohum ambardan ayrılır:** 1 six yerine 2 food. Bot testlerinde bulunan ölüm sarmalını önleyen kural.
- **Kışın ekim yapılmaz.** Büyüyen ekin büyümeye devam eder.
- **Hasat verimi** = verim × çiftçilerin ortalama verimi × tempo × mevsim × Kara Yıllar.
- **Safran:** "usta çiftçi ister". Hasat zamanı geldiğinde tarladaki 2 çiftçinin ortalama **Farming yatkınlığı 3'ün altındaysa** ya da tarlada 2 çiftçi yoksa hasat bekler. 1 turdan fazla beklerse çürür. (İlk taslaktaki "verim %60'ın altında" kuralı hiç tetiklenmiyordu, çünkü en düşük verim %70.)

---

## 8. Köylüler

### Yatkınlıklar **[K: 4 değer, rastgele]**

| Yatkınlık | İşler |
|---|---|
| **Farming** | Çiftçi, Oduncu |
| **Management** | Konsey üyesi (Elder) |
| **Military** | Asker |
| **Education** | Öğretmen, Rahip, Eczacı |

- Her biri 1–5, **4'ünün toplamı 10 [Ö]**. "Her şeyi iyi yapan" köylü çıkmaz.
- **Verim = 0.55 + 0.15 × yatkınlık [Ö]**: 1 → %70, 3 → %100, 5 → %130.

### Karakter **[K: her köylünün karakteri var]**

Her köylüye rastgele 1 karakter **[Ö]**:

| Karakter | Etkisi |
|---|---|
| **Hardworking** | Verim +%10 |
| **Lazy** | Verim -%15 |
| **Devout** | Shrine varken kişisel psikoloji +1/tur. Rahipse tarikat +1/tur ek |
| **Ambitious** | Askerse ordu nüfuzu +1/tur. Konseydeyse yönetim +1 |
| **Loyal** | Tarikat reddinde firar etmez |
| **Doubter** | "Ya para aslında öbür rakamsa?" Kişisel psikolojisi 30'un altına düşerse rakip köye kaçar |

### İşler

Çiftçi (tarla başına 2), Oduncu (sınırsız), Öğretmen (okul başına 2), Rahip (shrine başına 1), Eczacı (Apothecary başına 1), İtfaiyeci (Fire Brigade'de 1 asker), Asker (Barracks şart), Konsey (muhtarlık koltukları), Yandaş (Yes-Men's Guild'de 1, Management), Boşta.

### Kişisel psikoloji

- Her köylünün kendi psikolojisi var (başlangıç 60).
- En yüksek yatkınlığının olduğu işteyse **+1/tur**.
- Yatkınlığı 2 veya altı olan bir işteyken başka bir yatkınlığı 4 veya üstüyse **-2/tur** ("küçük insanlara büyük iş").
- Boşta olan **-1/tur**.
- **Köy psikolojisi** = kişisel psikolojilerin ortalaması, **en mutsuz %20 iki kat ağırlıklı [Ö]**.
- Köy geneline gelen etkiler (açlık, tempo, kartlar) herkese aynı uygulanır.

### Konsey ve "Let the elders decide"

- Konsey koltukları muhtarlık seviyesine bağlı (1, 2, 3).
- **Konseyin ortalama Management'ı** bütün köyün verimini etkiler: 1 → -%10, 3 → 0, 5 → +%10.
- **"Let the elders decide"** atamaları konseye yaptırır:
  - Yönetim 4–5: herkesi en uygun işe koyar.
  - Yönetim 3: çoğunu doğru, her turda 1–2 hata.
  - Yönetim 1–2: neredeyse rastgele.
- Oyuncu her zaman elle de atayabilir (F katmanı). C katmanında atama sadece bu düğme ve iş sayısı panelinden yapılır.

### Nüfus

- **Çift = evli çift.** Başlangıçta 10 kişiden **2 çift evli**, 6 kişi bekar **[Ö]**. Yeni çiftler sadece düğünle oluşur.
- Doğum: köy psikolojisi 55'in üstündeyse evli çift başına %6/tur, 40–55 arası %2, altında doğum yok. Düğünle yeni evlenen çiftin ilk yıl ihtimali ayrıca %50 (bkz. Düğün).
- C katmanından önce (köylüler sadece sayıyken) bekar sayısı basit bir sayaçtır.
- Çocuğun yatkınlıkları ve karakteri rastgele. **8 turda** yetişkin olur.
- Tüketim (tur başına): **yetişkin 1, asker 1.5, çocuk 0.5** gıda.
- Gıda yarıdan fazla eksikse her tur yetişkinlerin %5'i ölür (en düşük psikolojiliden başlayarak).

---

## 9. Metrikler ve dengeler

### Psikoloji (0–100)

| Etki | Tur başına |
|---|---|
| Tempo Light / Normal / Heavy | +3 / 0 / -4 |
| Gıda eksiği | -8 × eksik oranı |
| Her Shrine | +4 |
| Hane başına para 1'in altında | -1 |
| Kışın odun yetmezse | -3 |
| Ölen her asker | -2 (köy geneline) |
| **Doyduysa, psikoloji 50'nin altındaysa** | **+1** |
| **Bol doyduysa (ambarda en az 2 turluk gıda kaldıysa), psikoloji 50'nin altındaysa** | **+2** |
| **Düğün** (bkz. aşağısı) | **+8** |

Bütün metrikler **0 ile 100** arasındadır **[K]**.

**50 sınırı kime uygulanır:** sadece **yemek** 50'de durur. Düğün, kartlar (Tax Relief, Sermon) ve tempo 50'nin üstüne çıkarabilir. **Shrine** ve **Light tempo** ise en fazla **65**'e kadar çıkarır **[Ö]**, yoksa her tur bedava artış veren bu iki yol düğünü gereksiz kılar.

### Psikolojinin iki yarısı **[K]**

| Aralık | Ne yükseltir | Anlamı |
|---|---|---|
| **0–50** | **Yemek.** Doyan halk her tur toparlanır, ama yemek tek başına 50'yi geçirmez | Karın doyurmak hayatta tutar |
| **50–100** | **Düğün.** Yemek burada artık işe yaramaz | Mutluluk ise para ve emek ister |

Toparlanma kuralının çıkış sebebi: tasarım masasının simülasyonu, psikolojinin normal tempoda sadece düşebildiğini ve köyün er ya da geç isyanla bittiğini gösterdi.

### Düğün **[K]**

"**Hold a Wedding**" düğmesi. Tur başına en fazla bir düğün.

| | Değer **[Ö]** |
|---|---|
| Maliyet | **6 six + 10 food** (para ve yemek, **[K]**) |
| Etki | Köy psikolojisi **+8** (100'ü geçmez). İki bekar yetişkin evlenir, o çiftin ilk yıl içinde çocuk yapma ihtimali %50 |
| Şart | Köyde en az iki bekar yetişkin |

**Sık düğün verimi düşürür [K].** Son 4 turda yapılan düğün sayısına göre bütün işlerin verimi düşer (halk iş yerine eğlencede):

| Son 4 turdaki düğün | Verim |
|---|---|
| 1 | Normal |
| 2 | -%10 |
| 3 | -%20 |
| 4 | -%30 |

Tur raporunda: "The village is still celebrating. Work suffers."

### Yüksek psikolojinin ödülü **[Ö]**

Düğüne para ve yemek harcamanın karşılığı olmalı:
- Psikoloji **55'in üstünde:** doğum ihtimali artar (bkz. Nüfus).
- Psikoloji **75'in üstünde:** bütün işlerde **+%10 verim** ("The village works with a song.").
- Yüksek psikoloji, düşmanın Gossip kartına ve tarikat reddinin cezasına karşı tampon olur.

Böylece seçim şöyle olur: düğünle psikolojiyi 75'in üstüne çıkar ve +%10 verim kazan, ama düğünleri sıklaştırırsan o verimi geri kaybedersin.

**Simülasyon (karışık ekinli 4 tarlalı köy, 60 tur):**

| Düğün sıklığı | Ortalama psikoloji | 60. turda gıda |
|---|---|---|
| Hiç | 60 | 107 |
| **8 turda bir** | **85** | **69** |
| 4 turda bir | 92 | 0 (sınırda) |
| Her tur | 90, ama sonda 68'e düşüyor | 0 |

En iyi denge **yılda iki düğün civarı.** Daha sıkı yapan köy ambarını boşaltıyor ve verim cezası yüzünden psikoloji yine düşmeye başlıyor.

- **İsyan:** köy psikolojisi **3 tur üst üste 25'in altında** kalırsa. Sayaç ekranda görünür ("Unrest 2/3").

### Tempo **[Ö]**

| Tempo | Üretim | Psikoloji |
|---|---|---|
| Light | -%20 | +3/tur |
| Normal | 0 | 0 |
| Heavy | +%30 | -4/tur |

### Ordu nüfuzu (0–100)

- Her tur: **+ (asker / yetişkin) × 12 − 3**.
- Maaş ödenemezse **+5**.
- **Martial law (sıkıyönetim):** açıkken psikoloji düşmez, ordu nüfuzu **+8/tur**.
- **75'te uyarı, 100'de darbe.**

### Tarikat nüfuzu (0–100)

- Her Shrine **+3/tur** (Devout rahip +1 ek).
- **30, 50, 70'te talep** gelir (bkz. 12. bölüm).
- **100'de tarikat köyü ele geçirir.**

### Üç güç

Psikolojiyi korumanın her yolu başka bir tehlikeyi besler: sıkıyönetim orduyu, Shrine tarikatı büyütür. **Sermon** kartı orduyu tarikat pahasına yumuşatır.

---

## 10. Askerlik ve savaş

- **Asker almak:** Barracks şart. Tur başına en fazla 2. Asker başına **3 six**. Köylü işinden çıkar ve asker olur.
- **Maaş:** asker başına **1 six/tur**. Gıda 1.5/tur.
- **Eğitim süresi [Ö]:** alınan asker **1 tur** eğitilir. Alındığı tur ne saldırır ne savunur.
- **Saldırı:** "Attack" sayısı seçilir. Giden askerler o tur savunmaya katılmaz.
- **Dinlenme [Ö]:** saldıran askerler bir sonraki tur yorgundur ve normalde tekrar saldıramaz.

### Sınırları zorlamak **[K: savaşta askerler sınırlarını zorlayabilsin]**

Savaş anında kurallar esneyebilir, ama her esnetmenin bir bedeli var:

| Hamle | Ne yapar | Bedeli **[Ö]** |
|---|---|---|
| **Forced March** | Yorgun askerler dinlenmeden tekrar saldırır | Saldırı gücü **-%25**, ordu nüfuzu **+5**, köy psikolojisi **-3** |
| **Raw Recruits** | Bu tur alınan askerler eğitimsiz savaşır (saldırı ya da savunma) | Güçleri **%50**, kayıp oranları iki katı |
| **Levy** (seferberlik çağrısı) | Saldırı altındayken çiftçi ve oduncular da savunmaya katılır | Her biri %40 güçle savaşır, **o tur üretim yapmazlar**, ölen her köylü psikoloji -2 |

- Üçü de arayüzde sadece mümkün oldukları anda çıkar (Forced March saldırıdan sonraki tur, Levy sadece rakip saldırısı görüldüğünde ya da casusla öğrenildiğinde).
- Bu hamleler ordu nüfuzunu ve psikolojiyi yer, yani "kazanmak için her şeyi göze almak" darbe ve isyan riskini büyütür. İki yönlü ölüm kuralı savaşta da geçerli.
- **Levy** için teknik not: rakibin saldırısı tur çözülmeden görünmediği için Levy, oyuncu "savunmaya hazırlan" emri verdiğinde tetiklenir ve saldırı gelmezse o tur üretim boşa gider. Kumar budur.

**Formüller [Ö]:**
- Asker gücü = Military verimi × (1 + 0.1 × Barracks sayısı)
- **Saldırı** = gidenlerin gücü toplamı × (0.5 + psikoloji / 100)
- **Savunma** = kalanların gücü toplamı × 1.2 + sur (muhtarlık seviyesine göre 5–20)
- Saldırı savunmayı geçerse **muhtarlık hasarı = (saldırı − savunma) × 4**
- Kayıplar: saldıran, gidenlerin en fazla %60'ını, savunma oranına göre kaybeder. Savunan, kalanların en fazla %60'ını, saldırı oranına göre kaybeder.
- İki taraf aynı tur saldırırsa iki savaş aynı anda çözülür.
- **Muhtarlık canı 0 → muhtar ölür [K].** Muhtarın tek ölüm yolu bu (jam).

---

## 11. Kartlar

- **8 kart.** Short match'te ilk seçim **3. turda**, sonra **2 turda bir** (3, 5, 7...). Long match'te 4. turda, sonra 3 turda bir. Her seçimde 3 kart sunulur, 1'i seçilir. Elde en fazla 3 kart. Tur başına en fazla 1 kart oynanır.
- **Her kartın bir karşı hamlesi var.** Böylece kartlar şans değil, hazırlık meselesi olur.

| Kart | Tür | Bedel | Etkisi | Karşı hamle |
|---|---|---|---|---|
| **Vine** | Sabotaj | Yok | Rakibin en değerli ekili tarlasını sarar, bir sonraki hasadı yok olur | **Remedy** (ilaç) **[K]**, bkz. aşağısı |
| **Gossip** | Karanlık | Yok | Rakibin köy psikolojisi -10 | **Yes-Men's Guild** (yancılar birliği) **[K]**: dedikoduyu tamamen durdurur ve geri teper. Guild yoksa: psikoloji 75'in üstündeyse etkisi yarıya iner |
| **Spy** (casus) | Yönetim | 5 six | 2 tur boyunca rakibin kesin metriklerini, stoklarını ve **bu turki gizli emrini** (saldırı sayısı, oynayacağı kart) gösterir | **Guard Dog** (köpek) **[K]**: casusu yakalar, bkz. aşağısı |
| **Granary Fire** | Sabotaj | Yok | Rakibin gıdasının dörtte biri yanar | **Fire Brigade** (sadece Sword yolu) **[K]**: kayıp %5'e iner. Diğer yollar için: gıdayı fazla biriktirmemek, satmak |
| **Tax Relief** | Yönetim | 8 six | Kendi psikolojin +10 | Yok (kendine oynanır) |
| **Mobilize** | Yönetim | Yok | Bu tur 3 ek savaşçı (saldırı ya da savunma), ordu nüfuzu +5 | Rakip saldırıyı görünce bu tur saldırmamak. Sur seviyesi |
| **Sermon** | Karanlık | Yok | Psikoloji +6, ordu nüfuzu -10, tarikat +8 | Yok (kendine oynanır, bedeli tarikat) |
| **Upside Down** | Karanlık | 4 six | Rakibin parasını ters çevirir: **bir sonraki tur** rakibin satışları yarı fiyatına gider. Rakibe tur raporunda duyurulur: "Your coin looks... upside down." **[Ö, hikayeden]** | O tur satış oranını 0 yapmak (etki bir sonraki tura kaydırıldı, çünkü kartlar aynı tur çözülünce karşı hamle imkansızdı) |

### Remedy (ilaç) **[K]**

Sarmaşığın karşılığı. Bir eşya, ambarda sayılır (depo sınırı yok).

| Nereden | Nasıl |
|---|---|
| **Pazardan satın al** | **8 six** bir tane. Her yol satın alabilir **[K]** |
| **Apothecary** (sadece Book yolu) | 1 eczacıyla 2 turda bir 1 Remedy × verim **[K: eğitim kolunda]** |

- Sarmaşık sarılan tarla haritada yeşil sarmaşıkla görünür ve tur raporunda yazar: "Nine's vine is choking your Saffron."
- Oyuncu tarlaya tıklar, **"Cure (1 Remedy)"** der. Sarmaşık hasattan önce temizlenirse hasat kurtulur.
- Remedy yoksa hasat kaybolur.
- Böylece Book yolu sabotaja karşı ucuz bir kalkan kazanır, Sword yolu yangına karşı, Plough yolu ise kaybı kaldırabilecek kadar çok üretir. Her yolun kendi savunma dili var.

**Teknik not (Spy için):** bot emirlerini turun **başında** belirlemeli, End Turn'de değil. Yoksa casus gösterecek bir "gizli emir" bulamaz.

### Guard Dog (köpek) **[K: casusa karşı]**

Pazardan satın alınır, her yol alabilir. Maliyetler **[Ö]**:

| | Değer |
|---|---|
| Fiyat | **6 six** |
| Bakım | **0.5 food/tur** (köpek de yer) |
| En fazla | 2 köpek |
| Etkisi | Rakip Spy oynarsa: 1 köpekle **%70**, 2 köpekle **%90** ihtimalle casus yakalanır |
| Casus yakalanırsa | Kart boşa gider, rakip hiçbir şey öğrenmez. Üstüne, yakalanan casus konuşur: **sen 1 tur boyunca rakibin kesin metriklerini görürsün** |

Tur raporunda: "The dog caught Nine's spy. He talked." Haritada muhtarlığın önünde küçük bir köpek sprite'ı yatar.

### Yes-Men's Guild (yancılar birliği) **[K: dedikoduya karşı]**

Muhtarın yandaşları. Köyde "her şey yolunda" söylentisini yayarlar. Bir bina, bir slot kaplar, her yol kurabilir. Maliyetler **[Ö]**:

| | Değer |
|---|---|
| Maliyet | **10 six + 10 wood**, 1 tur |
| İşçi | 1 kişi (Management yatkınlığı) |
| Bakım | **1 six/tur** (yandaşlar ücretsiz yaranmaz) |
| Etkisi | Rakibin Gossip kartı **hiç işlemez** ve **geri teper**: rakibin kendi psikolojisi -3 |
| Bakım ödenemezse | Guild o tur çalışmaz |

Tur raporunda: "Your Yes-Men drowned out Nine's gossip. Everyone agrees with you. Loudly."

Seçim: bir slotu ve her tur parayı, belki hiç gelmeyecek bir dedikoduya mı harcarsın? Bot Gossip seven bir Zealot'sa evet.

---

## 12. Tarikat talepleri

Tarikat nüfuzu eşiğe ulaştığında bir sonraki turun başında açılır pencere çıkar. **"Accept"** ya da **"Refuse"**.

| Eşik | Talep (oyun metni) | Accept | Refuse **[K: huzursuzluk, ordu düzeni bozulur, isyan]** |
|---|---|---|---|
| 30 | "The Hooded Ones ask for a fifth of the harvest. For the coin, they say." | Gıdanın %20'si gider, tarikat +10 | Psikoloji -5 |
| 50 | "They want a seat on the council." | Bir konsey koltuğu tarikata geçer (verim çarpanı ondan hesaplanır, yönetimi 1), tarikat +10 | Psikoloji -10, askerlerin %10'u firar eder (Loyal olanlar hariç) |
| 70 | "One of yours has doubted the coin. They want him gone." | Bir köylü sürgün edilir (Doubter varsa o), tarikat +10 | Psikoloji -15, askerlerin %20'si firar eder, isyan sayacı +1 |

---

## 13. Mevsimler ve Kara Yıllar

| Mevsim | Etki |
|---|---|
| Spring | Ekim yapılabilir, orman +4 |
| Summer | Büyüme ×1.25, orman +4 |
| Autumn | Hasat +%25 |
| Winter | Ekim yok, gıda tüketimi +%25, ısınma odunu |

**Kara Yıllar [K: tur sınırı yok, biri düşene kadar]:** Short match'te 9. turdan itibaren yıllık %15 (bkz. 2c). Long match'te 29. turdan (8. yılın başı) itibaren her yıl birikimli olarak hasat **-%5**, tüketim **+%5** (ilk taslakta %10'du, simülasyonda fazla sert çıktı). Ekranda "The Lean Years" yazısı çıkar. Maçın sonsuza uzamasını engeller.

### Olaylar **[K: 3 olay, bir tur önceden duyurulur]**

Satranç hissini bozmamak için olaylar sürpriz değildir: **bir tur önceden** tur raporunda ve ekranın üstünde duyurulur, oyuncu hazırlanır. Olay **iki köyü birden** etkiler (aynı dünya), ama hazırlıklı olan daha az zarar görür.

| | Short match | Long match |
|---|---|---|
| İlk olay | 5. tur (4. turda duyurulur) | 7. tur |
| Sıklık | 4 turda bir (5, 9, 13, 17...) | 6 turda bir |
| Hangisi | Rastgele, aynı olay üst üste gelmez | Aynı |

| Olay | Duyuru (oyunda) | Etkisi **[Ö]** | Hazırlık / karşı hamle |
|---|---|---|---|
| **Drought** (kuraklık) | "The wells are low. Next season will be dry." | O tur bütün hasatlar **-%30**, orman yenilenmez | **Potato etkilenmez** (kökler derinde). Gıda almak, satışı azaltmak |
| **Plague** (salgın) | "A cough travels the road from Nine." (Nine'da: "...from Six.") | Her yetişkin %15 ihtimalle hastalanır: **2 tur çalışmaz**. Gıda eksikse hasta ölür | **Remedy** bir hastayı anında iyileştirir. Apothecary'si olan Book yolu avantajlı |
| **Wandering Merchant** (gezgin tüccar) | "A merchant's cart is on the road. He haggles badly." | O tur satış fiyatları **+%50**, gıda alış fiyatı **1 six**, Remedy **5 six**, köpek **4 six** | Satılacak stok biriktirmek. Nakit ekin eken köy kazanır |

- Hasta köylüler haritada gri ve oturur halde görünür.
- Bot da duyuruyu görür: kuraklıkta satışı keser, salgında Remedy alır, tüccarda satışı %80'e çıkarır.
- Katman: **E** (cila). Zaman kalmazsa ilk kesilecek şeylerden biri.

### Simülasyonun gösterdiği denge **[Ö]**

Tek köy, rakipsiz, 60 tur (tasarım masası):

| Köy | Sonuç |
|---|---|
| **Karışık: Wheat, Potato, Potato, Beet, %30 satış** | **60 tur ayakta**, 107 gıda, psikoloji 60, ordu nüfuzu 15 |
| Sadece gıda ekinleri (Wheat ve Potato) | Doyuyor ama parasız kalıyor. Asker maaşı ödenemiyor, **50. turda darbe** |
| Sadece Saffron ya da sadece Beet | 10–11. turda açlık. Nakit ekin tek başına köy doyurmaz |
| Fazla satış (%50) | 56. turda isyan |
| Heavy tempo sürekli | 13. turda isyan. Heavy bir kriz aracı, kalıcı politika değil |

**Sonuç:** üçlü kural oyuncuyu ekinleri karıştırmaya zorluyor. Gıda ekinleri karnı, nakit ekinler orduyu ve binaları doyuruyor. Tek bir ekine yaslanan köy ya açlıktan ya darbeden düşüyor. Bu "iki yönlü ölüm" fikrinin tarladaki karşılığı.

---

## 14. Bitişler

| Bitiş | Tetikleyici | Ekran başlığı | Muhtar animasyonu **[K: muhtar sadece bu anlarda görünür]** |
|---|---|---|---|
| Muhtar öldü | Muhtarlık canı 0 | "The Headman Fell" | Kapıdan son kez çıkar ve düşer |
| Açlık | 2 tur üst üste gıda tamamen yetmezse | "The Empty Granary" | Boş ambarın önünde tek başına oturur |
| İsyan | Psikoloji 3 tur 25'in altında | "The People Rose" | Kalabalık onu muhtarlıktan sürükleyerek çıkarır |
| Darbe | Ordu nüfuzu 100 | "The General's Hat" | General muhtarın şapkasını alıp kendi takar |
| Tarikat | Tarikat nüfuzu 100 | "The Hooded Ones" | Cübbeli figürler onu içeri alır, kapı kapanır |

Rakip düşerse kazanırsın. İkisi aynı tur düşerse berabere: "Both brothers lost. The coin stayed where it was."

**Kardeşin son sözü [Ö]** (kaybeden köyün muhtarı söyler):

| Bitiş | Six kaybederse | Nine kaybederse |
|---|---|---|
| The Headman Fell | "It was a six. Write that on the stone." | "Nine. It was always nine." |
| The Empty Granary | "We could have sold the coin." | "Nobody eats a number." |
| The People Rose | "They never cared what it said." | "Fine. Call it a seven." |
| The General's Hat | "At least the general agrees it's a six." | "The general says nine. I hate that he's right." |
| The Hooded Ones | "They say it's neither. That's worse." | "They worship the coin now. Both sides of it." |

**Kazanma ekranı:** "History will remember it as a six."

---

## 15. Director's Cut ekranı **[K]**

Maç sonunda, bitiş animasyonundan sonra gelir. Temayla bağı burada kurulur: muhtar köyün yönetmeniydi, bu onun filmi.

- Başlık: **"Director's Cut: The Tale of Six"**
- **3 sahne** (yıl ve mevsimiyle), maçın en belirleyici anları. Seçim kuralı **[Ö]**:
  1. Psikolojinin en çok düştüğü tur
  2. En çok asker ya da köylünün kaybedildiği tur
  3. Bitişi tetikleyen tur
- Her sahne kısa bir cümle. Örnek: "Year 3, Spring. The general asked for more men. You gave them."
- En altta bitişin başlığı ve kardeşin sözü. "Play again" düğmesi.

Bunun için tur çözümlemesi her turda olayları (event) kaydetmeli: hasat, kayıp, metrik değişimi, kart, talep.

---

## 16. Bot

Bot da aynı kurallarla oynar, sadece görünür bilgiyi kullanır (oyuncunun binaları ve askerleri). Maç başında 3 kişilikten biri rastgele seçilir **[Ö]**:

| Kişilik | İnşa sırası | Davranış |
|---|---|---|
| **Farmer** | Field, Field, Granary, School, Field (Saffron), Hall 2 | Az asker (%15), Vine ve Tax Relief sever |
| **Warlord** | Field, Field, School, Barracks, Hall 2 | Asker %30, rakipten 1.5 kat fazla askeri olunca saldırır, Mobilize sever |
| **Zealot** | Field, Field, School, Shrine, Hall 2 | Tarikat taleplerini kabul eder, Sermon ve Gossip sever |

Yol seçimi: Farmer → Plough, Warlord → Sword, Zealot → Book. Short match'te ilk 4 tur, Long match'te ilk 6 tur saldırmaz ve sabotaj oynamaz. Short match'te 8. turdan sonra askeri oyuncununkinden 2 fazlaysa saldırır (bkz. 2c).

Ortak kurallar:
- Tarlası sarılırsa ve Remedy'si varsa kullanır. Yoksa ve parası 20'nin üstündeyse satın alır.
- Oyuncu 2 kez Spy oynadıysa bir köpek alır. Oyuncu 2 kez Gossip oynadıysa ve boş slotu varsa Yes-Men's Guild kurar.
- Spy kartını oyuncuya saldırmadan bir tur önce oynar (Warlord).
- Atamaları her tur "en uygun işe koy" mantığıyla yapar (iyi konsey gibi).
- Gıda stoku 3 turluk tüketimin altına düşerse yeni tarla önceliklidir.
- Odun 15'in altındaysa en az 3 oduncu tutar.
- Her zaman tohum için 6 six yedek bırakır.
- Psikoloji 40'ın altında: tempo Light. 30'un altında ve ordu nüfuzu 55'in altında: sıkıyönetim.

**Not:** `core/` klasöründeki C++ çekirdek bu GDD'den önce yazıldı. Odun, köylüler ve yeni maliyetler orada yok. Formüller ve bot mantığı için referans olarak okunabilir, ama sayılar bu dokümana göre güncellenmeli.

---

## 17. Arayüz metinleri (İngilizce)

| Yer | Metin |
|---|---|
| Ana menü | "Village Headman" · "Short match" · "Long match" · "Skip tutorial" · "Quit" |
| Tur düğmesi | "End Turn" |
| İnşa menüsü | "Build" · "Field" · "Granary" · "School" · "Barracks" · "Shrine" · "Upgrade Hall" |
| Tarla | "Choose crop" · "Wheat" · "Potato" · "Beet" · "Saffron" · "Change crop" · "Demolish" |
| Köylüler | "Let the elders decide" · "Farmers" · "Woodcutters" · "Teachers" · "Priests" · "Soldiers" · "Elders" · "Idle" |
| Politika | "Tempo" · "Light" · "Normal" · "Heavy" · "Sell" · "Sell wood" · "Buy food" · "Martial law" |
| Düğün | "Hold a Wedding" · "The village is still celebrating. Work suffers." · "The village works with a song." |
| Ordu | "Recruit" · "Attack" |
| Yol | "How will Six be ruled?" · "The Plough" · "The Sword" · "The Book" · "Change path" |
| Savunma | "Buy Remedy" · "Cure (1 Remedy)" · "Buy Guard Dog" · "Yes-Men's Guild" · "Nine's vine is choking your Saffron." · "Your coin looks... upside down." · "The dog caught Nine's spy. He talked." · "Your Yes-Men drowned out Nine's gossip. Everyone agrees with you. Loudly." |
| Özel binalar | "Seed Barn" · "Fire Brigade" · "Apothecary" |
| Vergi | "Collect taxes" · "They will not pay quietly." |
| Savaş | "Forced March" · "Raw Recruits" · "Levy" · "Prepare to defend" |
| Olaylar | "Drought" · "Plague" · "Wandering Merchant" · "The wells are low. Next season will be dry." · "A cough travels the road from Nine." · "A merchant's cart is on the road. He haggles badly." |
| Uyarılar | "Unrest 2/3" · "The army grows restless." · "The Lean Years have begun." · "The granary overflowed." |
| Rakip | "High" · "Medium" · "Low" |

---

## 18. Sanat (2D pixel art) **[K]**

Referans: 9 Kings, **sadece ilham** (okunaklı küçük krallık, net siluetler). Görünüşü kopyalanmayacak, jam kuralları başkasının IP'sini yasaklıyor.

### Sprite listesi **[Ö]**

| Sprite | Boyut (px) | Not |
|---|---|---|
| Zemin karosu (çimen, toprak) | 64×32 | İzometrik elmas |
| Muhtarlık (4 seviye) | 96×96 | Six ve Nine için iki renk varyantı |
| Field (boş, ekili, olgun × 4 ekin) | 64×48 | Wheat, Potato, Beet, Saffron. Sarmaşıklı hali de |
| Granary, School, Barracks, Shrine | 64×64 | İnşaat iskelesi ortak |
| Seed Barn, Fire Brigade, Apothecary | 64×64 | Yola özel binalar |
| Remedy şişesi, sarmaşık örtüsü (tarlanın üstüne) | 16×16 / 64×48 | |
| Guard Dog (yatan ve havlayan, 2 kare) | 16×16 | Muhtarlığın önünde |
| Yes-Men's Guild binası | 64×64 | Bayraklı, alkışlayan iki figürle |
| Casus (pelerinli, gece) | 16×24 | Yakalanma anı için |
| Yol seçimi kartları (Plough, Sword, Book) | 96×128 | Açılış penceresi |
| Ağaç kümesi ve kütük | 32×48 | |
| Para (ortadaki taşın üstünde) | 32×32 | Büyük ve parlak, sahnenin odağı |
| Köylü (yürüme 2 kare) | 16×24 | İş rengine göre şapka |
| Asker | 16×24 | |
| Cübbeli tarikat üyesi | 16×24 | |
| Muhtar (animasyonlar için) | 24×32 | Sadece bitişlerde |
| Düğün (fenerler ve uzun masa, muhtarlık önünde) | 64×32 | Düğün turunda görünür |
| Kuru tarla örtüsü, hasta köylü (oturan, gri), tüccar arabası | 64×48 / 16×24 / 48×32 | Olaylar için |
| Arayüz ikonları (kaynaklar, metrikler, kartlar) | 16×16 | |
| Kart çerçevesi | 64×96 | 3 tür rengi |

**Renk:** soğuk, kasvetli bir zemin. Six için solgun kırmızı, Nine için solgun mavi bayrak rengi. Para altın sarısı ve sahnedeki en parlak şey.

### Sprite kaynağı: iki yol **[Ö]**

fal kredisi yok. Elde kalan iki yol:

**Yol 1: Tripo ile 3D model, Unreal'da pixel art'a çevirme (önerilen)**
- Jam partneri Tripo'nun 3.000 kredisi var (kod 16 Kasım'a kadar kullanılmalı). Bir model kabaca birkaç düzine kredi, yani bütün binalar ve karakterler rahat sığar.
- Tripo'dan muhtarlık, binalar, tarla, ağaç, köylü modelleri alınır (düşük poligon, "stylized" istenir).
- Unreal'da **ortografik izometrik kamera** düşük çözünürlüklü bir **Render Target**'a çizer (örneğin 480×270), bu görüntü ekrana **en yakın komşu (Nearest)** ile büyütülür. Sonuç gerçek pixel art gibi görünür, ayrıca ışık, gölge ve mevsim değişimi bedavaya gelir.
- Renk sayısını sınırlayan basit bir post-process (palet) materyali görünümü daha da toparlar.
- Artısı: tutarlı stil, dönen kamera gerekmez, Tripo bir jam sponsoru ("Tools you used"). Eksisi: Render Target kurulumu yapımcı için 30–45 dakika iş.

**Yol 2: Claude'un elle ürettiği pixel sprite'lar**
- Basit ve palet kilitli PNG sprite'lar kodla çizilir: zemin karoları, 4 ekinin tarla halleri, ağaç ve kütük, ikonlar, kart çerçeveleri, para. Bunlar hızlı ve piksel ızgarasına tam oturur.
- Binalar ve köylüler de yapılabilir ama sade kalır.
- Artısı: ücretsiz, anında, tutarlı. Eksisi: sanat kalitesi "temiz ama basit".

**Karma öneri:** zemin, tarla, ağaç, ikon ve arayüz Yol 2 ile (hemen), binalar ve karakterler Yol 1 ile (Tripo). Yapımcı A katmanına Yol 2 sprite'larıyla hemen başlayabilir.

### Unreal'da pixel art ayarları

- Dokular: **Texture Group "2D Pixels (unfiltered)"**, filtre **Nearest**, **mip map yok**, sıkıştırma **UserInterface2D**.
- Kamera ortografik, ölçek tam sayı katlarında.

---

## 19. Ses (kullanıcı hazırlayacak **[K]**)

| Ses | Ne zaman |
|---|---|
| Ana müzik (döngü) | Oyun boyunca |
| Kış müziği ya da katmanı | Kış turlarında |
| Tıklama | Arayüz |
| İnşaat bitti | Bina açılınca |
| Hasat | Hasat satırında |
| Balta | Odun |
| Savaş | Saldırı çözülürken |
| Kart çekme ve oynama | Kartlar |
| Tarikat talebi | Açılır pencere |
| Düğün (kısa, neşeli, biraz akortsuz) | Düğün turu |
| Bitiş (5 kısa melodi ya da tek ortak) | Bitiş ekranı |

Müzik OGG ya da sıkıştırılmış olmalı (1 GB sınırı için).

---

## 20. Teknik

### Katmanlar

```
Sunum (harita, arayüz, ses)  →  sadece durumu okur, olayları dinler
Köprü                       →  durum fotoğrafı, olay listesi, emir girişi
Kurallar                    →  tur çözücüsü, sistemler sabit sırayla
Rakip                       →  bot (sonra Jev, sonra ikinci oyuncu)
```

- **Kurallar ekranı bilmez, ekran kuralları bilmez.** Yeni bir özellik yeni bir olay türü ekler, eski ekranlar bozulmaz.
- **Bütün sayılar tek bir ayar tablosunda** (Unreal'da DataTable ya da tek bir Data Asset). Denge değişikliği için koda dokunulmaz.
- **Rakip arayüzü:** "Bu durumu görüyorsun, emirlerin ne?" Bot, Jev, ikinci oyuncu aynı yere takılır.

### Build ve boyut **[K: 1 GB altı]**

- Hedef zip **400 MB altı**. Starter Content yok, gereksiz eklentiler kapalı.
- Paketleme: Use Pak File, Create compressed cooked packages, Exclude editor content when cooking.
- Sadece oyun haritası paketlenir. **Development build** (jam e-postası bunu öneriyor). Development build Shipping'den biraz büyüktür, 1 GB bütçesinde sorun değil.
- Zip adı: **`Arfdev_VillageHeadman.zip`**.

---

## 21. Yapım öncelikleri

Bir katman bitmeden sonrakine geçilmez. Hangi saatte durulursa durulsun elde oynanabilir bir oyun kalır.

| Katman | İçerik | Bitince |
|---|---|---|
| **A** | Harita, slotlar, Field ve ekinler, orman ve odun, gıda, mevsimler, End Turn, basit bot, **Short match kuralları**, **yol seçimi (sadece bonuslar)**, **pazar (Sell wood, Buy food, satış oranı)**, ilk 5 dakika ipuçları | Köy kurulup yaşatılabiliyor |
| **B** | Psikoloji, **düğün**, **vergi**, tempo, ordu nüfuzu, Barracks ve asker (eğitim süresi, dinlenme), savaş, can barları, Repair hall, 5 bitiş | Kazanıp kaybedilebiliyor |
| **C** | 10 rastgele köylü, yatkınlık, karakter, "Let the elders decide", iş sayısı paneli | Liyakat teması oyunda |
| **D** | Kartlar ve karşı hamleleri (Remedy, Guard Dog, Yes-Men's Guild, Fire Brigade), yola özel binalar, Shrine ve tarikat talepleri | Rakiple etkileşim, üç güç |
| **E** | Açılış sahnesi, Director's Cut, muhtar animasyonları, ses, **3 olay**, **sınırları zorlama hamleleri** (Forced March, Raw Recruits, Levy) | Jüri için cila |
| **F** | Tek tek köylü atama, Doubter'ın kaçması | Tam liyakat |
| **G** | Pazar, olaylar, suikast, Jev, iki kişilik mod | Jam sonrası |

**Her durumda teslimden önce:** bitiş ekranı ve bir müzik (E'nin en küçük parçası).

### Saat planı **[Ö]**

| Saat (TR) | İş |
|---|---|
| 19:50–20:30 | Proje kurulumu, kamera, pixel art ayarları, boş harita |
| 20:30–22:30 | Katman A |
| 22:30–00:00 | Katman B |
| 00:00–01:00 | Katman C |
| 01:00–01:45 | Katman D |
| 01:45–02:45 | Katman E |
| 02:45–03:30 | Paketleme, başka bir bilgisayarda deneme, boyut kontrolü |
| 03:30–04:15 | Video (30–60 sn), itch sayfası |
| 04:15–04:40 | Jam'e teslim |
| 04:40–04:59 | Yedek süre |

Bir katman geç kalırsa sonraki katman kısaltılır, **paketleme ve teslim saatleri kaydırılmaz.**

---

## 22. Teslim

- **Video (30–60 sn):** ilk 5 saniyede bir bitiş anı ("The General's Hat"), sonra para ve kardeşler (3 sn), sonra hızlı oynanış: inşa, hasat, kart, saldırı, Director's Cut ekranı.
- **itch sayfası:** tek cümlelik özet ("Two brothers found a coin. One says six. One says nine. Run your half of the village without starving, revolting, or getting couped."), 3 ekran görüntüsü, kontroller, takım, kullanılan araçlar ve asset listesi.
- **Dev log (Glass Box ödülü için):** tasarımın yapay zekayla nasıl kurulduğu, bot simülasyonunun bulduğu hatalar (ölüm sarmalı, çok sık kartlar), kesilen özellikler.
- **Form:** takım adı **Arfdev**, iki üyenin adı ve Epic hesabı e-postası, oyun adı **Village Headman**, video linki.
- **Opsiyonel ama ödül için gerekli:** dev log linki (Glass Box), "Tools you used" listesi (Hyper3D ödül havuzu için). Kullanılan araçları gece boyunca bir yere not edin: Claude, Unreal Engine 5, sprite ve ses için ne kullanıldıysa.
- **Son teslim:** 15 Kasım 17:59 PST = **16 Kasım 04:59 TR**. Geç teslim kabul edilmiyor. Yükleme için zaman bırakın.
- **Yükleme sırası:** paketle, zip'i **`Arfdev_VillageHeadman.zip`** olarak adlandır, kendi itch.io hesabına yükle, sonra jam'e gönder.

---

## 23. Hâlâ eksik olanlar

| # | Eksik | Kimde | Engel mi? |
|---|---|---|---|
| 1 | **Sprite kaynağı.** fal kredisi yok. Öneri: zemin, tarla, ağaç, ikonlar Claude'dan (Yol 2), binalar ve karakterler Tripo'dan (Yol 1), bkz. 18 | Karar lazım | **Evet, A katmanı için** |
| 2 | Ses dosyaları. Seçenek: jam partneri **WeLoveIndies** ücretsiz ses ve müzik (sadece ticari olmayan kullanım, oyun satılırsa lisans gerekir) | Kullanıcı | E katmanına kadar hayır |
| 3 | ~~Takım adı~~ **Arfdev** | Karar verildi | |
| 4 | maybeno2906'nın GitHub erişimi | Sonra | Hayır |
| 5 | Yeni ekonominin denge testi (odun, köylüler, savaş, kartlar) | Yapımcı, ilk oynanabilir sürümde | Hayır, sayılar tabloda değiştirilebilir |
| 13 | Her iki üyenin Epic hesabı e-postası | Kullanıcı ve maybeno2906 | **Teslimde evet** |
| 14 | itch.io sayfası metni, dev log (Glass Box), "Tools you used" listesi, video senaryosu | Claude hazırlayabilir | Teslimde evet |
| 15 | Saat planı (19:50'de başlıyordu) yapımcının gerçek başlangıç saatine göre güncellenmeli | Yapımcı | Evet |
| 16 | `core/` C++ çekirdeği GDD'nin gerisinde (odun, köylü, vergi, olay yok) | Yapımcı GDD'yi esas alır | Hayır |
| 6 | Tarikat talep metinlerinin onayı | Kullanıcı | Hayır |
| 7 | Bitiş sözlerinin onayı | Kullanıcı | Hayır |
| 8 | Hangi köyü oyuncu yönetiyor (öneri: Six) | Kullanıcı | Hayır |
| 9 | Jev, iki kişilik mod, pazar, suikast | Jam sonrası | Hayır |
| 10 | ~~Dal seviye ağacı~~ Jam'de sadece yol seçimi, seviye ağacı M1 **[K]** | Karar verildi | |
| 11 | ~~Ek rakip etkileşimi~~ Jam'de yok (savaş, kartlar, Doubter yeterli), sınır tarlaları ve su jam sonrası **[K]** | Karar verildi | |
| 12 | ~~Platform~~ Yapımcının bilgisayarına göre Windows ya da macOS development build. Kayıt/yükleme yok **[K]** | Karar verildi | |

---

## 24. Uyarılar ve zayıf yönler

15 Kasım 20:15 itibarıyla GDD'nin eleştirel okuması. Kesin hatalar dokümanda düzeltildi (24.3), büyük kararlar kullanıcıya soruldu (24.1).

### 24.1 Kritik: jam'i tehlikeye atanlar

| # | Sorun | Neden tehlikeli | Öneri |
|---|---|---|---|
| K1 | **Sprite yok** | A katmanı zemin, tarla, ağaç ve muhtarlık olmadan başlayamaz | İlk saat sadece bu 4 sprite'a. Gerisi için düz renkli yer tutucu kutular |
| K2 | **Saat planı geride** | Plan 19:50'de kurulumla başlıyordu. Yapımcı başlamadıysa her saat bir katman yer | A ve B'ye odaklan, C ve D'yi kısalt. Paketleme saati (02:45) kaymaz |
| K3 | **Jüri muhtemelen hiçbir bitişi görmeyecek** → **Çözüldü: Short match varsayılan (bkz. 2c)** | Hedef maç 25–40 dakika, bir tur 1–2 dakika sürebilir. Jüri 5–10 dakika oynar. Oyunun en güçlü anları (bitiş animasyonu, kardeşin sözü, Director's Cut) maç sonunda | Ana menüye **"Short match"** (jam için varsayılan): Kara Yıllar 3. yılda başlar, bot 8. turdan sonra daha saldırgan. Hedef 12–15 dakika. Karar lazım |
| K4 | **Arayüz kalabalık** | Tempo, satış, odun sat, gıda al, düğün, sıkıyönetim, saldırı, asker, kartlar, ilaç, köpek, yol... İlk açışta 15+ kontrol | **Kademeli açılma:** kontrol, ilgili şey ilk kez mümkün olduğunda görünür (Recruit sadece Barracks'tan sonra, Cure sadece sarmaşıktan sonra) |
| K5 | **Denge, gerçek kurallarla hiç test edilmedi** | Tasarım masasının simülasyonunda odun, köylüler, kartlar, savaş, depo sınırı ve rakip yok. "60 tur ayakta" sonucu kısmi | Yapımcı ilk oynanabilir sürümde 2–3 tam maç oynasın, sayılar ayar tablosundan değiştirilsin |

### 24.2 Denge riskleri (oynayınca kontrol edilmeli)

| # | Risk | Belirti | İlk ayar |
|---|---|---|---|
| D1 | Depo sınırı simülasyonda yok | 4 tarlalı köy 107 gıda biriktiriyordu, gerçek oyunda 60'ta taşar | Granary erken lazım olabilir. Taşma çok sinir bozucuysa başlangıç kapasitesi 80 |
| D2 | Savaş formülleri hiç denenmedi | Tek saldırıda muhtar ölebilir ya da hiç hasar çıkmayabilir | Hasar çarpanı 4 ile başla, ilk maçta muhtarlık 3 saldırıdan önce düşüyorsa 3'e indir |
| D3 | Shrine ve Light tempo bedava psikoloji | Düğünü gereksiz kılabilirdi | 65 tavanı eklendi (24.3). Yine de baskınsa Shrine +4'ü +3'e indir |
| D4 | Bot zayıf kalabilir | Kural tabanlı bot, oyuncu bir açık bulunca hep aynı şekilde kaybeder | 3 kişilik rastgele seçiliyor. Jam için yeterli |
| D5 | Kartopu | Önde olan köy hızla büyür | Tarikat ve darbe riski büyük köyü zaten frenliyor. Ek önlem jam sonrası |
| D6 | Sword yolu ile Fire Brigade asimetrisi | Diğer yollar yangına karşı tamamen savunmasız | Bilinçli bir seçim **[K]**, ama oyunda hissedilirse Granary yangın kaybını %20'ye indirebilir |

### 24.3 Bu okumada düzeltilen hatalar

| Hata | Düzeltme |
|---|---|
| "Pazar eksik gıdayı kendiliğinden **satar**" (yanlış fiil) | **Satın alır** |
| Safran kuralı hiç tetiklenmiyordu (verim %60 altı, ama en düşük verim %70) | Çiftçilerin ortalama Farming yatkınlığı 3'ün altındaysa ya da 2 çiftçi yoksa |
| Upside Down'un karşı hamlesi imkansızdı (kartlar aynı tur çözülüyor) | Etki bir sonraki tura kaydırıldı ve rakibe duyuruluyor |
| "Çift" tanımsızdı (doğum çift başına, düğün bekarları evlendiriyor) | Başlangıçta 2 evli çift ve 6 bekar. Yeni çift sadece düğünle |
| İlk kart turu çelişkiliydi | İlk seçim 4. tur, sonra 3 turda bir |
| "Sadece düğün 50'yi geçirir" ile Shrine, Light tempo ve kartlar çelişiyordu | Sadece yemek 50'de durur. Shrine ve Light tempo 65'e kadar, düğün ve kartlar 100'e kadar |
| Muhtarlık canı hiç iyileşmiyordu | "Repair hall": 5 six + 10 wood ile +15 |
| Pazar, düğün, köpek ve Guild hiçbir katmana atanmamıştı | Pazar A'ya, düğün B'ye, köpek ve Guild D'ye |

### 24.4 Yapay zeka sprite araçları için uyarılar

Kullanıcının bulduğu araçlar (15 Kasım):

| Araç | Ne | Gerekenler | Not |
|---|---|---|---|
| [scenario-labs/skills](https://github.com/scenario-labs/skills) | Claude Code'a görsel, ses, 3D üretimi öğreten skill'ler (MIT). `scenario-game-assets`, `scenario-sprite-animation` gibi oyun skill'leri var | Scenario MCP sunucusu, Scenario hesabı ve kredisi (ücretli olabilir) | Ayrıca **Unreal skill'leri** var (Claude'un Unreal'ı sürmesi), ama kendi README'leri "Unreal içinde hiç çalıştırılmadı" diyor. Bu gece güvenilecek bir şey değil |
| [gpt-image-2d-assets](https://github.com/Harrison0223-svg/gpt-image-2d-assets) | Codex için 2D asset skill'i (MIT): stil seçimi, sprite sayfası, GIF önizleme | Codex ve GPT-image erişimi, Python ve Pillow | Küçük ve yeni bir proje. Kendi README'si pixel stilinin "pixel-perfect olarak kontrol edilmediğini" söylüyor |

**Hangisi seçilirse seçilsin:**
1. Yapay zeka "pixel art" çıktısı gerçek piksel ızgarasına oturmaz. Her sprite oyuna girmeden önce: büyük üret, **en yakın komşu** ile hedef boyuta küçült (64×64 gibi), renk sayısını sabit bir palete indir. Yoksa Unreal'daki "2D Pixels" ayarı bile bulanık görünümü kurtarmaz.
2. **Tutarlılık:** her sprite'ı aynı stil tarifi ve aynı referans görselle üret. Yoksa her bina başka bir oyundan gelmiş gibi durur.
3. Üçüncü parti bir skill kurmadan önce içindeki script'lere bakılmalı (kurulum kod çalıştırır).
4. Kullanılan araç teslimde **"Tools you used"** listesine yazılır. GPT-image kullanılırsa jam'in **OpenAI ödülleri** için de aday olunur (formda OpenAI sorusu var).
