import sys
import tomllib
from dataclasses import dataclass, field
from pathlib import Path
from typing import Any, List, Optional

@dataclass
class ParameterDoc:
    name: str = ""
    type: str = ""
    description: str = ""
    optional: bool = False
    fields: List["ParameterDoc"] = field(default_factory=list)

@dataclass
class ReturnDoc:
    name: str = "result"
    type: str = ""
    description: str = ""

@dataclass
class FunctionDoc:
    name: str = ""
    description: str = ""
    parameters: List[ParameterDoc] = field(default_factory=list)
    returns: List[ReturnDoc] = field(default_factory=list)
    qualified_name: str = ""

@dataclass
class FieldDoc:
    name: str = ""
    type: str = ""
    description: str = ""
    qualified_name: str = ""

@dataclass
class TypeDoc:
    name: str = ""
    inherits: str = ""
    methods: List[FunctionDoc] = field(default_factory=list)
    fields: List[FieldDoc] = field(default_factory=list)

@dataclass
class DefineDoc:
    name: str = ""
    fields: List[FieldDoc] = field(default_factory=list)

@dataclass
class NamespaceDoc:
    name: str = ""
    functions: List[FunctionDoc] = field(default_factory=list)
    fields: List[FieldDoc] = field(default_factory=list)

types: List[TypeDoc] = []
defines: List[DefineDoc] = []
namespaces: List[NamespaceDoc] = []

def parse_field(tbl: dict[str, Any]) -> FieldDoc:
    return FieldDoc(
        name=tbl.get("name", ""),
        type=tbl.get("type", ""),
        description=tbl.get("description", "")
    )

def parse_fields(tbl: dict[str, Any]) -> List[FieldDoc]:
    return [parse_field(item) for item in tbl.get("fields", []) if isinstance(item, dict)]

def parse_parameter(tbl: dict[str, Any]) -> ParameterDoc:
    param = ParameterDoc(
        name=tbl.get("name", ""),
        type=tbl.get("type", ""),
        description=tbl.get("description", ""),
        optional=tbl.get("optional", False)
    )
    param.fields = [parse_parameter(item) for item in tbl.get("fields", []) if isinstance(item, dict)]
    return param

def parse_function(tbl: dict[str, Any]) -> FunctionDoc:
    func = FunctionDoc(
        name=tbl.get("name", ""),
        description=tbl.get("description", "")
    )

    for item in tbl.get("params", []):
        if isinstance(item, dict):
            func.parameters.append(parse_parameter(item))

    for item in tbl.get("returns", []):
        if isinstance(item, dict):
            func.returns.append(ReturnDoc(
                name=item.get("name", "result"),
                type=item.get("type", ""),
                description=item.get("description", "")
            ))

    return func

def parse_functions(tbl: dict[str, Any], key: str) -> List[FunctionDoc]:
    return [parse_function(item) for item in tbl.get(key, []) if isinstance(item, dict)]

def parse_toml(file_path: Path) -> None:
    try:
        with open(file_path, "rb") as f:
            tbl = tomllib.load(f)
    except Exception as e:
        print(f"Error: Failed to parse definition file {file_path}: {e}", file=sys.stderr)
        return

    for item in tbl.get("types", []):
        if isinstance(item, dict):
            types.append(TypeDoc(
                name=item.get("name", ""),
                inherits=item.get("inherits", ""),
                fields=parse_fields(item),
                methods=parse_functions(item, "methods")
            ))

    for item in tbl.get("defines", []):
        if isinstance(item, dict):
            defines.append(DefineDoc(
                name=item.get("name", ""),
                fields=parse_fields(item)
            ))

    for item in tbl.get("namespaces", []):
        if isinstance(item, dict):
            namespaces.append(NamespaceDoc(
                name=item.get("name", ""),
                fields=parse_fields(item),
                functions=parse_functions(item, "functions")
            ))

def assign_qualified_names() -> None:
    for t in types:
        path = f"types.{t.name}"
        for f in t.fields:
            f.qualified_name = f"{path}.{f.name}"
        for m in t.methods:
            m.qualified_name = f"{path}:{m.name}"

    for d in defines:
        for f in d.fields:
            f.qualified_name = f"defines.{d.name}.{f.name}"

    for ns in namespaces:
        for f in ns.fields:
            f.qualified_name = f"{ns.name}.{f.name}"
        for func in ns.functions:
            func.qualified_name = f"{ns.name}.{func.name}"

def write_field(file, field_obj: FieldDoc) -> None:
    file.write(f"### `{field_obj.name}`\n\n")
    file.write(f"Type: `{field_obj.type}`\n\n")
    if field_obj.description:
        file.write(f"{field_obj.description}\n\n")

def write_fields(file, fields_list: List[FieldDoc]) -> None:
    if not fields_list:
        return

    file.write("## Fields\n\n")
    for i, field_obj in enumerate(fields_list):
        if i > 0:
            file.write("---\n\n")
        write_field(file, field_obj)

