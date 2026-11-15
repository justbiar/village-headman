# Kararlar, Kısıtlar ve Açık Sorular

## Verilen kararlar

| Konu | Karar |
|---|---|
| Hedef | Epic MegaJam 2026'ya yetiştirmek istendi (bkz. teknik kısıtlar) |
| Rakip | Yapay zeka (ucuz LLM, oyuncu başına 1 ücretsiz hak, sonra kendi API anahtarı) + kural tabanlı bot |
| İki kişilik mod | Zaman kalırsa en son |
| Savaş | Basit, üstte can barları |
| Maç süresi | 15–25 dakika (öneri kabul edildi) |
| Slotlar | Tanımlı slotlar, başta 3, muhtarlık seviyesiyle artar |
| Ton | Ciddi ve karanlık |
| Motor deneyimi | Genelde Godot, Unreal az. Unreal'a Claude bağlanarak geliştirilecekti |

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

- [ ] Hangi seçenekle ilerlenecek (yukarıdaki 1, 2 veya 3)?
- [ ] "jev" ile kastedilen model / sağlayıcı hangisi?
- [ ] Muhtar nasıl ölür: ordu muhtarlığa ulaşınca mı, suikast kartıyla mı, ya da ikisiyle de mi?
- [ ] Tarikat mekaniğinin detayı: tarikat ne ister, nasıl ele geçirir?
- [ ] Düşmanlığın hikayesi (kullanıcı yazacak).
- [ ] Köylülerin istek ve yetenek seçimi oyunun başında mı, yoksa her doğumda da mı?
- [ ] Oyunun adı.
