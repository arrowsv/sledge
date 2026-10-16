The API is what your mod uses to communicate with Sledge and the game.

The current API version is `1.1.0`.

## Compatibility

Specify the API version your mod was built and tested for using the `api_version` field in `mod.toml`. Sledge uses this value to verify compatibility:

* **Compatible** - The major version matches Sledge's current version, and the minor version is equal to or lower. The mod loads normally.
* **Warning** - If the version numbers do not match these criteria, the launcher displays a warning icon because the mod may not function correctly.

!!! info

    Major API versions can be released with any Sledge update. Check the [API changelog](changelog.md) for details on changes, additions, and release versions.
