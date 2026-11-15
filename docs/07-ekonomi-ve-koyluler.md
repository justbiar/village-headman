# Ekonomi ve Köylüler

Bu dosyada kullanıcının verdiği kararlar ve onların etrafında benim kurguladığım değerler var.
**K** işaretli satırlar kullanıcının kararı, **Ö** işaretli satırlar benim önerim (değiştirilebilir).
1 tur = 1 mevsim.

## 1. Kaynaklar

| Kaynak | Nereden gelir | Nereye gider | Sınır |
|---|---|---|---|
| **Para** (six / nine) | Hasat satışı | İnşa, tohum, asker | Sınırsız (kese) |
| **Odun** (K) | Köyün etrafındaki ağaçlar | İnşa, kışın ısınma, satış (2 odun = 1 para) | Depo kapasitesi |
| **Gıda** | Hasat | Nüfus | Depo kapasitesi |
| **Eğitim Puanı (EP)** | İnşa etmek ve Eğitim Merkezi (K) | Gelişmiş binalar, muhtarlık seviyesi | Sınırsız |

## 2. Başlangıç (K: kaynaklar sadece ilk tarlaya yetecek kadar)

| Kaynak | Başlangıç | Not |
|---|---|---|
| Para | 14 | İlk tarla (10) + ilk tohum (2) + 2 artık |
| Odun | 12 | İlk tarla (10) + 2 artık |
| Gıda | 50 | 10 köylü yaklaşık 5 tur yer |
| EP | 0 | |
| Slot | 3, hepsi boş | |

**Ö:** Bu başlangıç gerilimli olacak şekilde ayarlandı. İlk tur tarla kurulmazsa köy 6. turda aç kalır.

**Neden odun satılabiliyor (Ö):** Sadece ilk tarlaya yetecek para varsa, ikinci tarlanın parası ancak hasat satılarak bulunur. Bu da köy açken yiyeceği satmak demek ve açlık sarmalına gider. Bu yüzden **odun pazarda satılabilir: 2 odun = 1 para.** İlk yol haritası şöyle olur:

| Tur | Ne olur |
|---|---|
| 1 | Tarla kurulur (para 4, odun 2 kalır). 8 köylü odun keser (+24 odun) |
| 2 | Tarla biter, buğday ekilir. 16 odun satılır (+8 para) |
| 3 | İkinci tarla kurulur |
| 4 | İlk hasat. Köy kendi kendine yetmeye başlar |

Böylece ilk dakikanın kararı "kaç kişi odun keser, kaç kişi tarlaya" olur ve köylülerin yatkınlıkları ilk turdan önem kazanır.

## 3. Ağaçlar ve odun (K: köyün etrafında toplanabilir ağaçlar)

**Ö:**
- Her köyün etrafında bir **orman halkası** var. Slot kaplamaz.
- Ormanın stoku **120 odun** (görselde yaklaşık 12 ağaç kümesi, her biri 10 odun).
- Köylüler **Oduncu** işine atanır. Oduncu başına tur başına **3 odun** (kışın 2).
- Orman ilkbahar ve yazda tur başına **+4 odun** kendini yeniler, 120'yi geçmez.
- Stok bittikçe ağaçlar görselde tek tek kesilmiş kütüklere döner. Orman biterse odun da biter.
- **Kışın ısınma:** her kış turunda 5 kişi başına 1 odun yanar. Odun yoksa psikoloji -3.

## 4. Depo

**Ö:**
- Muhtarlığın kendi deposu: **60 gıda, 40 odun.**
- Her **Ambar** binası: **+60 gıda, +40 odun** kapasite.
- Kapasiteyi aşan ürün kaybolur. Tur raporunda "The granary overflowed" yazar.
- **Bozulma:** her tur depodaki gıdanın %4'ü bozulur. Köyde en az bir Ambar varsa %2.
- Ambar Yangını kartı gıdanın dörtte birini yakar (Ambar binası bu oranı değiştirmez, ama yangından sonra stok yine de daha büyük kalır).

