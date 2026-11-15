# Tam Analiz: Güçlü Yanlar, Riskler, Eksikler

Tarih: 15 Kasım 2026. Bu dosya tasarımın baştan sona eleştirel bir okumasıdır.

## 1. Unity ile jam'de şansı

- Epic MegaJam'de **Unity ile katılmak mümkün değil.** Kural açık: sadece Unreal Engine veya UEFN. Unity ile yapılan oyun ne kadar iyi olursa olsun değerlendirmeye alınmaz.
- Yapay zeka araçları serbest, ama motorun yerine geçmiyor. "Sadece yapay zeka araçları" diye bir yol yok: yapay zeka, Unreal'ın üzerinde yardımcı olarak kullanılıyor.
- Unity'nin serbest olduğu başka bir jam'de (örneğin genel itch.io jam'leri) fikrin şansı aşağıdaki değerlendirmeyle aynıdır.

## 2. Fikrin jüri kriterlerine göre puanı (tahmini, 1–5)

| Kriter | Puan | Neden |
|---|---|---|
| Ambition ve yenilik | 4–5 | Üç güç dengesi (halk, ordu, tarikat), iki yönlü ölüm, liyakat sistemi özgün |
| Tema | 2–3 | "Director's Cut" ile bağ zayıf, anlatıyla kurulabilir |
| Eğlence | 2–4 | Denge oturursa yüksek, oturmazsa sayı yönetimi gibi hissedilir |
| Oynanış | 3–4 | Derin, ama ilk dakikalar karmaşık |
| Görsel | 2–3 | Yönetim oyunu ağırlıklı menü; izometrik köy sahnesi kurtarabilir |
| Level design / ilerleme | 2–3 | Tek harita, ilerleme dalların açılmasıyla sınırlı |
| Ses | 1–3 | Henüz hiç planlanmadı |

Sonuç: Tasarım olarak ilk 3 seviyesinde bir fikir. Ama 4 günlük bir jam'de bu derinliği hem çalışır hem de görsel olarak etkileyici hale getirmek çok zor. Asıl şansı, sakin geliştirilmiş bir oyun olarak.

## 3. Güçlü yanlar

1. **Her metriğin iki yönlü tehlikesi.** Zayıf ordu saldırı yer, güçlü ordu darbe yapar. Bu, "hep daha fazla" stratejisini kırar ve satranç hissi verir.
2. **Halk, ordu ve tarikat üçgeni.** Psikolojiyi korumanın her yolu başka bir canavarı besler.
3. **Liyakat teması mekaniğe dönüşüyor.** "Küçük insanlara büyük iş" sadece hikaye değil, azaların verim çarpanı olarak oynanıyor.
4. **Mahsul üçgeni** (hız, maliyet, getiri) basit ama derin bir karar alanı.
5. **Ciddi ve karanlık ton** türde az bulunan bir şey. Tarikat talepleri, sürgün, kıtlık yılları güçlü anlatı anları üretir.
6. **Yapay zeka rakibinin kişiliği** (muhtar mektupları) oyunu hatırlanır kılabilir.

## 4. Riskler ve zayıf yanlar

### 4.1 Kapsam
Sistem sayısı çok fazla: 4 kaynak, 5 metrik, 2 nüfuz, kişisel değerler, nüfus, azalar, mahsuller, işleme, depo, kartlar, savaş, olaylar, yapay zeka. Hepsini aynı anda yapmak yerine katmanlı ilerlemek gerekiyor (bkz. 6. bölüm).

### 4.2 Bilişsel yük
Oyuncu aynı anda 10'dan fazla sayı izliyor. Çözüm önerileri:
- Ekranda sayı yerine **tehlike göstergesi**: her metrik için yeşil, sarı, kırmızı bant.
- Sadece tehlikeye giren metrikler büyüsün ve titresin.
- Tur sonunda "Bu tur ne değişti" özeti (en fazla 3 satır).

### 4.3 Paralel solitaire
İki köy yan yana kendi işini yapıp birbirine hiç dokunmayabilir. Rakip etkileşim kaynakları şimdilik: savaş, kartlar, ortak pazar. Ek öneriler:
- **Sınır tarlaları:** haritanın ortasında iki köyün de ekebileceği ama korunmasız tarlalar.
- **Göç:** mutsuz köylüler rakip köye kaçabilir (huzuru yüksek olan köy nüfus kazanır).
- **Ortak su kaynağı:** biri fazla kullanırsa diğerinin verimi düşer.

### 4.4 Dominant strateji riski
- Safran her tur ekilip hiç sabote edilmezse en iyi seçenek olur. Sabotaj kartları yeterince sık gelmeli veya safranın başka bir bedeli olmalı (toprağı yorar).
- Tamamen savunmada beklemek (turtle). "Kara Yıllar" bunu kısmen çözüyor.
- Sıkıyönetim çok güçlü olabilir. Ordu nüfuzu artışı yeterince sert olmalı.
- Bunlar ancak bot vs bot simülasyonuyla görülebilir. Bu yüzden simülasyon çekirdeği şart.

### 4.5 Kartopu ve geri dönüş
Önde olan köy daha hızlı büyür ve oyun 10. turda belli olabilir. Geri dönüş mekanikleri:
- Güçlü köy tarikat ve darbe riskine daha açık (zaten var, iyi).
- Geride olan oyuncuya kart seçiminde 4. seçenek.
- Göç mekaniği tersine de işleyebilir: aşırı kalabalık köyde huzur düşer.

### 4.6 Rastgelelik ve satranç
"Satranç gibi" hedefi ile rastgele olaylar ve kartlar çelişebilir. Öneri:
- Rastgele olaylar **bir tur önceden haber verilsin** (kehanet, gezgin söylentisi). Oyuncu hazırlanabilir.
- Kart havuzu iki oyuncuya simetrik olsun.

### 4.7 Mikro yönetim
Nüfus 30–40 kişiye çıkınca herkesi tek tek atamak sıkıcı olur. Öneri: **azalar otomatik atama yapsın, oyuncu politika belirlesin.** "Tarıma %50, askere %20" gibi. İyi aza doğru kişiyi doğru işe koyar, kötü aza karıştırır. Bu, liyakat temasını mekaniğin merkezine taşır ve mikro yönetimi ortadan kaldırır. Oyuncu istediğinde tek bir köylüyü elle de atayabilir.

### 4.8 Süre tutarsızlığı
Kararlar dosyasında "maç 15–25 dakika" yazıyor, ama tur sınırı kaldırıldı. Çocukların 8 turda büyümesi de maçın 30+ tur sürmesini gerektiriyor. Hedef süre yeniden belirlenmeli (öneri: 25–40 dakika, 30–40 tur).

### 4.9 Öğretici
Bu karmaşıklıkta oyun, öğretici olmadan ilk dakikada oyuncuyu kaybeder. İlk maç, adım adım açılan bir senaryo olmalı (önce sadece tarım, sonra eğitim, sonra ordu).

### 4.10 Yapay zeka rakibi
- Tur başına gecikme (1–5 sn) eş zamanlı turda kabul edilebilir.
- LLM geçersiz emir verebilir: şema doğrulama ve bot yedeği şart (planlandı).
- Kural tabanlı bot zayıf olursa oyun kolay biter. Bot için en az 3 kişilik profil: Tarımcı, Militarist, Dindar.

## 5. Eksik kalan kısımlar (baştan sona)

### Başlangıç ve kurulum
- [ ] Başlangıç kaynakları (altın, gıda, EP).
- [ ] 10 köylünün yetenek ve istekleri nasıl belirleniyor: rastgele mi, oyuncu bir aday havuzundan mı seçiyor (örneğin 15 adaydan 10)?
- [ ] Muhtarın kendisi bir karakter mi, özellikleri var mı?
- [ ] Harita düzeni: tarım alanı slotlardan ayrı mı, slot mu kaplıyor?

### Ekonomi
- [ ] Bina listesi, maliyetleri (altın, EP), yapım süreleri.
- [ ] Muhtarlık seviyesine göre slot sayısı (öneri: 3, 5, 7, 9).
- [ ] Eğitim Puanı nasıl üretiliyor (okul + öğretmen köylü?).
- [ ] Depo kapasitesi, çürüme oranları, işleme süreleri.
- [ ] Asker maaşı.
- [ ] Vergi var mı (halktan altın, huzur karşılığında)?

### Dallar ve doktrinler
- [ ] **Her dalın seviye ağacı tamamen eksik**: Tarım, Eğitim, Askeri, İnanç dallarının her seviyesi ne açıyor? En kritik eksik budur.
- [ ] Doktrinlerin kalıcı bonusları ve kapattığı yollar.

### Köylüler
- [ ] Karakter özellikleri (hırslı, dindar, tembel, sadık) olacak mı?
- [ ] Aza sayısı, seçimi, değiştirilmesi, aza kalitesi formülü.
- [ ] Köylülerin yeteneği zamanla gelişiyor mu (eğitimle)?

### Askeri
- [ ] Asker eğitim süresi, silah atölyesinin girdisi ve çıktısı.
- [ ] Sur ve savunma binaları.
- [ ] Sabotaja karşı savunma (bekçi, gözcü kulesi).
- [ ] Saldırı her tur mümkün mü, bekleme süresi var mı?

### Kartlar ve olaylar
- [ ] Tam kart listesi: maliyet, nadirlik, karşı hamle.
- [ ] Rastgele olay listesi.

### Bitiş ve sunum
- [ ] Muhtarın ölüm kuralı (öneri hazır, onay bekliyor).
- [ ] Her bitiş için son sahnesi.
- [ ] Düşmanlığın hikayesi.
- [ ] Görsel stil referansı, ses ve müzik planı.
- [ ] Ekran akışı: ana menü, ayarlar (API anahtarı), maç, sonuç.
- [ ] Dil: Türkçe, İngilizce, ya da ikisi.

### Teknik
- [ ] Hedef platform (Windows, Mac, Steam?).
- [ ] Kayıt ve yükleme.
- [ ] Jev'in API'si.
- [ ] Mac'te Unreal kurulumu için disk alanı.

## 6. Önerilen yapım sırası

1. **Simülasyon çekirdeği (C++):** tarım, gıda, altın, psikoloji, huzur, mevsimler. Ekransız, bot vs bot.
2. **Denge testi:** yüzlerce bot maçıyla dominant stratejileri bulmak.
3. **Minimal arayüz:** metrik barları, slotlar, emir paneli.
4. **Ordu, savaş, darbe.**
5. **Kartlar.**
6. **Köylüler ve azalar.**
7. **İnanç ve tarikat.**
8. **Jev / LLM rakip.**
9. **Görsel cila, ses, öğretici.**
10. **İki kişilik mod.**
