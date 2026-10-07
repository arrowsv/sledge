## Checking the log
 
Use [`sledge.log`](../../lua/api/namespaces.sledge.md#log), [`sledge.log_warn`](../../lua/api/namespaces.sledge.md#log_warn), and [`sledge.log_error`](../../lua/api/namespaces.sledge.md#log_error) to write messages to the `sledge.log` file, located alongside the launcher. This can be useful for checking the state of a variable at a certain point in your script.

See [Writing log messages](creating-your-mod/script.md#writing-log-messages) for more information.
 
## Reloading mods
 
While the game is running, click `Reload mods` in the `Sledge` menu to reload all enabled mods. All registered events, widgets, and windows are cleared, and every mod's script is run again.
 
This is mainly useful for developing windows and widgets, since you can edit a script and see the result without restarting the game.
 
!!! warning
 
    Reloading doesn't undo changes that mods have already made to the game, such as edited files or modified game variables. Only use it for testing windows and widgets, and restart the game to test anything else.
 