After [installing Sledge](installing-sledge.md), run the `launcher.exe` file. The launcher is where you choose which mods are enabled and start the rfg.

## Launcher

### Changing options

Click the `Options` button to show the options window. The main option to note is `Overlay key`, which sets the key that opens the overlay in-game, where you can access windows and widgets. By default, it is `F1`. Choose a key that isn't commonly used in the game and is out of the way.

Click `Apply` to save any changes.

### Toggling mods

1. Click the `Mods` button to show the mods window.

2. Mods in your `mods` folder are listed on the left. Click the checkbox next to a mod's name to enable or disable it.

3. Click a mod's name to view its information on the right. If the mod has options, they appear under an `Options` heading. Hover over an option's box to see its default value and, if the mod's author has provided one, a description.

4. Click `Apply` to save your changes.

If you add or remove a mod's folder while the launcher is open, click `Rescan` to refresh the list.

To browse for mods compatible with Sledge, click the `FactionFiles` button.

!!! info "See also"

    For more information about mods, see the [Managing your mods](managing-mods.md) page.

### Launching the game

Click `Play` to launch the rfg. To launch it without Sledge, change the `Profile` dropdown to `Vanilla`.

The launcher supports the Steam and GOG versions of the rfg. If you use Steam, Steam must be open for the game to launch.

!!! warning "Sledge is also active when you don't use the launcher"

    Sledge loads whenever the game starts, even if you didn't launch it from the launcher. Use the launcher to change your settings and enabled mods, but you can then start the game however you like.

    To force the game to run without Sledge, pass the `--vanilla` flag to the rfg. For example, in Steam, right-click the game, select `Properties`, and enter `--vanilla` under `Launch Options`.

## In-game

Press the key set as the `Overlay key` to toggle the overlay. While it's open, input to the game is blocked and the system cursor is shown, so you can click the Sledge menu bar at the top of the screen.

### Windows

Available windows are listed in the `Windows` menu. Hover over a window's name to see which mod it belongs to, if any, and click it to toggle its visibility. Windows are only visible while the overlay is open.

Move a window by dragging its title bar, and resize it by dragging its edges. Some mods turn off resizing for their windows.

Some windows can't show their contents until the game has loaded and you're in gameplay, to avoid displaying information that doesn't exist yet. If you open one from the main menu and it shows the message "This panel requires the player to be in gameplay.", load a save and the contents will appear.

### Widgets

Available widgets are listed in the `Widgets` menu. Hover over a widget's name to see which mod it belongs to, if any. A sub-menu lets you toggle its visibility and choose its anchor position, which is the part of the screen it's placed against.

Unlike windows, widgets stay visible while the overlay is closed, so they're useful for information you want to see while playing.

### Reloading mods

The `Reload mods` option in the `Sledge` menu reloads all enabled mods while the game is running. It's meant for mod developers testing their scripts.

!!! warning

    As a player, don't use `Reload mods`. Changes that mods have already made to the game aren't tracked, so they can't be undone, and reloading can leave the game in a state that no longer matches your mods.

    See the [Testing your mod](../developers/testing.md) page for more information.
