"""Render GDD.md into a standalone, themed HTML page for the Artifact viewer.
Usage: python3 build_gdd_page.py <GDD.md> <out.html>"""
import re
import sys
from datetime import datetime

import markdown

src, out = sys.argv[1], sys.argv[2]
text = open(src, encoding="utf-8").read()

md = markdown.Markdown(extensions=["tables", "fenced_code", "toc", "sane_lists"],
                       extension_configs={"toc": {"permalink": False, "slugify": lambda v, s: re.sub(r"[^a-z0-9]+", "-", v.lower()).strip("-") or "s"}})
body = md.convert(text)

# decision markers: **[K]** / **[K: ...]** and **[Ö]** / **[Ö, ...]**
def tag(m):
    kind, rest = m.group(1), (m.group(2) or "").strip(" :,")
    label = "Karar" if kind == "K" else "Öneri"
    cls = "k" if kind == "K" else "o"
    extra = f'<span class="tag-note">{rest}</span>' if rest else ""
    return f'<span class="tag {cls}">{label}</span>{extra}'

body = re.sub(r"<strong>\[(K|Ö)([:,][^\]]*)?\]</strong>", tag, body)
body = body.replace("<table>", '<div class="frame"><table>').replace("</table>", "</table></div>")
body = body.replace("<pre>", '<div class="frame"><pre>').replace("</pre>", "</pre></div>")
# drop the markdown H1 (the page header carries it)
body = re.sub(r"^<h1[^>]*>.*?</h1>", "", body, count=1, flags=re.S)

toc_items = []
for tok in md.toc_tokens:
    for h2 in tok.get("children", []) if tok["level"] == 1 else [tok]:
        name = re.sub(r"\s*\[(K|Ö)[^\]]*\]", "", re.sub(r"<[^>]+>", "", h2["name"])).replace("**", "").strip()
        toc_items.append(f'<li><a href="#{h2["id"]}">{name}</a></li>')
toc = "\n".join(toc_items)

stamp = datetime.now().strftime("%d.%m.%Y %H:%M")

