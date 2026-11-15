# Açık Konular: Öneriler

Bu dosyadaki her şey **öneri**. Onaylanan maddeler [02-oyun-tasarimi.md](02-oyun-tasarimi.md) dosyasına taşınacak.
Sayılar ilk denge tahminleri, oynanış testinde değişecek.

## 1. Zaman ve mevsimler

- 1 tur = 1 mevsim, 4 tur = 1 yıl.
- Tur sınırı yok. 28. turdan (7. yıl) sonra "Kara Yıllar" başlar (bkz. 13. bölüm).

| Mevsim | Etki |
|---|---|
| İlkbahar | Ekim yapılabilir |
| Yaz | Büyüme hızı +%25 |
| Sonbahar | Hasat verimi +%25, pazar fiyatları düşer (herkes satıyor) |
| Kış | Ekim yok, gıda tüketimi +%25, pazar fiyatları yükselir |

Kış, oyunun "sınav" mevsimi olur: sonbaharda stok yapmayan köy kışta çöker.

## 2. Tur akışı

1. **Olay fazı:** mevsim etkisi, rastgele olay (kuraklık, salgın, göçmen gelmesi), tarikat talebi (varsa).
2. **Kart fazı:** 3 karttan 1'i seçilir. Elde en fazla 3 kart tutulur.
3. **Emir fazı (gizli ve eş zamanlı):** köylü atamaları, ekim ve hasat, inşa ve yükseltme, pazara satış, saldırı emri, kart oynama, çalışma temposu.
4. **Çözümleme (sabit sıra):** kartlar, üretim, savaş, gıda tüketimi, metrik güncelleme, nüfus (evlilik, doğum, büyüme), bitiş kontrolü.

Sabit çözümleme sırası önemli: oyuncu "kartım savaştan önce çözülür" diye plan yapabilir. Satranç hissi buradan gelir.

## 3. Çalışma temposu

Her tur köy için bir tempo seçilir:

| Tempo | Üretim | Psikoloji (tur başına) | Huzur (tur başına) |
|---|---|---|---|
| Hafif | -%20 | +3 | +2 |
| Normal | 0 | 0 | 0 |
| Ağır | +%30 | -6 | -3 |

Kriz anında "Ağır" tempoya geçmek kurtarır, ama uzun sürerse isyan getirir.

## 4. Kişisel huzur ve psikoloji

Her köylünün iki değeri var: **Huzur** (0–100) ve **Psikoloji** (0–100).

### Tur başına etkiler

| Durum | Huzur | Psikoloji |
|---|---|---|
| İşi yeteneğine uygun | +2 | +1 |
| İşi isteğine uygun | +3 | +2 |
| İşi ikisine de uymuyor | -3 | -2 |
| Gıda payı tam | 0 | 0 |
| Gıda payı yarım | -4 | -3 |
| Gıda payı yok | -8 | -8 |
| Hane geliri düşük (altın az) | -2 | 0 |
| Evli | +2 | +1 |
| Yakını öldü (savaş, açlık) | -5 | -10 (3 tur sürer) |

### Köy değeri

Köy değeri, köylülerin ortalaması. Ama **en mutsuz %20'lik kesim 2 kat ağırlıkla** sayılır.
Anlatıdaki karşılığı: isyanı ortalama insan değil, en öfkeli kalabalık başlatır.

## 5. İsyan, darbe ve tarikat: üç güç

Köyde üç güç var ve birbirini dengeliyor:

```
          HALK
     (psikoloji)
        /    \
       /      \
   ORDU ------ TARİKAT
 (nüfuz)       (nüfuz)
```

### İsyan (halk)

- Köy psikolojisi 25'in altına düşerse **isyan sayacı** başlar.
- 3 tur üst üste 25'in altında kalırsa isyan çıkar ve oyun biter.
- Sayaç ekranda açıkça görünür. Oyuncunun tepki vermesi için zamanı olur.

### Ordu Nüfuzu (0–100)

- Askeri dal seviyesi ve asker sayısı arttıkça yükselir.
- **Sıkıyönetim** kararı: psikolojiyi her tur sabitler (düşmesini durdurur), ama huzuru -4 düşürür ve Ordu Nüfuzunu her tur +8 artırır.
- Askerlerin maaşı (altın) veya gıdası verilmezse nüfuz hızla artar (ordu huzursuz).
- **100'e ulaşırsa darbe olur, oyun biter.**
- 75'in üstünde uyarı verilir.

