# Usage

After installation, run the `launcher.exe` file.

## Launcher

### Changing options

Show the options modal by clicking the `Options` button. The main option to note is `Overlay key`, which will allow you to open the overlay while in-game and access windows and widgets. By default, it is set to the `f1` key. It is recommended to use a key that is not commonly used and out of the way.

Click the `Apply` button to save any changes.

### Toggling mods

Show the mods modal by clicking the `Mods` button. 

Mods that are present in the `mods` folder are shown in the left panel. Click the checkbox next to a mod's name to enable or disable it.

Click on a mod's name to view its information in the right panel. If a mod defines options, they will appear in the right panel under an `Options` heading. Hovering over each option's interactable box will show its default value and, if defined by the mod author, a description of the option.

Click the `Apply` button to save any changes, or the `Rescan` button in case the mod folder has been modified while the launcher is open.

### Launching the game

Click the `Play` button to launch the game. Click the `Play (vanilla)` button to launch the game without Sledge active.

If the Steam version is detected, it will run the `steam://run/667720` URI command. Steam must be open for the game to run. If the GOG version is detected, the `rfg.exe` process will be manually created.

!!! note

    Sledge will be active even if the game wasn't run through the launcher. Passing the `--vanilla` flag to the game will override the launcher and force it to run without Sledge.

## In-game

Toggle the overlay by pressing the key set in the `Overlay key` option. While the overlay is active, input to the game is blocked and the OS' cursor will be visible, allowing you to click the Sledge menu bar at the top.

### Windows

Available windows are shown in the `Windows` menu bar item. Hovering over a window's name will show the mod it belongs to, if any. Click the window's name to toggle its visibility. Windows will only be visible while the overlay is enabled.

While a window is open, it can be moved to any position by dragging its title bar. A window can be resized by dragging its edges, unless a mod has disabled the functionality for that window.

Depending on the mod, a window's contents may not be visible until the player is fully loaded and in gameplay. This is to ensure that the windows can't display information that doesn't exist yet.

### Widgets

Available widgets are shown in the `Widgets` menu bar item. Hovering over a widget's name will show the mod it belongs to, if any, and show a sub-menu to toggle its visibility and anchor position. Widgets will be visible even while the overlay is disabled and will stay in their selected anchor position.

### Reloading mods

If a mod's contents have been changed while the game is running, the `Reload mods` option can be clicked in the `Sledge` menu bar item to reload all currently enabled mods. All registered events, widgets, and windows will be cleared and mods will be re-run. 

This option is only useful for debugging windows and widgets as it lets you quickly view changes. It is not recommended to use this as a regular user as any changes that mods have made to the game aren't tracked and can't be reverted to their original state.