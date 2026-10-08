import re
import tomllib
from pathlib import Path


def link(t: str) -> str:
    t = t.replace("<", "&lt;").replace(">", "&gt;")
    t = re.sub(r"\b(types|defines)\.(\w+)", r"[\g<0>](\1.\2.md)", t)
    return f"<code>{t}</code>"


def params(items, depth=0):
    lines = []
    for p in items:
        opt = " <small>optional</small>" if p.get("optional") else ""
        desc = f" - {p['description']}" if p.get("description") else ""
        lines.append(f"{'    ' * depth}* `{p['name']}` ({link(p.get('type', ''))}){opt}{desc}")
        lines += params(p.get("fields", []), depth + 1)
    return lines


def field(f):
    parts = [f.get("description", ""),
             "**Returns**", f"* `result` ({link(f.get('type', ''))})"]
    return "\n\n".join(p for p in parts if p)


def function(f, call_name):
    ps, rets = f.get("params", []), f.get("returns", [])
    args = ", ".join(p["name"] + ("?" if p.get("optional") else "") for p in ps)
    call = f"{call_name}({args})"
    if rets:
        call = f"local {', '.join(r.get('name', 'result') for r in rets)} = {call}"
    parts = [f.get("description", ""), f"```lua\n{call}\n```"]
    if ps:
        parts += ["**Parameters**", "\n".join(params(ps))]
    if rets:
        parts += ["**Returns**", "\n".join(params([{"name": "result", **r} for r in rets]))]
    return "\n\n".join(p for p in parts if p)


def section(title, items, render, sort=True):
    if not items:
        return ""
    if sort:
        items = sorted(items, key=lambda i: i["name"])

    # Group by name: one heading, then every body with that name, divided by ---
    bodies = {}
    for i in items:
        bodies.setdefault(i["name"], []).append(render(i))

    entries = [f"### `{name}`\n\n" + "\n\n---\n\n".join(group) for name, group in bodies.items()]
    return f"## {title}\n\n" + "\n\n---\n\n".join(entries)


def write(out: Path, name: str, *parts):
    text = "\n\n".join(p for p in parts if p) + "\n"
    (out / f"{name}.md").write_text(text, encoding="utf-8")


def main():
    root = Path.cwd().parent
    out = root / "lua" / "api"
    out.mkdir(parents=True, exist_ok=True)

    for path in (root / "_sources").rglob("*.toml"):
        doc = tomllib.loads(path.read_text(encoding="utf-8"))

        for t in doc.get("types", []):
            n = t["name"]
            write(out, f"types.{n}", f"# types.{n}",
                  f"> Inherits from: {link(t['inherits'])}" if t.get("inherits") else "",
                  section("Fields", t.get("fields", []), field),
                  section("Functions", t.get("functions", []), lambda f: function(f, f"types.{n}.{f['name']}")),
                  section("Methods", t.get("methods", []), lambda f: function(f, f"object:{f['name']}")))

        for d in doc.get("defines", []):
            n = d["name"]
            write(out, f"defines.{n}", f"# defines.{n}",
                  section("Fields", d.get("fields", []), field, sort=False))

        for ns in doc.get("namespaces", []):
            n = ns["name"]
            write(out, f"namespaces.{n}", f"# {n}",
                  section("Fields", ns.get("fields", []), field),
                  section("Functions", ns.get("functions", []), lambda f: function(f, f"{n}.{f['name']}")))

        for e in doc.get("events", []):
            n = e["name"]
            arg = "data" if e.get("data") else ""
            code = (f"```lua\nlocal function {n}_callback({arg})\nend\n\n"
                    f"sledge.register_event(defines.event.{n}, {n}_callback)\n```")
            write(out, f"events.{n}", f"# {n}", e.get("description", ""), code,
                  "## Event data\n\n" + "\n".join(params(e["data"])) if e.get("data") else "")


if __name__ == "__main__":
    main()