def write_parameter(file, param: ParameterDoc, depth: int = 0) -> None:
    indent = "  " * depth
    opt = ", optional" if param.optional else ""
    desc = f" - {param.description}" if param.description else ""

    file.write(f"{indent}* `{param.name}` (`{param.type}`{opt}){desc}\n")

    for f_param in param.fields:
        write_parameter(file, f_param, depth + 1)

def write_function(file, func: FunctionDoc) -> None:
    file.write(f"### `{func.name}`\n\n")

    if func.description:
        file.write(f"{func.description}\n\n")

    file.write("```lua\n")

    if func.returns:
        returns_str = ", ".join(r.name for r in func.returns)
        file.write(f"local {returns_str} = ")

    params_str = ", ".join(f"{p.name}?" if p.optional else p.name for p in func.parameters)
    file.write(f"{func.qualified_name}({params_str})\n```\n\n")

    if func.parameters:
        file.write("**Parameters**\n\n")
        for param in func.parameters:
            write_parameter(file, param, depth=0)
        file.write("\n")

    if func.returns:
        file.write("**Returns**\n\n")
        for ret in func.returns:
            desc = f" - {ret.description}" if ret.description else ""
            file.write(f"* `{ret.name}` (`{ret.type}`){desc}\n")
        file.write("\n")

def write_functions(file, heading: str, functions_list: List[FunctionDoc]) -> None:
    if not functions_list:
        return

    file.write(f"## {heading}\n\n")
    for i, func in enumerate(functions_list):
        if i > 0:
            file.write("---\n\n")
        write_function(file, func)

def write_types(api_dir: Path) -> None:
    if not types:
        return

    dir_path = api_dir / "types"
    dir_path.mkdir(parents=True, exist_ok=True)

    for t in types:
        with open(dir_path / f"{t.name}.md", "w", encoding="utf-8") as f:
            f.write(f"# types.{t.name}\n\n")

            if t.inherits:
                f.write(f"> Inherits from [`types.{t.inherits}`]({t.inherits}.md)\n\n")

            write_fields(f, t.fields)
            write_functions(f, "Methods", t.methods)

def write_defines(api_dir: Path) -> None:
    if not defines:
        return

    dir_path = api_dir / "defines"
    dir_path.mkdir(parents=True, exist_ok=True)

    for d in defines:
        with open(dir_path / f"{d.name}.md", "w", encoding="utf-8") as f:
            f.write(f"# defines.{d.name}\n\n")
            write_fields(f, d.fields)

def write_namespaces(api_dir: Path) -> None:
    for ns in namespaces:
        with open(api_dir / f"{ns.name}.md", "w", encoding="utf-8") as f:
            f.write(f"# {ns.name}\n\n")
            write_fields(f, ns.fields)
            write_functions(f, "Functions", ns.functions)

def build_sidebar_block() -> str:
    lines = [
        "# API start",
        "- Lua"
    ]

    if types:
        lines.append("  - Types")
        for t in types:
            lines.append(f"    - [{t.name}]({t.name}.md)")
            #lines.append(f"    - [{t.name}](lua/api/types/{t.name}.md)")

    if defines:
        lines.append("  - Defines")
        for d in defines:
            lines.append(f"    - [{t.name}]({t.name}.md)")
            #lines.append(f"    - [{d.name}](lua/api/defines/{d.name}.md)")

    if namespaces:
        lines.append("  - Namespaces")
        for ns in namespaces:
            lines.append(f"    - [{t.name}]({t.name}.md)")
            #lines.append(f"    - [{ns.name}](lua/api/{ns.name}.md)")

    lines.append("# API end\n")
    return "\n".join(lines)

def write_sidebar(output_path: Path) -> None:
    sidebar_path = output_path / "_sidebar.md"

    existing = ""
    if sidebar_path.exists():
        existing = sidebar_path.read_text(encoding="utf-8")

    start_marker = "# API start"
    end_marker = "# API end"
    block = build_sidebar_block()

    start_pos = existing.find(start_marker)
    end_pos = existing.find(end_marker)

    if start_pos != -1 and end_pos != -1 and end_pos > start_pos:
        result = existing[:start_pos] + block + existing[end_pos + len(end_marker):]
    else:
        result = existing
        if result and not result.endswith("\n"):
            result += "\n"
        if result:
            result += "\n"
        result += block

    sidebar_path.write_text(result, encoding="utf-8")

def write_docs(output_path: Path) -> None:
    api_dir = output_path / "lua" / "api"
    api_dir.mkdir(parents=True, exist_ok=True)

    write_types(api_dir)
    write_defines(api_dir)
    write_namespaces(api_dir)
    #write_sidebar(output_path)

def parse_api(api_path: Path, output_path: Path) -> None:
    for file_path in api_path.rglob("*.toml"):
        parse_toml(file_path)

    assign_qualified_names()
    write_docs(output_path)

def main():
    api_path = Path.cwd() / "_sources"
    output_path = Path.cwd()

    parse_api(api_path, output_path)

if __name__ == "__main__":
    main()
