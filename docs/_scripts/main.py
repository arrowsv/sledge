import sys
import tomllib

from pathlib import Path
from typing import Any, List

from classes import DefineDoc, FieldDoc, FunctionDoc, NamespaceDoc, ParameterDoc, ReturnDoc, TypeDoc, EventDoc, EventDataDoc
from globals import defines, types, namespaces, events
from utils import format_type_links, assign_qualified_names_and_sort

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

def parse_event_data(tbl: dict[str, Any]) -> EventDataDoc:
    return EventDataDoc(
            name=tbl.get("name", ""),
            type=tbl.get("type", ""),
            description=tbl.get("description", "")
        )

def parse_event_data_list(tbl: dict[str, Any]) -> List[EventDataDoc]:
    return [parse_event_data(item) for item in tbl.get("data", []) if isinstance(item, dict)] 

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
                functions=parse_functions(item, "functions"),
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

    for item in tbl.get("events", []):
            if isinstance(item, dict):
                events.append(EventDoc(
                    name=item.get("name", ""),
                    description=item.get("description", ""),
                    data=parse_event_data_list(item)
                ))

def write_field(file, field_obj: FieldDoc) -> None:
    file.write(f"### `{field_obj.name}`\n\n")

    if field_obj.description:
        file.write(f"{field_obj.description}\n\n")

    formatted_type = format_type_links(field_obj.type)
    file.write("**Returns**\n\n")
    file.write(f"* `result` ({formatted_type})\n\n")

def write_fields(file, fields_list: List[FieldDoc]) -> None:
    if not fields_list:
        return

    file.write("## Fields\n\n")
    for i, field_obj in enumerate(fields_list):
        if i > 0:
            file.write("---\n\n")
        write_field(file, field_obj)

def write_parameter(file, param: ParameterDoc, depth: int = 0) -> None:
    indent = "    " * depth
    opt = ", optional" if param.optional else ""
    desc = f" - {param.description}" if param.description else ""

    formatted_type = format_type_links(param.type)
    file.write(f"{indent}* `{param.name}` ({formatted_type}{opt}){desc}\n")

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
            formatted_type = format_type_links(ret.type)
            file.write(f"* `{ret.name}` ({formatted_type}){desc}\n")
        file.write("\n")

def write_functions(file, heading: str, functions_list: List[FunctionDoc]) -> None:
    if not functions_list:
        return

    file.write(f"## {heading}\n\n")
    for i, func in enumerate(functions_list):
        if i > 0:
            file.write("---\n\n")
        write_function(file, func)

def write_event_data(file, event_data: EventDataDoc) -> None:
    formatted_type = format_type_links(event_data.type)
    file.write(f"* `{event_data.name}` ({formatted_type})\n")

def write_events(lua_dir: Path) -> None:
    if not events:
        return

    dir_path = lua_dir / "events"
    dir_path.mkdir(parents=True, exist_ok=True)

    for e in events:
        with open(dir_path / f"{e.name}.md", "w", encoding="utf-8") as f:
            f.write(f"# {e.name}\n\n")

            if e.description:
                f.write(f"{e.description}\n\n")

            data_parameter = "data" if e.data else ""

            f.write("```lua\n")
            f.write(f"local function {e.name}_callback({data_parameter})\nend\n\n")
            f.write(f"sledge.register_event(defines.event.{e.name}, {e.name}_callback)\n")
            f.write("```\n\n")

            if e.data:
                f.write("## Event data\n\n")
                for e_data in e.data:
                    write_event_data(f, e_data)

            
def write_types(lua_dir: Path) -> None:
    if not types:
        return

    dir_path = lua_dir / "api" / "types"
    dir_path.mkdir(parents=True, exist_ok=True)

    for t in types:
        with open(dir_path / f"{t.name}.md", "w", encoding="utf-8") as f:
            f.write(f"# types.{t.name}\n\n")

            if t.inherits:
                formatted_inherits = format_type_links(t.inherits)
                f.write(f"> Inherits from: {formatted_inherits}\n\n")

            write_fields(f, t.fields)
            write_functions(f, "Functions", t.functions)
            write_functions(f, "Methods", t.methods)

def write_defines(lua_dir: Path) -> None:
    if not defines:
        return

    dir_path = lua_dir / "api" / "defines"
    dir_path.mkdir(parents=True, exist_ok=True)

    for d in defines:
        with open(dir_path / f"{d.name}.md", "w", encoding="utf-8") as f:
            f.write(f"# defines.{d.name}\n\n")
            write_fields(f, d.fields)

def write_namespaces(lua_dir: Path) -> None:
    for ns in namespaces:
        with open(lua_dir / "api" / f"{ns.name}.md", "w", encoding="utf-8") as f:
            f.write(f"# {ns.name}\n\n")
            write_fields(f, ns.fields)
            write_functions(f, "Functions", ns.functions)

def write_docs(output_path: Path) -> None:
    lua_dir = output_path / "lua"
    lua_dir.mkdir(parents=True, exist_ok=True)

    write_types(lua_dir)
    write_defines(lua_dir)
    write_namespaces(lua_dir)
    write_events(lua_dir)

def parse_api(api_path: Path, output_path: Path) -> None:
    for file_path in api_path.rglob("*.toml"):
        parse_toml(file_path)

    assign_qualified_names_and_sort()

    write_docs(output_path)

def main():
    output_path = Path.cwd().parent
    api_path = output_path / "_sources"

    parse_api(api_path, output_path)

if __name__ == "__main__":
    main()
