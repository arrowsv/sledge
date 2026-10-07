Mods for Sledge are folders that you place inside the `mods` folder. Once a mod is there, you can enable it in the launcher.

This page assumes you've already [installed Sledge](installing-sledge.md).

!!! warning "Legacy mods"

     Mods in the older `modinfo.xml` format don't appear in the launcher. See [Legacy mods](#legacy-mods) for more information.

## Install a mod

1. Mods for Sledge can be found in the `Mods - Remaster (Sledge)` category on [FactionFiles](https://www.factionfiles.com/ff.php?action=files&file_category=52). Download the mod, which should be a `.zip` or `.7z` file.

2. Extract the archive. The result should be a folder named after the mod, such as `my_name.my_mod`, containing a `mod.toml` file, a `mod.lua` file, and any extra files that the mod needs.

3. Move that folder into the `mods` folder:

    ```text
    📁 mods/
    └── 📁 my_name.my_mod/
        ├── 📄 mod.toml
        └── 📄 mod.lua
    ```

    The `mods` folder is next to `launcher.exe`. This is inside the `sledge` folder by default, or directly in the game's root folder if you used the alternative layout.

4. Open the launcher and click the `Mods` button. If the launcher was already open, click `Rescan` so it finds the new folder.

5. Click the checkbox next to the mod's name to enable it, then click `Apply`.

!!! warning "Check that the mod isn't nested"

    Some mods extract into an extra folder, so you end up with `mods/my_name.my_mod/my_name.my_mod/mod.toml`. If so, the launcher won't list the mod. Move the inner folder up so that `mod.toml` is directly inside the mod's folder.

## Configure a mod

Some mods have options you can change. In the launcher's `Mods` window, click the mod's name and look for an `Options` heading in the panel on the right. Hover over an option to see its default value and a description, if the mod's author provided one.

Click `Apply` to save your changes.

## Update a mod

To update a mod, find if a newer version of the mod exists in the [FactionFiles category](https://www.factionfiles.com/ff.php?action=files&file_category=52). If so, download the new version and replace the old folder in `mods` with the new one. If you're not sure the old one is fully replaced, delete the old folder first, so no leftover files remain.

Enabled mods will stay enabled when you replace an existing mod, unless the mod has changed its unique identifier. Click `Rescan` if the launcher is open.

## Remove a mod

There are two ways to remove a mod:

- Clear the mod's checkbox and click `Apply`. The mod stays in your `mods` folder, so you can enable it again later.
- Delete the mod's folder from `mods`, then click `Rescan` in the launcher.

## Legacy mods

Mods in the older `modinfo.xml` format are not compatible with Sledge.

- **Players** - install them with [Mod Manager Re-Mars-tered v1.03](https://www.factionfiles.com/ff.php?action=file&id=5995), which can be used alongside Sledge. See the [Installing Sledge](installing-sledge.md) page to see why SyncFaction is not compatible.

- **Mod authors** - convert the mod to the new format. See [Converting legacy mods](../developers/editing-files/legacy-mods.md).