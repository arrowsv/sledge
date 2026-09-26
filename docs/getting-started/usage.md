# Usage

After installation, run the `launcher.exe` file in the `sledge` folder. 

On its first run, a `sledge.toml` file will be generated which stores config values. It is not recommended to manually edit this file as the launcher provides an interface for doing so.

## Changing options

Show the options modal by clicking the `Options` button. The main option to note is `Overlay key`, which will allow you to open the overlay while in-game and access windows and widgets. By default, it is set to the `f1` key. It is recommended to use a key that is not commonly used and out of the way.

Click the `Apply` button to save any changes.

## Enabling mods

Show the mods modal by clicking the `Mods` button. Currently installed mods are listed in the left panel with checkboxes denoting whether they are enabled. To enable or disable a mod, click the checkbox next to the mod's name. To view a mod's information in the right panel, click on the mod's name. Depending on the mod, options are available to change under the `Options` heading in the right panel.

Click the `Apply` button to save any changes, or the `Rescan` button in case any mods have been added/removed/changed while the launcher has been open.

## Launching the game

To play, click the `Play` button. To play without Sledge being active, click the `Play (vanilla)` button. Depending on the game version, it will attempt to launch the game:

- For the Steam version, it will run the `steam://run/667720` URI command. Steam must be open for the game to run.
- For the GOG version, it will find the `rfg.exe` executable and manually create the process.

!!! note

    The game will start with Sledge active even if the game wasn't run through the dedicated launcher, as it is currently designed to be opt-out. If this isn't desired, add the `--vanilla` argument to the game to force it to run without activating Sledge.

## Using the overlay

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