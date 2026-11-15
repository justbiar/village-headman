# Hikaye ve Büyüyen Mimari

## 1. Hikaye: Six ve Nine

İki kardeş, aynı köyün muhtarlığını paylaşıyordu. Bir gün yolda bir para buldular. Üzerinde tek bir rakam vardı.

Biri "Altı" dedi. Öbürü "Dokuz" dedi.

Para hep aynı paraydı. Sadece hangi taraftan baktığına bağlıydı. Tartışma bir gün sürdü, sonra bir yıl, sonra bir ömür. Köy ikiye bölündü.

- **Six:** "Altı" diyen kardeşin köyü. Para birimi **six**.
- **Nine:** "Dokuz" diyen kardeşin köyü. Para birimi **nine**.

### Ton: kara mizah

Sebep gülünç, sonuçlar karanlık. İnsanlar bir rakam yüzünden aç kalıyor, isyan ediyor, tarikatlara sığınıyor. Komiklik sebepte ve dilde, karanlık sonuçlarda.

### Hikayenin oyuna yansıyabileceği yerler (öneri)

| Yer | Fikir |
|---|---|
| Para birimi | Arayüzde altın yerine kendi köyünün parası: "12 six" ya da "12 nine" |
| Haritanın ortası | Para, iki köyün arasında bir taşın üstünde duruyor. İki köyden de bakılınca farklı okunuyor |
| Açılış | 3 kısa sahne: para bulunur, "Six!" "Nine!", köy ikiye bölünür |
| Kart: **Upside Down** | Rakibin parasını ters çevirir. Bir tur boyunca rakibin sattığı ürünler daha ucuza gider |
| Bitiş metinleri | Her bitişin sonunda kardeşlerin tek satırlık bir sözü. Örnek (darbe): "At least the general agrees it's a six." |
| Kazanma ekranı | "History will remember it as a nine." (Nine kazanırsa) |

### Director's Cut ekranı (onaylandı)

Maç bitince oyuncuya maçın "son kurgusu" gösterilir. Temayla bağlantı burada kurulur: muhtar köyün yönetmeniydi, bu da onun filmi.

- **Başlık:** "Director's Cut: The Tale of Six" (ya da Nine)
- **3 sahne:** maçın en belirleyici 3 anı, tur numarası ve mevsimiyle. Örnek:
  - "Year 2, Winter. You sold the last of the potatoes. The granary stood empty."
  - "Year 3, Spring. The general asked for more men. You gave them."
  - "Year 4, Summer. The general agreed it was a six. You did not."
- **Son satır:** bitişin adı ve kardeşin tek satırlık sözü.
- Sahneler, tur sırasında oluşan olaylardan seçilir (en büyük metrik düşüşü, en büyük kayıp, bitişi tetikleyen olay). Mimarideki olay akışı bunun için yeterli.

### Telif notu
9 Kings sadece ilham. Görsel dili, karakterleri ve arayüzü kopyalanmayacak. Jam kuralları da başkasının IP'sini yasaklıyor. "Nine" adı kendi hikayemizden geliyor.

## 2. Büyüyen mimari

Amaç: jam'de yapılabilen küçük oyun bu gece çalışsın, sonradan eklenecek her sistem mevcut sistemleri bozmadan takılabilsin.

### Katmanlar

```
[ Sunum ]      Dünya görünümü · Arayüz paneli · Ses ve efekt
      ↑ okur           ↑ dinler
[ Köprü ]      Durum fotoğrafı (snapshot) · Olay akışı (events) · Emir girişi
      ↑
[ Kurallar ]   Tur çözücüsü → sistemler sırayla çalışır
      ↑
[ Rakipler ]   Bot · (sonra) Jev · (sonra) ikinci oyuncu
```

### Kurallar: sistem sırası

Tur çözücüsü, sistemleri sabit bir sırayla çalıştırır. Yeni bir sistem eklemek, sıraya yeni bir adım eklemek demek.

| Sıra | Sistem | Jam'de |
|---|---|---|
| 1 | Kartlar | Var |
| 2 | Emirler (inşa, asker alma, muhtarlık) | Var |
| 3 | Üretim (tarlalar, okul) | Var |
| 4 | Savaş | Var |
| 5 | Tüketim ve metrikler | Var |
| 6 | Tarikat | Var |
| 7 | Nüfus | Var (basit) |
| 8 | Bitiş kontrolü | Var |
| sonra | Köylüler ve azalar (üretim çarpanı) | Sonra |
| sonra | Huzur | Sonra |
| sonra | Ortak pazar | Sonra |
| sonra | Rastgele olaylar | Sonra |

### Üç kural, her şeyi büyütülebilir tutar

1. **Kurallar sunumu bilmez.** Kurallar katmanı ekran, ses, model bilmez. Sadece durum ve olay üretir. Böylece aynı kurallarla bot maçları ekransız simüle edilebilir.
2. **Sunum kuralları bilmez.** Ekran sadece durumu okur ve olayları dinler. "Hasat oldu" olayı gelince ses çalar, "Sarmaşık" olayı gelince tarla yeşile bürünür. Yeni bir özellik, yeni bir olay türü ekler, eski ekranlar etkilenmez.
3. **Bütün sayılar tek bir ayar tablosunda.** Mahsul değerleri, maliyetler, eşikler kodda dağınık değil, tek yerde. Denge değişikliği kod değiştirmeden yapılır. (Unreal'da bu, bir DataTable ya da tek bir ayar varlığı olur.)

### Rakip arayüzü

Her rakip aynı soruya cevap verir: "Bu durumu görüyorsun, emirlerin ne?"

- Jam: kural tabanlı bot (Çiftçi, Militarist, Dindar).
- Sonra: Jev. Aynı soruyu JSON olarak alır, emirleri JSON olarak döner. Hata olursa bot devreye girer.
- Sonra: ikinci oyuncu (aynı ekranda sırayla, ya da online).

### Kilometre taşları

| Taş | İçerik |
|---|---|
| **M0 (jam, bu gece)** | Tek ekran, bota karşı. 3 slot, 3 mahsul, okul, kışla, inanç evi, 6 kart, savaş (muhtarın tek ölüm yolu can barı), tarikat talepleri, 5 bitiş, Director's Cut özet ekranı. İngilizce arayüz. Solo giriş. |
| M1 | Köylüler ve azalar (liyakat sistemi), huzur |
| M2 | Ortak pazar, rastgele olaylar, sınır tarlaları |
| M3 | Jev rakip, kişilikli muhtar mektupları |
| M4 | İki kişilik mod, öğretici, Türkçe dil |

## 3. Jam'de kesilenler ve geri dönüş yolu

| Kesilen | Neden | Hangi taşta geri gelir |
|---|---|---|
| Köylü bireyleri ve azalar | Arayüzü çok büyütür | M1 |
| Huzur | Psikolojiyle şimdilik birleşik | M1 |
| Jev / LLM | Sunucu ve anahtar gerekir | M3 |
| Ortak pazar | Rakip etkileşimi şimdilik kartlarla | M2 |
| Suikast kartı | Casus ağı sistemi gerekir | M2 |
| İki kişilik mod | Ağ veya sıra ekranı gerekir | M4 |