### Tarikat Nüfuzu (0–100)

- İnanç binası açılınca başlar.
- İnanç her tur köy psikolojisini +4 destekler.
- Tarikat nüfuzu her tur +3 artar (İnanç dalı seviyesiyle hızlanır).
- 30, 50 ve 70'te **tarikat bir talepte bulunur**. Talepleri karanlık ve giderek ağırlaşır:
  - "Tarlaların birinin ürünü bize." (ekonomik)
  - "Konseyde bir koltuk." (aza yerlerinden biri tarikat üyesine geçer)
  - "Şüpheli birini sürgün et." (bir köylü kaybedilir)
- **Kabul:** tarikat nüfuzu +10.
- **Red (onaylandı):** tarikat tek bir değeri değil, köyün tamamını sarsar. Talebin seviyesi yükseldikçe sonuç ağırlaşır:

| Talep seviyesi | Huzur | Psikoloji | Ordu düzeni | İsyan |
|---|---|---|---|---|
| 30 | -5 | -5 | Yok | Yok |
| 50 | -8 | -10 | Askerlerin %10'u firar eder (tarikat kışkırtır) | Yok |
| 70 | -12 | -15 | Askerlerin %20'si firar eder, ordu moralı 2 tur yarıya düşer | İsyan sayacı +1 |
- **100'e ulaşırsa tarikat köyü ele geçirir, oyun biter.**

### Dengenin kendisi

- Ordu tarikatı bastırabilir: **Baskın** kararı tarikat nüfuzunu -25 düşürür, ama ordu nüfuzunu +15 artırır ve psikolojiyi -5 düşürür.
- Tarikat orduyu yumuşatabilir: **Vaaz** kararı ordu nüfuzunu -15 düşürür, ama tarikat nüfuzunu +10 artırır.
- Yani psikolojiyi korumak için ya orduya ya tarikata yaslanırsın, ikisi de bir gün seni yutmaya çalışır.

## 6. Muhtarın ölümü

1. **Savaş:** ekranın üstündeki muhtarlık can barı sıfırlanırsa muhtar ölür.
2. **Suikast kartı:** nadir bir kart. Yalnızca önceki turlarda **Casus Ağı** kurulduysa oynanabilir. Başarı şansı, rakibin muhtarlık savunma seviyesine göre düşer.
3. İsyan, darbe ve tarikat da anlatıda muhtarın ölümüyle biter (farklı sonu sahneleri).

## 7. Savaş

- Saldırı emrinde kaç askerin gideceği seçilir. Giden askerler o tur başka iş yapmaz.
- **Saldırı gücü** = asker sayısı × ekipman seviyesi × moral (köy psikolojisi / 100)
- **Savunma gücü** = kalan asker × ekipman seviyesi + sur seviyesi × 5
- Saldırı gücü savunmadan büyükse, fark kadar **muhtarlık canı** düşer.
- İki taraf da güç oranına göre asker kaybeder. Ölen askerler nüfustan düşer ve yakınlarının psikolojisi düşer.
- İki saldırı aynı turda olursa iki savaş da çözülür (savunmada kalan asker sayısı önemli olur).

## 8. Pazar (iki köy aynı pazarda)

- İki köy **ortak bir pazarda** satış yapar.
- Aynı turda iki köy de aynı ürünü satarsa fiyat düşer.
- Örnek: buğday taban fiyatı 4 altın. Tek köy satarsa 4, iki köy de satarsa 2.5.
- Bu, ekonomiye de bir rakip etkileşimi getirir: "O pancar satacak, ben bu tur satmayayım."
- Mevsimsel fiyatlar (bkz. 1. bölüm).

## 9. Gıda tüketimi (tur başına)

| Kim | Gıda |
|---|---|
| Yetişkin | 2 |
| Asker | 3 |
| Çocuk | 1 |

## 10. Nüfus

