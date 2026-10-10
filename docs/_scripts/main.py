import re
import textwrap
import tomllib
from pathlib import Path


def link(t: str) -> str:
    t = t.replace("<", "&lt;").replace(">", "&gt;")
    return re.sub(r"\b(types|enums)\.(\w+)", r"[\g<0>](\1.\2.md)", t)


def params(items, depth=0):
    lines = []
    for p in items:
        opt = " <small>optional</small>" if p.get("optional") else ""
        desc = f" - {p['description']}" if p.get("description") else ""
        lines.append(f"{'    ' * depth}* `{p['name']}` (<code>{link(p.get('type', ''))}</code>){opt}{desc}")
        lines += params(p.get("fields", []), depth + 1)
    return lines


def indent(text: str) -> str:
    lines = text.strip().split("\n")
    rest = ["    " + line if line else "" for line in lines[1:]]
    return "\n".join([":   \n    " + lines[0]] + rest)


def property(f):
    return link(f.get("type", "")), textwrap.dedent(f.get("description", "")).strip()


def function(f, call_name):
    ps, rets = f.get("params", []), f.get("returns", [])
    args = ", ".join(p["name"] + ("?" if p.get("optional") else "") for p in ps)
    call = f"{call_name}({args})"
    if rets:
        call = f"local {', '.join(r.get('name', 'result') for r in rets)} = {call}"

    parts = [textwrap.dedent(f.get("description", "")).strip(), f"```lua\n{call}\n```"]
    if ps:
        parts += ["**Parameters**", "\n".join(params(ps))]

    heading_returns = ", ".join(
        f"{r['name']} ({link(r['type'])})" if r.get("name") else link(r["type"]) for r in rets
    )
    return heading_returns, "\n\n".join(p for p in parts if p)


def section(title, items, render, sort=True):
    if not items:
        return ""
    if sort:
        items = sorted(items, key=lambda i: i["name"])

    entries = []
    for i in items:
        returns, body = render(i)
        name = i["name"]

        heading = f"### <small><code>{name}</code></small>"
        if returns:
            heading += f" <small>:lucide-move-right: <code>{returns}</code></small>"
        heading += f' {{ #{name} data-toc-label="{name}" }}'

        entries.append(heading + "\n\n" + indent(body))

    return f"## {title}\n\n" + "\n\n---\n\n".join(entries)


def write(out: Path, name: str, *parts):
    text = "\n\n".join(p for p in parts if p) + "\n"
    (out / f"{name}.md").write_text(text, encoding="utf-8")


def main():
    root = Path.cwd().parent
    out = root / "api" / "lua"
    out.mkdir(parents=True, exist_ok=True)

    for path in (root / "_sources").rglob("*.toml"):
        doc = tomllib.loads(path.read_text(encoding="utf-8"))

        for t in doc.get("types", []):
            n = t["name"]
            write(out, f"types.{n}", f"# types.{n}",
                  f"!!! info \"This type inherits {link(t['inherits'])}.\"" if t.get("inherits") else "",
                  section("Properties", t.get("properties", []), property),
                  section("Functions", t.get("functions", []), lambda f: function(f, f"types.{n}.{f['name']}")),
                  section("Methods", t.get("methods", []), lambda f: function(f, f"object:{f['name']}")))

        for d in doc.get("enums", []):
            n = d["name"]
            write(out, f"enums.{n}", f"# enums.{n}",
                  section("Fields", d.get("fields", []), property, sort=False))

        for ns in doc.get("namespaces", []):
            n = ns["name"]
            write(out, f"namespaces.{n}", f"# {n}",
                  section("Properties", ns.get("properties", []), property),
                  section("Functions", ns.get("functions", []), lambda f: function(f, f"{n}.{f['name']}")))

        for e in doc.get("events", []):
            n = e["name"]
            arg = "data" if e.get("data") else ""
            code = (f"```lua\nlocal function {n}_callback({arg})\nend\n\n"
                    f"sledge.register_event(enums.event.{n}, {n}_callback)\n```")
            write(out, f"events.{n}", f"# {n}", e.get("description", ""), code,
                  "## Event data\n\n" + "\n".join(params(e["data"])) if e.get("data") else "")


if __name__ == "__main__":
    main()