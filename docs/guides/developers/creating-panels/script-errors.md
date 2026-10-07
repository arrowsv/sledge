Some game objects, such as [`types.player`](../../../lua/api/types.player.md), only exist at certain times. Using one before it's valid causes a script error. For example, calling [`game.get_player()`](../../../lua/api/namespaces.game.md#get_player) before the player has loaded returns `nil`.

Panels are especially prone to this because the player can open them at any time, including from the main menu. The same applies to event callbacks, where each event guarantees different things about the state of the game.

There are three ways to guard a panel. Which one to use depends on what the panel should do when the objects aren't available.

## Requiring gameplay

If the whole panel needs the player to be in gameplay, set the `requires_gameplay` field to `true` in the panel's options.

The following script causes errors if the player opens the window from the main menu, because the player object doesn't exist yet:

```lua title="mod.lua"
sledge.register_window("My Window", function()
    local player = game.get_player()
    gui.text(player.salvage)
end)
```

This version won't cause an error:

```lua title="mod.lua"
sledge.register_window("My Window", function()
    local player = game.get_player()
    gui.text(player.salvage)
end, { requires_gameplay = true })
```

When `requires_gameplay` is `true`, Sledge intercepts the callback and shows the message `This panel requires the player to be in gameplay.` in the window instead, if the player opens it from the main menu.

## Checking for gameplay

[`game.is_in_gameplay`](../../../lua/api/namespaces.game.md#is_in_gameplay) lets you do the same check yourself. This is equivalent to `requires_gameplay`, but you control what's shown instead:

```lua title="mod.lua"
sledge.register_window("My Window", function()
    if not game.is_in_gameplay() then
        gui.text_disabled("This panel requires the player to be in gameplay.")
        return
    end

    local player = game.get_player()
    gui.text(player.salvage)
end)
```

Use this when you want a custom message, or when only part of the panel needs the player and the rest can always be drawn.

## Checking for `nil`

Checking whether an object is `nil` before using it also prevents errors, and doesn't require `game.is_in_gameplay`. This is the best choice when the panel should still show something useful without the object.

For example, here is a simplified version of the built-in `Position` widget. It shows `0.0` for each coordinate when the player doesn't exist:

```lua title="mod.lua"
sledge.register_widget("Position", function()
    local x, y, z = 0.0, 0.0, 0.0

    local player = game.get_player()
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

## Which one to use

`requires_gameplay`
:   The simplest choice. Use it when the whole panel depends on the player or other gameplay objects.

---

`game.is_in_gameplay`
:   Use it when you want a custom message, or when only some of the panel depends on gameplay.

---

Checking for `nil`
:   Use it when the panel should keep working, showing default values, even when an object isn't available.