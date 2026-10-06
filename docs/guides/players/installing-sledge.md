!!! warning "Not compatible with SyncFaction"

    Don't install Sledge in a game folder that [SyncFaction](https://www.factionfiles.com/ff.php?action=file&id=7724) has modified. SyncFaction automatically installs [Reconstructor](https://www.factionfiles.com/ff.php?action=file&id=7743) and the [Terraform Patch](https://www.factionfiles.com/ff.php?action=file&id=7744), and Reconstructor and Sledge each need their own `dinput8.dll` to load into the game. Installing one replaces the other's file, so only one of them will work.

    To use older mods in the `modinfo.xml` format alongside Sledge, install them with [Mod Manager Re-Mars-tered v1.03](https://www.factionfiles.com/ff.php?action=file&id=5995) instead.

1. Download the latest release from the [releases page](https://github.com/arrowsv/sledge/releases/latest) by selecting the `Sledge.<ver>.zip` file.

2. Find the game's root folder containing `rfg.exe`.

3. Extract the zip file into that folder. The structure should be as follows:

    ```
    📁 Red Faction Guerrilla Re-Mars-tered/
    ├── 📁 sledge/
    │   ├── 📁 mods
    │   ├── 📄 launcher.exe
    │   └── 📄 sledge.dll
    ├── 📄 dinput8.dll
    └── 📄 rfg.exe
    ```

    !!! info "Alternative layout"
    
        Sledge's files can also be placed directly alongside `rfg.exe` in the root folder instead of inside a `sledge` folder. Use this layout if you'd rather keep everything together. The `mods` folder is then in the game's root folder:
    
        ```text
            📁 Red Faction Guerrilla Re-Mars-tered/
            ├── 📁 mods/
            ├── 📄 launcher.exe
            ├── 📄 sledge.dll
            ├── 📄 dinput8.dll
            └── 📄 rfg.exe
        ```

Once Sledge is installed, see how to [use Sledge](using-sledge) and [install mods](managing-mods).