!!! warning "Not compatible with SyncFaction"

    Don't install Sledge in a folder modified by [SyncFaction](https://www.factionfiles.com/ff.php?action=file&id=7724). It includes [Reconstructor](https://www.factionfiles.com/ff.php?action=file&id=7743) and the [Terraform Patch](https://www.factionfiles.com/ff.php?action=file&id=7744), which conflict with Sledge's `dinput8.dll` file.

    Use [Mod Manager Re-Mars-tered v1.03](https://www.factionfiles.com/ff.php?action=file&id=5995) if you wish to use older mods made with the `modinfo.xml` format.

1.  Download the latest `Sledge.<ver>.zip` file from the [releases page](https://github.com/arrowsv/sledge/releases/latest).

2.  Find the game's root folder containing `rfg.exe`.

3.  Unzip the contents directly into that folder.

## Folder structure

By default, Sledge's files live inside a `sledge` folder, with `dinput8.dll` next to `rfg.exe`:

```
📁 Red Faction Guerrilla Re-Mars-tered/
├── 📁 sledge/
│   ├── 📁 mods
│   ├── 📄 launcher.exe
│   └── 📄 sledge.dll
├── 📄 dinput8.dll
└── 📄 rfg.exe
```

Everything can go directly in the root folder if you prefer keeping files together:

```
📁 Red Faction Guerrilla Re-Mars-tered/
├── 📁 mods/
├── 📄 launcher.exe
├── 📄 sledge.dll
├── 📄 dinput8.dll
└── 📄 rfg.exe
```

Next, learn how to [use Sledge](using-sledge.md) and [install mods](managing-mods.md).
