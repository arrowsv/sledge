# Overriding files

Use the [`sledge.register_file`](../lua/api/sledge.md#register_file) and [`sledge.register_packfile`](../lua/api/sledge.md#register_packfile) functions to add or override files. These are akin to the `<Replace>` feature from the `modinfo.xml` format.

These functions should be written at the root level of a script to ensure it is called immediately by Sledge at launch. While it is technically possible for these functions to be be called later, its results can be unpredictable.

!!! warning

    Overriding `.xtbl` files will cause compatibility issues between mods that override the same file and result in edits being overwritten. Instead, use the [`sledge.register_xml_edit`](editing-xml-files.md) function.

### Registering a file

The [`sledge.register_file`](../lua/api/sledge.md#register_file) function will add a new file or override an existing file if its name already exists in the game. Use the function by placing the file inside the mod's folder and pass the relative path to the function.

To demonstrate, we will use the `No Tutorial` mod that replaces a `.scriptx` file:

```
📁 mods/
└── 📁 No Tutorial/
    ├── 📁 files/
    │   └── 📄 terr01_tutorial.scriptx
    ├── 📄 mod.toml
    └── 📄 mod.lua
```

```lua title="mod.lua"
sledge.register_file("files/terr01_tutorial.scriptx")
```

!!! info

    If a file is registered with a name that does not already exist in the game, it is considered "added", but it won't be used unless the game explicitly looks for a file with that name.

### Registering a packfile

The [`sledge.register_packfile`](../lua/api/sledge.md#register_packfile) function is identical to `sledge.register_file` but only allows `.vpp_pc` files. All files within the packfile will be added or override any existing files. For example:

```
📁 mods/
└── 📁 My Mod/
    ├── 📁 files/
    │   └── 📄 custom.vpp_pc
    ├── 📄 mod.toml
    └── 📄 mod.lua
```

```lua title="mod.lua"
sledge.register_packfile("files/custom.vpp_pc")
```

!!! info

    Files registered with `sledge.register_file` always take precedence over ones registered with `sledge.register_packfile`, even if the packfile was registered after. This may change in the future.
