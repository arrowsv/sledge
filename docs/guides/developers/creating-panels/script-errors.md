Some game objects (like the player), do not exist immediately, such as when in the main menu. Accessing them too early causes script errors.

You can prevent errors using one of three methods depending on your needs:

## Require gameplay

The simplest fix for entire panels. If a player opens the panel outside of gameplay, Sledge automatically blocks execution and displays `This panel requires the player to be in gameplay.`.

``` lua title="mod.lua"
sledge.register_window("My Window", function()
    local player = rfg.get_player()
    gui.text(player.salvage)
end, { requires_gameplay = true })
```

## Check for gameplay

[`rfg.is_in_gameplay`](../../../api/lua/namespaces.rfg.md#is_in_gameplay) is equivalent to the `requires_gameplay` option, except you can control what section of code is blocked from executing:

``` lua title="mod.lua"
sledge.register_window("My Window", function()
    if not rfg.is_in_gameplay() then
        gui.text_disabled("This panel requires the player to be in gameplay.")
        return
    end

    local player = rfg.get_player()
    gui.text(player.salvage)
end)
```

## Check for `nil`

Best used when a panel should stay functional and display default/fallback values even when certain game objects aren't valid yet.

The following widget shows `0.0` for each coordinate when the player doesn't exist:

``` lua title="mod.lua"
sledge.register_widget("Position", function()
    local x, y, z = 0.0, 0.0, 0.0

    local player = rfg.get_player()
    if player then
        x = player.position.x
        y = player.position.y
        z = player.position.z
    end

    gui.property_table("position", function()
        gui.property_row("X", function()
            gui.text(x)
        end)
        gui.property_row("Y", function()
            gui.text(y)
        end)
        gui.property_row("Z", function()
            gui.text(z)
        end)
    end)
end)
```