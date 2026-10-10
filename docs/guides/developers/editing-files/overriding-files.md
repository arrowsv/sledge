Use the [`sledge.register_file`](../../../api/lua/namespaces.sledge.md#register_file) and [`sledge.register_packfile`](../../../api/lua/namespaces.sledge.md#register_packfile) functions to add new files to the game or replace existing ones. If you're coming from the `modinfo.xml` format, these take the place of `<Replace>`.

!!! warning

    Overriding `.xtbl` files causes compatibility issues between mods that override the same file, because one mod's edits will overwrite the other's. Use [`sledge.register_xml_edit`](editing-xml-files.md) instead.

!!! info "Call these functions at the root level"

    Write these functions at the root level of `mod.lua`, not inside an event callback, so Sledge calls them immediately at launch. Calling them later is technically possible, but the results can be unpredictable.

## Registering a file

The [`sledge.register_file`](../../../api/lua/namespaces.sledge.md#register_file) function adds a new file, or replaces an existing file if one with the same name already exists in the rfg.

To use it, place the file inside your mod's folder and pass its path relative to the mod's folder to the function. The `files` folder in the example below is only for organization, and you can name it whatever you like.

To demonstrate, here is a mod named `my_name.no_tutorial` that replaces a `.scriptx` file:

``` text
📁 mods/
└── 📁 my_name.no_tutorial/
    ├── 📁 files/
    │   └── 📄 terr01_tutorial.scriptx
    ├── 📄 mod.toml
    └── 📄 mod.lua
```

``` lua title="mod.lua"
sledge.register_file("files/terr01_tutorial.scriptx")
```

!!! info

    If a file is registered with a name that doesn't exist in the game, it is considered "added". It won't be used unless the game explicitly looks for a file with that name.

## Registering a packfile

The [`sledge.register_packfile`](../../../api/lua/namespaces.sledge.md#register_packfile) function works like `sledge.register_file`, but only accepts `.vpp_pc` files. Every file inside the packfile is added to the game, or replaces the existing file with the same name.

``` text
📁 mods/
└── 📁 my_name.my_mod/
    ├── 📁 files/
    │   └── 📄 custom.vpp_pc
    ├── 📄 mod.toml
    └── 📄 mod.lua
```

``` lua title="mod.lua"
sledge.register_packfile("files/custom.vpp_pc")
```

!!! info

    Files registered with `sledge.register_file` always take precedence over files registered with `sledge.register_packfile`, even if the packfile was registered later. This behavior is likely to change in the future.
