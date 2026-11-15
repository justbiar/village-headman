# Oyun Tasarımı (taslak)

## Çekirdek fikir

İki düşman köy karşı karşıya. Harita ortadan ikiye bölünmüş, her yarıda bir muhtarlık binası ve bina slotları var.
Her muhtar köyünü farklı dallarda geliştirebilir, ama her dalın bir bedeli ve bir dengesi var.
Hedef satranç gibi bir his: her hamle bir şeyi güçlendirirken başka bir şeyi açıkta bırakıyor.

Düşmanlığın hikayesi ayrıca yazılacak.

## Zaman modeli

- **Tur bazlı, eş zamanlı gizli emir.** İki muhtar kararlarını aynı anda verir, sonra tur birlikte çözülür.
- 1 tur = 1 mevsim.
- Hedef maç süresi: 15–25 dakika (yaklaşık 20–30 tur).

## Harita ve slotlar

- Tanımlı slotlar var, serbest yerleşim yok.
- Başlangıçta **3 slot**. Muhtarlık binasının seviyesi arttıkça slot sayısı artar.
- Muhtarlık binası seviyesi Eğitim Puanı ile yükseltilir.

## Gelişim dalları

| Dal | Ne sağlar | Neden gerekli |
|---|---|---|
| Tarım | Gıda ve (satışla) altın | Her şeyin parası buradan gelir, gıda yoksa isyan çıkar |
| Eğitim | Eğitim Puanı (EP) | Bina geliştirmek için şart |
| Askeri | Askeri güç | Köyü savunur, rakibi yok eder |
| İnanç | Psikolojiyi stabilize eder | Bedeli: tarikatlar güçlenir |

### Uzmanlaşma kilidi (yön değiştirmenin zorlaşması)

- Her dalın seviyeleri var. Bir dala yatırdıkça diğer dallara geçmenin maliyeti katlanarak artar.
- Seviye 3'ten sonra o dal bir **Doktrin** olur: kalıcı bonus verir ama karşıt dalın üst seviyelerini kapatır.
- Oyunun başında yön değiştirmek ucuz, ortasında pahalı, sonunda neredeyse imkansız.

## Kaynaklar (birikir)

- **Altın:** tarım ürünlerinin satışından gelir.
- **Gıda:** tarımdan gelir, nüfus tüketir.
- **Eğitim Puanı (EP):** bina gelişimi için harcanır.
- **Askeri Güç:** asker sayısı ile ekipmanın çarpımı (silah atölyesi).

## Denge metrikleri (bir aralıkta tutulmalı)

| Metrik | Çok düşükse | Çok yüksekse |
|---|---|---|
| Gıda | Açlık isyanı (oyun biter), ordu dağılır | Çürüme, depo maliyeti |
| Psikoloji | İsyan (oyun biter) | Sorun yok |
| Huzur | Doğurganlık ve çalışma isteği düşer | Sorun yok |
| Ordu gücü | Saldırıya açık | **Darbe**: ordu muhtarı devirir (oyun biter) |
| İnanç | Psikoloji tamponu yok | **Tarikat** güçlenir, kendi taleplerini dayatır |

### Psikoloji ve huzur farkı

- **Huzur:** doğurganlığı ve çalışma isteğini etkiler. Altın az, gıda az, hane başına gelir düşükse azalır. Ölümcül değildir ama köyü yavaşça boğar.
- **Psikoloji:** isyana götürür, yani ölümcüldür. Aşırı çalışma ve yıpranma ile düşer.
- İkisi de köylülerin **kişisel değerlerinin ortalaması**. Köy değeri = köylülerin ortalaması (ağırlıklı ortalama düşünülebilir).

### Psikolojiyi düzeltmenin iki yolu

1. **Orduya daha çok yetki vermek:** halk sakinleşir ama ordu güçlenir, darbe riski artar.
2. **İnanç birimini açmak:** insanlar durgunlaşır ama tarikatlar diye yeni bir denge ortaya çıkar.

## Bitiş koşulları

1. Muhtarın öldürülmesi.
2. Gıdanın bitmesi ve açlık isyanı.
3. Psikolojinin düşmesi ve isyan.
4. Ordunun fazla güçlenip darbe yapması.
5. (Öneri) Tarikatın köyü ele geçirmesi.

## Tarım

### Mahsul üçgeni