page = f"""<title>Village Headman GDD</title>
<meta name="claude:viewport-fit-sides" content="cover">
<link rel="stylesheet" href="https://fonts.googleapis.com/css2?family=Spectral:wght@500;700&family=IBM+Plex+Sans:ital,wght@0,400;0,500;0,600;1,400&family=IBM+Plex+Mono:wght@400;500&display=swap">
<style>
/* Layout: a field manual. Sticky contents rail on the left, one long reading column, wide tables scroll in their own frame. */
:root {{
  --bg: #F1F0EA; --surface: #FAF9F5; --sunk: #E6E4DB; --fg: #1F201B; --muted: #615F55; --line: #D3D0C4;
  --six: #9C3B33; --nine: #34598F; --accent: #8C6A1C;
  --k-bg: #E4EDE0; --k-fg: #2F5C2A; --o-bg: #F2E7CF; --o-fg: #7A5612;
  --f-display: "Spectral", Georgia, "Times New Roman", serif;
  --f-body: "IBM Plex Sans", system-ui, -apple-system, "Segoe UI", sans-serif;
  --f-mono: "IBM Plex Mono", ui-monospace, Menlo, Consolas, monospace;
}}
@media (prefers-color-scheme: dark) {{ :root:not([data-theme="light"]) {{
  --bg: #141511; --surface: #1B1C17; --sunk: #101109; --fg: #E6E3D8; --muted: #A09D90; --line: #2F3029;
  --six: #E0786C; --nine: #84A9E0; --accent: #D6AE55;
  --k-bg: #22331F; --k-fg: #A4D196; --o-bg: #3A3020; --o-fg: #E5C27A; color-scheme: dark }} }}
:root[data-theme="dark"] {{
  --bg: #141511; --surface: #1B1C17; --sunk: #101109; --fg: #E6E3D8; --muted: #A09D90; --line: #2F3029;
  --six: #E0786C; --nine: #84A9E0; --accent: #D6AE55;
  --k-bg: #22331F; --k-fg: #A4D196; --o-bg: #3A3020; --o-fg: #E5C27A; color-scheme: dark }}
body {{ background: var(--bg); color: var(--fg); font-family: var(--f-body); font-size: 15px; line-height: 1.6; }}
.shell {{ max-width: 1240px; margin: 0 auto; padding-left: max(16px, env(safe-area-inset-left, 0px)); padding-right: max(16px, env(safe-area-inset-right, 0px)); display: grid; grid-template-columns: 250px minmax(0, 1fr); gap: 40px; }}
@media (max-width: 900px) {{ .shell {{ grid-template-columns: minmax(0, 1fr); gap: 0; }} }}
header.cover {{ grid-column: 1 / -1; padding-block: 40px 28px; border-bottom: 1px solid var(--line); display: flex; flex-wrap: wrap; gap: 16px 40px; align-items: flex-end; justify-content: space-between; }}
.eyebrow {{ font-family: var(--f-mono); font-size: 12px; letter-spacing: .12em; text-transform: uppercase; color: var(--muted); margin: 0 0 6px; }}
header h1 {{ font-family: var(--f-display); font-weight: 700; font-size: clamp(34px, 6vw, 58px); line-height: 1; margin: 0; letter-spacing: -.01em; text-wrap: balance; }}
header h1 .six {{ color: var(--six); }} header h1 .nine {{ color: var(--nine); }}
.tagline {{ margin: 12px 0 0; color: var(--muted); max-width: 62ch; font-style: italic; }}
dl.meta {{ display: grid; grid-template-columns: auto auto; gap: 4px 16px; margin: 0; font-size: 13px; }}
dl.meta dt {{ color: var(--muted); }} dl.meta dd {{ margin: 0; font-family: var(--f-mono); font-variant-numeric: tabular-nums; }}
.legend {{ grid-column: 1 / -1; display: flex; flex-wrap: wrap; gap: 8px 18px; align-items: center; padding-block: 14px; font-size: 13px; color: var(--muted); border-bottom: 1px solid var(--line); }}
.legend a {{ color: var(--fg); }}
nav.toc {{ position: sticky; top: env(safe-area-inset-top, 0px); align-self: start; max-height: 100vh; overflow-y: auto; padding-block: 24px; }}
nav.toc details summary {{ cursor: pointer; font-size: 12px; letter-spacing: .1em; text-transform: uppercase; color: var(--muted); font-weight: 600; list-style: none; }}
nav.toc ol {{ list-style: none; margin: 10px 0 0; padding: 0; display: flex; flex-direction: column; gap: 2px; }}
nav.toc a {{ display: block; padding: 4px 8px; border-radius: 4px; color: var(--muted); text-decoration: none; font-size: 13.5px; line-height: 1.35; }}
nav.toc a:hover, nav.toc a.on {{ color: var(--fg); background: var(--sunk); }}
@media (max-width: 900px) {{ nav.toc {{ position: static; max-height: none; padding-block: 16px 0; }} }}
main {{ padding-block: 8px 96px; min-width: 0; }}
main > * {{ max-width: 78ch; }}
main > .frame {{ max-width: 100%; }}
h2 {{ font-family: var(--f-display); font-weight: 700; font-size: 28px; line-height: 1.2; margin: 56px 0 12px; padding-top: 18px; border-top: 1px solid var(--line); text-wrap: balance; scroll-margin-top: 16px; }}
h3 {{ font-family: var(--f-display); font-weight: 500; font-size: 20px; margin: 30px 0 8px; scroll-margin-top: 16px; }}
p, ul, ol {{ margin: 10px 0; }}
li {{ margin: 3px 0; }}
hr {{ display: none; }}
strong {{ font-weight: 600; }}
code {{ font-family: var(--f-mono); font-size: .9em; background: var(--sunk); padding: 1px 5px; border-radius: 3px; }}
a {{ color: var(--accent); }}
del {{ color: var(--muted); }}
.frame {{ overflow-x: auto; margin: 14px 0; border: 1px solid var(--line); border-radius: 6px; background: var(--surface); }}
table {{ border-collapse: collapse; width: 100%; font-size: 13.5px; font-variant-numeric: tabular-nums; }}
th, td {{ text-align: left; vertical-align: top; padding: 7px 10px; border-bottom: 1px solid var(--line); }}
th {{ background: var(--sunk); font-size: 12px; color: var(--muted); font-weight: 600; white-space: nowrap; }}
tr:last-child td {{ border-bottom: 0; }}
pre {{ margin: 0; padding: 14px; font-family: var(--f-mono); font-size: 12.5px; line-height: 1.45; }}
pre code {{ background: none; padding: 0; }}
.tag {{ display: inline-block; font-family: var(--f-mono); font-size: 10.5px; font-weight: 500; letter-spacing: .04em; text-transform: uppercase; padding: 0 6px; border-radius: 3px; vertical-align: 1px; margin: 0 2px; white-space: nowrap; }}
.tag.k {{ background: var(--k-bg); color: var(--k-fg); }} .tag.o {{ background: var(--o-bg); color: var(--o-fg); }}
.tag-note {{ font-size: 12px; color: var(--muted); margin-right: 2px; }}
:focus-visible {{ outline: 2px solid var(--accent); outline-offset: 2px; }}
</style>

<div class="shell">
  <header class="cover">
    <div>
      <p class="eyebrow">Game design document · Epic MegaJam 2026 · Arfdev</p>
      <h1>Village Headman</h1>
      <p class="tagline">Two brothers found a coin. One says <span style="color:var(--six)">six</span>. One says <span style="color:var(--nine)">nine</span>. Run your half of the village without starving, revolting, or getting couped.</p>
    </div>
    <dl class="meta">
      <dt>Takım</dt><dd>Arfdev</dd>
      <dt>Motor</dt><dd>Unreal Engine 5</dd>
      <dt>Teslim</dt><dd>16.11.2026 04:59 TR</dd>
      <dt>Güncelleme</dt><dd>{stamp}</dd>
    </dl>
  </header>
  <div class="legend">
    <span><span class="tag k">Karar</span> kullanıcının kararı</span>
    <span><span class="tag o">Öneri</span> önerilen değer, oynarken değiştirilebilir</span>
    <span>Kaynak: <code>GDD.md</code> · <a href="https://github.com/justbiar/village-headman" target="_blank" rel="noopener">GitHub reposu</a> · <a href="https://claude.ai/artifact/4ihHVnny12mPr3NtRxnRB2" target="_blank" rel="noopener">Tasarım masası</a></span>
  </div>
  <nav class="toc" aria-label="İçindekiler">
    <details open><summary>İçindekiler</summary><ol>
{toc}
    </ol></details>
  </nav>
  <main>
{body}
  </main>
</div>
<script>
(() => {{
  const links = [...document.querySelectorAll('nav.toc a')];
  const map = new Map(links.map(a => [a.getAttribute('href').slice(1), a]));
  const heads = [...document.querySelectorAll('main h2[id]')];
  if (!('IntersectionObserver' in window)) return;
  const io = new IntersectionObserver(es => {{
    es.forEach(e => {{ if (e.isIntersecting) {{ links.forEach(l => l.classList.remove('on')); map.get(e.target.id)?.classList.add('on'); }} }});
  }}, {{ rootMargin: '0px 0px -70% 0px' }});
  heads.forEach(h => io.observe(h));
  if (window.matchMedia('(max-width: 900px)').matches) document.querySelector('nav.toc details').open = false;
}})();
</script>
"""
open(out, "w", encoding="utf-8").write(page)
print(len(page), "bytes,", len(toc_items), "sections")