## 5. Eğitim Puanı (K: inşa ettikçe gelir, Eğitim Merkezi sürekli üretir)

**Ö:**
- **Usta payı:** her bina tamamlandığında **+2 EP**. Muhtarlık seviye atlayınca **+5 EP**.
- **Eğitim Merkezi:** öğretmen başına tur başına **3 EP × öğretmenin verimi** (bkz. 7. bölüm).

## 6. Binalar (Ö: maliyet ve süre)

Hepsi slot kaplar (K: tarlalar da slotlara dahil).

| Bina | Para | Odun | EP | Süre (tur) | İşçi | Etkisi |
|---|---|---|---|---|---|---|
| Tarla | 10 | 10 | 0 | 1 | 2 çiftçi | Seçilen ekini yetiştirir. Ekin her ekimde ayrıca tohum ister |
| Ambar | 8 | 15 | 0 | 1 | 0 | +60 gıda, +40 odun kapasite, bozulma yarıya iner |
| Eğitim Merkezi | 15 | 20 | 0 | 2 | 2 öğretmen | EP üretir |
| Kışla | 20 | 25 | 5 | 2 | 0 | Asker almayı açar (tur başına en fazla 2), savaş gücü +%10 |
| İnanç Evi | 15 | 15 | 5 | 2 | 1 rahip | Psikoloji +4/tur, tarikat +3/tur |

| Muhtarlık | Para | Odun | EP | Süre | Slot | Konsey koltuğu |
|---|---|---|---|---|---|---|
| Seviye 1 (başlangıç) | | | | | 3 | 1 |
| Seviye 2 | 25 | 20 | 10 | 2 | 5 | 2 |
| Seviye 3 | 40 | 40 | 25 | 3 | 7 | 3 |
| Seviye 4 | 60 | 60 | 45 | 3 | 9 | 3 |

- İnşa süresince slotta iskele görünür, bina çalışmaz.
- **Kışla olmadan asker alınamaz.** Askeri yol bilinçli bir yatırım olur.
- Kışla ve İnanç Evi EP istediği için, önce bir şeyler inşa etmek ya da Eğitim Merkezi kurmak gerekir. Eğitim dalı böylece doğal olarak "kilit açan" dal olur.

### Ekinler (değişmedi)

| Ekin | Tohum (para) | Büyüme | Verim | Gıda/birim | Fiyat/birim | Risk |
|---|---|---|---|---|---|---|
| Buğday | 2 | 2 tur | 8 | 2 | 2 | Yok |
| Patates | 2 | 4 tur | 12 | 3 | 1 | Yok |
| Safran | 3 | 2 tur | 4 | 0.5 | 8 | Vaktinde toplanmazsa çürür, sarmaşığa hedef |

Para yoksa tohum ambardan ayrılır (1 para yerine 2 gıda). Bu kural bot testlerinde bulunan "ölüm sarmalını" önlüyor.

## 7. Köylüler

### Yatkınlıklar (K: 4 değer, rastgele)

Her köylünün 4 yatkınlığı var, her biri **1 ile 5** arası:

| Yatkınlık | Hangi işlerde kullanılır |
|---|---|
| **Farming** (tarım) | Çiftçi, Oduncu |
| **Management** (yönetim) | Konsey üyesi (Elder) |
| **Military** (askerlik) | Asker |
| **Education** (eğitim) | Öğretmen, Rahip |

**Ö:** Rastgele dağıtımda 4 değerin toplamı 10 olur (en az 1, en fazla 5). Böylece her köylünün bir iki güçlü yanı ve zayıf yanları olur, "her şeyi iyi yapan" köylü çıkmaz.

**Verim formülü (Ö):** `verim = 0.55 + 0.15 × yatkınlık`

| Yatkınlık | 1 | 2 | 3 | 4 | 5 |
|---|---|---|---|---|---|
| Verim | %70 | %85 | %100 | %115 | %130 |

