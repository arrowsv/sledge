A mod is a folder inside the `mods` folder containing a `mod.toml` (metadata) and a `mod.lua` (script).

## Create the folder

Create a folder inside `mods` named `author.name` (using only lowercase letters `a-z`, numbers `0-9`, and underscores `_`, e.g., `my_name.my_mod`).

While this specific folder name isn't strictly required, it should match the metadata's `id` field for the sake of consistency. Ensure it is correctly formatted.

## Create the files

- The `mod.toml` file contains your mod's metadata, such as its name, version, and options.
- The `mod.lua` file is the main script Sledge runs when the game launches.

```
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
api_version = "1.1.0"
```

```lua title="mod.lua"
sledge.log("Hello from my mod!")
```

Enable the mod in the launcher, launch the game, and check the `sledge.log` file to verify it loaded.

Next, check out the [metadata reference](../../api/metadata.md) and learn how to [write your script](script.md).