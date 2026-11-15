# Muhtarlar (çalışma adı)

İki düşman köyün karşı karşıya geldiği, 2D izometrik, tur bazlı bir strateji ve köy yönetimi oyunu.
Oyunun özü: **köyü büyütmek değil, köyü dengede tutmak.** Ton ciddi ve karanlık.

Bu repo şimdilik sadece tasarım notlarını içeriyor. Kodlamaya tasarım netleşince başlanacak.

## Dokümanlar

| Dosya | İçerik |
|---|---|
| [docs/01-jam-analizi.md](docs/01-jam-analizi.md) | Epic MegaJam 2026 kuralları, takvim, puanlama, ödüller |
| [docs/02-oyun-tasarimi.md](docs/02-oyun-tasarimi.md) | Çekirdek oyun mimarisi: kaynaklar, denge metrikleri, mahsuller, nüfus, köylüler, kartlar |
| [docs/03-kararlar-ve-sorular.md](docs/03-kararlar-ve-sorular.md) | Verilen kararlar, teknik kısıtlar, açık sorular |
| [docs/00-orijinal-fikir.md](docs/00-orijinal-fikir.md) | Fikrin ilk hali, olduğu gibi |

## Kısa özet

- 1v1: iki muhtarlık binası karşı karşıya, harita ortadan ikiye bölünmüş.
- Gelişim dalları: **Tarım** (para ve gıda), **Eğitim** (bina gelişimi), **Askeri** (savunma ve saldırı), **İnanç** (psikoloji tamponu, tarikat riski).
- Her metriğin hem altında hem üstünde bir tehlike var: zayıf ordu saldırı yer, fazla güçlü ordu darbe yapar.
- Her tur 3 güç kartından 1'i seçilir (sabotaj, propaganda, casusluk...).
- Başta 5 kadın ve 5 erkek köylü. Evlilik, çocuk ve büyüme var.
- Köylülerin yeteneği ve isteği var. Yanlış işe verilen köylü mutsuz olur. Azaların kalitesi tüm yönetimi etkiler.
- Rakip: yapay zeka (LLM) veya kural tabanlı bot. İki kişilik mod sonra.
