The API is what your mod uses to communicate with Sledge and the game. It has two parts:

- The [metadata file](metadata.md) tells Sledge about your mod and what the script requires.
- The Lua scripting API, which contains the functions, types, enums, and events your script can use.

## API version

The current API version is `1.0.0`.

Your mod declares the API version it was written and tested for with the `api_version` field in `mod.toml`. Sledge uses it to check whether your mod is compatible:

- If the mod's major number matches Sledge's and its minor number is equal or lower, the mod loads as usual.
- Otherwise, the launcher shows a warning icon next to the mod, since it may not work correctly.

A new major version can be released with any Sledge version. See the [API changelog](changelog.md) for what each version added, changed, or removed, and which Sledge release provides it.
