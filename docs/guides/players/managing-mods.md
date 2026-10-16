!!! warning "Legacy mods"

    Older `modinfo.xml` format mods do not appear in the Sledge launcher. See [Legacy mods](#legacy-mods) below.

## Install a mod

1.  Download a mod from the [FactionFiles Sledge category](https://www.factionfiles.com/ff.php?action=files&file_category=52).
2.  Unzip the folder (e.g., `my_name.my_mod`), ensuring it contains `mod.toml` and `mod.lua`.
3.  Move that folder into your `mods` directory:

    ```
    📁 mods/
    └── 📁 my_name.my_mod/
        ├── 📄 mod.toml
        └── 📄 mod.lua
    ```

    The `mods` folder is inside `sledge/`, or directly in the root folder if you used the alternative folder structure.

4.  Open the launcher and click `Mods` (if the launcher is already open, click `Rescan`). Check the mod's box, and click `Apply`.

!!! warning "Check for nested folders"

    Make sure the extracted mod isn't double-nested (e.g., `mods/mod/mod/mod.toml`). The inner folder must be moved up so `mod.toml` is right inside the mod's folder.

## Configure, update and remove

- **Configure** - In the launcher's `Mods` window, select the mod and adjust settings under the `Options` heading. Click `Apply` to save changes.
- **Update** - Download the newest version from FactionFiles and replace the old folder in `mods`. Delete the old folder first if you want to clear leftover files.
- **Remove** - Uncheck the mod in the launcher to disable it temporarily, or delete its folder from `mods` entirely.

## Legacy mods

- **Players** - Install older mods using [Mod Manager Re-Mars-tered v1.03](https://www.factionfiles.com/ff.php?action=file&id=5995) alongside Sledge.
- **Developers** - Convert your mods to the new format using the [Converting legacy mods](../developers/editing-files/legacy-mods.md) guide.