### Karakter (K: her köylünün bir karakteri var)

**Ö:** Her köylüye rastgele 1 karakter:

| Karakter | Etkisi |
|---|---|
| **Hardworking** | Verim +%10 |
| **Lazy** | Verim -%15 |
| **Devout** | İnanç Evi varken psikolojisi +1/tur. Rahip olursa tarikat +1/tur ek |
| **Ambitious** | Asker olursa ordu nüfuzu +1/tur. Konseyde olursa yönetim +1 |
| **Loyal** | Tarikat talebi reddedilince firar etmez. Darbeye katılmaz |
| **Doubter** | Paranın aslında öbür rakam olduğundan şüphelenir. Psikolojisi 30'un altına düşerse rakip köye kaçar |

"Doubter", hikayeyi (6 mı 9 mu) doğrudan mekaniğe bağlıyor ve rakip köyle ikinci bir etkileşim kanalı açıyor.

### İşler

| İş | Nerede | Yatkınlık |
|---|---|---|
| Çiftçi | Tarla (2 kişi) | Farming |
| Oduncu | Orman (sınırsız) | Farming |
| Öğretmen | Eğitim Merkezi (2 kişi) | Education |
| Rahip | İnanç Evi (1 kişi) | Education |
| Asker | Kışla gerekir | Military |
| Konsey üyesi (Elder) | Muhtarlık koltukları | Management |
| Boşta | | |

### Kişisel ruh hali (yanlış işe verme)

**Ö:**
- Köylü en yüksek yatkınlığının olduğu işteyse: kişisel psikoloji **+1/tur**.
- Yatkınlığı 2 veya altı olan bir işteyken başka bir yatkınlığı 4 veya üstüyse: **-2/tur** ("küçük insanlara büyük iş").
- Köyün psikolojisi, kişisel psikolojilerin ortalaması. En mutsuz %20 iki kat ağırlıkla sayılır.

### Konsey (liyakat mekaniğinin jam'deki hali)

**Ö:**
- Muhtarlık seviyesine göre 1, 2 ya da 3 konsey koltuğu var.
- Konseyin ortalama yönetim yatkınlığı bütün köyün verimini etkiler: 1 ise **-%10**, 3 ise **0**, 5 ise **+%10**.
- **"Let the elders decide"** düğmesi: atamaları konsey yapar.
  - İyi konsey (yönetim 4–5) herkesi en uygun işe koyar.
  - Orta konsey (3) çoğunu doğru koyar, birkaç hata yapar.
  - Kötü konsey (1–2) neredeyse rastgele dağıtır.
- Oyuncu her zaman elle de atama yapabilir. Kalabalıklaşınca konseye bırakmak cazip olur, ama konseyi kimin oluşturduğu her şeyi belirler.

### Nüfus

- Başlangıç: 5 kadın, 5 erkek, yatkınlıkları ve karakterleri rastgele (K).
- Doğan çocukların yatkınlıkları ve karakteri de rastgele. Çocuk 8 turda yetişkin olur.
- Tüketim: yetişkin 1, asker 1.5, çocuk 0.5 gıda/tur.

## 8. Muhtar (K: görünmez)

Muhtar oyunda görünmez. Sadece şu anlarda kısa bir animasyonla ortaya çıkar:

| An | Animasyon fikri |
|---|---|
| Savaşta ölüm | Muhtarlığın kapısından son kez çıkar, düşer |
| İsyan | Kalabalık muhtarlıktan onu sürükleyerek çıkarır |
| Darbe | General muhtarın şapkasını alıp kendi takar |
| Tarikat | Cübbeli figürler muhtarı içeri alır, kapı kapanır |
| Açlık | Boş ambarın önünde tek başına oturur |
| Suikast (M2) | Gece, tek bir mum söner |

Bu anlar aynı zamanda Director's Cut ekranının son sahnesi olur.
