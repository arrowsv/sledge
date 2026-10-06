from globals import types, defines, namespaces


def assign_qualified_names_and_sort() -> None:
    for t in types:
        path = f"types.{t.name}"
        for f in t.fields:
            f.qualified_name = f"{path}.{f.name}"
        for m in t.functions:
            m.qualified_name = f"{path}.{m.name}"
        for m in t.methods:
            m.qualified_name = f"object:{m.name}"
        t.fields.sort(key=lambda f: f.name)
        t.functions.sort(key=lambda f: f.name)
        t.methods.sort(key=lambda m: m.name)

    for d in defines:
        for f in d.fields:
            f.qualified_name = f"defines.{d.name}.{f.name}"

    for ns in namespaces:
        for f in ns.fields:
            f.qualified_name = f"{ns.name}.{f.name}"
        for func in ns.functions:
            func.qualified_name = f"{ns.name}.{func.name}"
        ns.fields.sort(key=lambda f: f.name)
        ns.functions.sort(key=lambda f: f.name)

def format_type_links(type_str: str) -> str:
    if not type_str:
        return ""

    is_array = type_str.endswith("[]")
    is_table = type_str.startswith("table<") and type_str.endswith(">")

    if is_array:
        type_str = type_str[:-2]

    if is_table:
        type_str = type_str[6:]
        type_str = type_str[:-1]

    tokens = type_str.split("|")
    
    formatted_tokens = ["<code>"]
    for i, token in enumerate(tokens):
        if i > 0:
            formatted_tokens.append(", ")
        else:
            if is_table:
                formatted_tokens.append("table&lt;")

        if token.startswith("types."):
            parts = token.split(".")
            type_name = parts[1] if len(parts) > 1 else token
            formatted_tokens.append(f"[{token}](/lua/api/types/{type_name})")

        elif token.startswith("defines."):
            parts = token.split(".")
            define_name = parts[1] if len(parts) > 1 else token
            formatted_tokens.append(f"[{token}](/lua/api/defines/{define_name})")

        else:
            formatted_tokens.append(f"{token}")

        # TODO: check and link Lua standard types to the manual too.

    if is_table:
        formatted_tokens.append(">")
    elif is_array:
        formatted_tokens.append("[]")

    formatted_tokens.append("</code>")
    return "".join(formatted_tokens)