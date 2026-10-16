Use [`sledge.register_file`](../../../api/lua/namespaces.sledge.md#register_file) and [`sledge.register_packfile`](../../../api/lua/namespaces.sledge.md#register_packfile) to add new files or replace existing ones.

!!! warning

    Do not use file overrides for `.xtbl` files, as this causes conflicts between mods. Use [`sledge.register_xml_edit`](editing-xml-files.md) instead.

!!! info "Call at the root level"

    Always place these functions at the root level of `mod.lua`, outside of any event callback, so Sledge registers it immediately at launch.

## Registering a file

[`sledge.register_file`](../../../api/lua/namespaces.sledge.md#register_file) adds or replaces a single file using its path relative to your mod folder.

```
📁 mods/
└── 📁 my_name.no_tutorial/
    ├── 📁 files/
    │   └── 📄 terr01_tutorial.scriptx
    ├── 📄 mod.toml
    └── 📄 mod.lua
```

```lua title="mod.lua"
sledge.register_file("files/terr01_tutorial.scriptx")
```

## Registering a packfile

[`sledge.register_packfile`](../../../api/lua/namespaces.sledge.md#register_packfile) handles `.vpp_pc` archives, replacing or adding every internal file inside them at once.

```
📁 mods/
└── 📁 my_name.my_mod/
    ├── 📁 files/
    │   └── 📄 custom.vpp_pc
    ├── 📄 mod.toml
    └── 📄 mod.lua
```

```lua title="mod.lua"
sledge.register_packfile("files/custom.vpp_pc")
```

!!! info

    Files registered via `sledge.register_file` take precedence over files registered with `sledge.register_packfile`, even if the packfile was registered later. This behavior is likely to change in the future.