- Evlilik: iki bekar yetişkin, ikisinin de huzuru 50'nin üstünde, şans %30 / tur.
- Doğum: evli çift, köy huzuru 60'ın üstünde, şans %25 / tur. Huzur 40'ın altındaysa doğum yok.
- Çocuk **8 turda** (2 yıl) yetişkin olur. Doğduğunda yetenek ve istek rastgele atanır, yetişkin olunca açılır.
- Maç kısa olduğu için yaşlılıktan ölüm yok. Ölüm sebepleri: savaş, açlık, salgın, sürgün.

## 11. Bilgi ve gizlilik

(onaylandı)

- Rakibin **kurduğu binalar ve ordusu** haritada görünür.
- Rakibin **metrikleri gizli**, sadece tahmini gösterilir: "Yüksek", "Orta", "Düşük".
- **Casus** kartı bir tur boyunca kesin değerleri ve gizli emri gösterir.

## 12. Güç kartları

Üç renk:

| Tür | Örnekler |
|---|---|
| Sabotaj (kırmızı) | Sarmaşık, Ambar Yangını, Kuyu Zehirleme, Suikast |
| Yönetim (mavi) | Casus, Vergi Affı (huzur +), Tüccar Anlaşması (bir ürüne sabit fiyat), Seferberlik |
| Karanlık (mor) | Dedikodu, Kışkırtma, Kıtlık Söylentisi, Aza Satın Alma, Kehanet (tarikat nüfuzu oyunu) |

- Bazı kartlar altın veya EP ister.
- Kartın gücü, oyuncunun doktrinine göre değişebilir (askeri doktrinde Seferberlik daha güçlü gibi).

## 13. Kazanma

(onaylandı: süre sınırı yok)

- **Tur sınırı yok. Oyun, köylerden biri bir bitiş koşuluna düşene kadar sürer.**
- Kilitlenmeyi (iki tarafın sonsuza kadar savunmada beklemesini) önlemek için öneri: **Kara Yıllar.**
  - 7. yıldan (28. tur) sonra her yıl toprak yorulur: tarım verimi -%10 (birikimli).
  - Gıda tüketimi her yıl +%10 artar.
  - Böylece maç uzadıkça baskı artar ve biri mutlaka düşer. Hikayeye de uyar: kıtlık yılları iki köyün düşmanlığını büyütür.

## 14. Yapay zeka rakibi (LLM)

- Kullanılacak model: **Jev** (bir karar / decision modeli). API detayları ve fiyatı henüz netleşmedi.
- Oyun tarafındaki arayüz modelden bağımsız olacak: "durum girer, emirler çıkar". Jev, başka bir LLM veya kural tabanlı bot aynı arayüze takılır.

- Her tur LLM'e oyunun durumu JSON olarak gönderilir (kendi metrikleri, rakip hakkında bildikleri, eli, slotlar).
- LLM, sabit bir şemada emirleri JSON olarak döner.
- Geçersiz cevap veya zaman aşımı olursa o tur **kural tabanlı bot** devreye girer. Oyun asla takılmaz.
- Maç başına yaklaşık 28 çağrı. Ucuz bir modelle maç başı maliyet çok düşük.
- Ücretsiz hak: cihaz başına 1 maç, anahtarı tutan küçük bir sunucu (proxy) üzerinden. Sunucu oran sınırı da koyar.
- Ayarlarda: kendi API anahtarı ve model seçimi.
- Ekstra fikir: LLM rakip her tur karanlık, kısa bir "muhtar mektubu" yazsın. Rakip muhtarın kişiliği hissedilir.

## 15. Teknik mimari

- **Vite + TypeScript + Three.js**.
- **Simülasyon çekirdeği ayrı ve saf TypeScript:** görüntüden bağımsız, tohumlu (seed) rastgelelikle deterministik.
  - Böylece bot, LLM ve ileride iki kişilik mod aynı çekirdeği kullanır.
  - Denge testi için binlerce maçı tarayıcı açmadan simüle edebiliriz (bot vs bot).
- **Görüntü katmanı:** Three.js, ortografik kamera, izometrik açı. Tripo AI'dan low-poly GLB modeller.
- **Arayüz:** HTML/CSS katmanı (kartlar, metrik barları, emir paneli).
- **Sunucu:** sadece LLM proxy için küçük bir serverless fonksiyon.