Hız, maliyet ve getiriden ancak ikisi bir arada olur. Üçü birden olan ürün risklidir.

| Ürün | Hız | Maliyet | Getiri | Risk |
|---|---|---|---|---|
| Buğday | Hızlı | Ucuz | Az para, orta gıda | Yok |
| Patates | Yavaş | Ucuz | Çok gıda, az para | Yok |
| Pancar | Orta | Orta | Para (şekere işlenirse çok) | Yok |
| Safran (veya başka lüks ürün) | Hızlı | Ucuz | Çok para | Vaktinde hasat edilmezse çürür, sabotaja açık |

### Riskler

- Vaktinde hasat edilmezse çürüme.
- Rakip sabotajı: örneğin **sarmaşık** ile tarlayı sabote etmek.

### Hasat ve işçiler

- Tarlaları hasat eden işçiler var. İşçi sayısı ve uygunluğu verimi belirler.

### İşleme tesisi

- Her ürün için ayrı tesis kurmak ölçeği büyütür.
- Buğdaydan un (değirmen), pancardan şeker (şeker atölyesi).
- İşlenmiş ürün daha pahalıya satılır, daha geç bozulur.

### Depolar

- Ürünleri depolar. Depo kapasitesi bir darboğaz.

## Nüfus

- Başlangıç: **5 kadın, 5 erkek**.
- Evlilik için huzur eşiği.
- Çocuk 1 turda doğar, 6–8 turda yetişkin olur (maç kısa olduğu için büyüme hızlı olmalı).
- Huzur düşükse köylüler çocuk yapmayı bırakır.

## Köylüler

- Her köylünün bir **Yeteneği** (Tarım, Zanaat, Eğitim, Savaş, İnanç) ve ayrı bir **İsteği** var.
- Başta oyuncu, kimin ne yapacağını isteklerine veya yeteneklerine göre seçer.
- Yeteneği eğitim olan birini tarıma verirsen kişisel huzursuzluğu artar.

### Azalar

- Köylüler arasından 2–3 kişilik bir konsey (azalar) seçilir.
- Azaların kalitesi tüm atamalara bir verimlilik çarpanı uygular.
- Kötü azalar küçük insanlara büyük işler, büyüklere küçük işler verir. Tema: "Bu sistem koskoca imparatorlukları çökertti."

## Binalar (ilk liste)

- Muhtarlık (slot sayısını belirler)
- Tarla
- İşleme tesisi (değirmen, şeker atölyesi)
- Depo
- Okul / eğitim binası
- Kışla
- Silah atölyesi
- İnanç binası

## Güç kartları

- 9 Kings tarzı: her tur 3 karttan 1'i seçilir.
- Örnek kartlar:
  - **Sarmaşık:** rakibin bir tarlasını sabote eder.
  - **Dedikodu:** rakibin psikolojisini düşürür.
  - **Kışkırtma:** rakip köyde isyanı hızlandırır.
  - **Casus:** rakibin bu turki gizli emrini görürsün.
  - **Kıtlık Söylentisi:** rakibin gıda satış fiyatını düşürür.
  - **Aza Satın Alma:** rakibin bir azasının verimini düşürür.

## Savaş

- Basit tutulacak.
- Ekranın üst tarafında iki köyün **can barı** var.
- Askeri güçler karşılaşır, sonuç can barlarına yansır.
- Muhtarlık can barı sıfırlanırsa muhtar ölür.

## Rakip

- **Yapay zeka (LLM) rakibi:** ucuz bir model.
  - Her oyuncuya ücretsiz 1 maçlık hak.
  - Sonrasında oyuncu ayarlardan kendi modelini / API anahtarını ekleyebilir.
  - Teknik not: oyuna gömülen API anahtarı build'den çıkarılabilir. Ücretsiz hak, anahtarı tutan küçük bir sunucu (proxy) üzerinden verilmeli.
- **Kural tabanlı bot:** her zaman ücretsiz, API gerektirmez.
- **İki kişilik mod:** zaman kalırsa en son.

## Görsel ve ton

- 2D izometrik görünüm.
- Ciddi ve karanlık ton.
- Unreal kullanılırsa öneri: low-poly 3D + ortografik izometrik kamera (görünüş 2D izometrik, ama asset üretimi ve görsel kalite daha kolay). Paper2D Unreal'da zayıf.
