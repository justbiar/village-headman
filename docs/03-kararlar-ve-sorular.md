# Kararlar, Kısıtlar ve Açık Sorular

## Verilen kararlar

| Konu | Karar |
|---|---|
| Oyunun adı | **Village Headman** |
| Hedef | **Epic MegaJam 2026'ya yetiştirilecek.** Unreal tarafı bu Mac'te değil, başka bir bilgisayarda yapılacak. Bu Mac plan ve tasarım içindir |
| Katılım | **Takım (2 kişi).** Kullanıcı: tasarım ve plan. **maybeno2906**: Unreal'da kodlama ve yapım. Teslimde ikisi de adı ve Epic hesabının e-postasıyla listelenecek. Best Team (2+ kişi) ödülüne uygun, Solo Driver'a değil |
| Planın detayı | Plan bütün sistemleri tam anlatır, kodlayan kişi öncelik sırasına göre yetişebildiği kadarını yapar (bkz. 06, bölüm 3) |
| Muhtarın ölümü (jam) | Sadece savaşta muhtarlık can barının sıfırlanması. Suikast kartı M2'ye kaldı |
| Tema ekranı | Maç sonunda **"Director's Cut"** özeti: hangi kararlar köyü batırdı ya da kurtardı |
| Arayüz dili | **İngilizce** |
| Köyler | **Six** ve **Nine** (hikayeden geliyor, bkz. 06 dosyası) |
| Hikaye tonu | Komik bir sebep (6 mı 9 mu?), karanlık sonuçlar: kara mizah |
| Ses | Kullanıcı hazırlayacak |
| Görsel referans | 9 Kings (sadece ilham: okunaklı küçük krallık, net siluetler. Görünüşü kopyalanmayacak) |
| Mimari | Jam'de yapılabilenler şimdi, gerisi sonradan takılabilecek şekilde katmanlı (bkz. 06 dosyası) |
| Teknoloji | **Unreal Engine 5** (önce Three.js düşünüldü, sonra UE5 seçildi). İzometrik görünüm ortografik kamera ile |
| Görsel stil | **2D pixel art** (izometrik). Daha önce Tripo ile low-poly 3D düşünülmüştü, pixel art'a geçildi |
| Rakip | Yapay zeka (ucuz LLM, oyuncu başına 1 ücretsiz hak, sonra kendi API anahtarı) + kural tabanlı bot |
| İki kişilik mod | Zaman kalırsa en son |
| Savaş | Basit, üstte can barları |
| Maç süresi | 15–25 dakika (öneri kabul edildi) |
| Slotlar | Tanımlı slotlar, başta 3, muhtarlık seviyesiyle artar |
| Ton | Önce "ciddi ve karanlık", sonra kara mizaha döndü (komik sebep, karanlık sonuçlar) |
| Motor deneyimi | Genelde Godot, Unreal az. Unreal'a Claude bağlanarak geliştirilecekti |

## Kural: build boyutu en fazla 1 GB

Jam kuralı: masaüstü build'in zip'i **1 GB'ın altında** olmalı (büyükse butler gibi ayrı araçlar gerekir, bunu istemiyoruz). Hedefimiz bunun çok altında kalmak.

### Boyut bütçesi (hedef: zip 400 MB altı)

| Parça | Tahmini | Not |
|---|---|---|
| Unreal motoru (paketlenmiş, Windows) | 150–300 MB | Boş bir proje bile bu kadar tutar. Development build Shipping'den büyüktür |
| Pixel art sprite ve arayüz | 10–40 MB | Küçük çözünürlüklü PNG'ler, sorun değil |
| Ses ve müzik | 20–60 MB | En büyük risk burası. Müziği OGG/sıkıştırılmış tut, uzun WAV koyma |
| Toplam | ~200–400 MB | 1 GB'ın rahat altında |

### Boyutu küçük tutma kuralları

1. **Starter Content ekleme**, kullanılmayan eklentileri (plugins) kapat.
2. Paketleme ayarlarında: **Use Pak File** açık, **Create compressed cooked packages** açık, **Exclude editor content when cooking** açık.
3. Sadece kullanılan haritayı paketle ("List of maps to include in a packaged build").
4. Mümkünse **Shipping** build. Jam Windows ve macOS için Shipping'i kabul ediyor.
5. Teslimden önce zip'in boyutuna bak. 1 GB'a yaklaşırsa önce sesleri kontrol et.

### Pixel art için Unreal ayarları (görüntünün bulanık çıkmaması için)

- Sprite dokularında **Texture Group: 2D Pixels (unfiltered)**, filtre **Nearest**.
- **Mip map yok** (Mip Gen Settings: NoMipmaps).
- Sıkıştırma: **UserInterface2D (RGBA)** ya da kayıpsız. Normal sıkıştırma pixel art'ı bozar.
- Kamera ortografik, sprite ölçeği tam sayı katlarında (piksel kaymasını önler).
- Arayüz fontu pixel font ise UMG'de de filtre kapalı olmalı.

## Teknik kısıtlar (15 Kasım 2026, 17:49 TR)

- Jam teslimine yaklaşık 11 saat kalmıştı (son: 16 Kasım 04:59 TR).
- Mac'te (Apple M4) Unreal Engine ve Xcode kurulu değil.
- Diskte 17.7 GB boş yer var.

### Motor boyutları (yaklaşık)

| Motor | Boyut | Not |
|---|---|---|
| UEFN | Fortnite (~30–50 GB) + UEFN (~10–20 GB) | Sadece Windows. Verse'ten dış LLM API'sine istek atılamaz. Fortnite adası olarak çıkar, 2D izometrik strateji için uygun değil. |
| Unreal Engine 5 | ~35–60 GB | Mac'te paketleme için Xcode da lazım (~15–35 GB). Toplam en az ~60–80 GB. |
| Godot | ~150 MB | Jam'e giremez (jam Unreal/UEFN zorunlu tutuyor) |

### Seçenekler

1. Mac'te ~60–80 GB yer açıp Unreal kurmak ve en küçük oynanabilir dilimi yapmak (tek ekran, bota karşı, 3 slot, 3 ürün, 2 metrik, kartlar).
2. Yeri olan bir Windows bilgisayarda Unreal kullanmak (Xcode gerekmez).
3. Jam'i bırakıp oyunu Godot'ta, tam tasarımla ve jam baskısı olmadan yapmak (önerilen).

## Açık sorular

- [x] Motor: Unreal Engine 5.
- [x] Oyunun adı: Village Headman.
- [x] "jev": bir karar (decision) modeli. Rakip yapay zekası için kullanılacak.
- [ ] Jev'in API'si, dokümanı ve fiyatı.
- [ ] Muhtar nasıl ölür? (öneri: 04 dosyasında)
- [x] Tarikat talebi reddedilirse: huzursuzluk artar, ordu düzeni bozulur (firar), isyan riski doğar.
- [x] Kazanma: tur sınırı yok, biri düşene kadar sürer ("Kara Yıllar" önerisiyle).
- [x] Rakibin metrikleri gizli, kurduğu binalar görünür.
- [ ] Düşmanlığın hikayesi (kullanıcı yazacak).
- [ ] Köylülerin istek ve yetenek seçimi oyunun başında mı, yoksa her doğumda da mı?
