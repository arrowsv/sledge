A mod is a folder inside the `mods` folder, containing two files that tell Sledge what your mod is and what it does.

## Create the folder

Create a folder inside `mods` named `author.name`, where both parts use only lowercase letters `a-z`, numbers `0-9`, and underscores `_`. For example: `my_name.my_mod`.

This name should match the `id` field you set in the `mod.toml` file later, so make sure it's correctly formatted.

## Create the files

Inside the new folder, create two files:

- [`mod.toml`](metadata.md) contains your mod's metadata, such as its name, version, and options.
- [`mod.lua`](script.md) is the script Sledge runs to load your mod.

```text
📁 mods/
└── 📁 my_name.my_mod/
    ├── 📄 mod.toml
    └── 📄 mod.lua
```

## Sample

To check that everything works, add this to each file:

```toml title="mod.toml"
id = "my_name.my_mod"
name = "My Mod"
authors = ["My Name"]
version = "1.0.0"
sledge_version = ">=0.1.0"
```

```lua title="mod.lua"
sledge.log("Hello from my mod!")
```

Enable the mod in the launcher, then launch the game and look for the message in the `sledge.log` file. If it's there, your mod is loaded.

## Next steps

Continue to [`mod.toml`](metadata.md) to learn about the metadata fields, then [`mod.lua`](script.md) to start scripting.