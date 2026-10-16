Panels are the windows and widgets a mod can draw on screen to display information or let players change settings in-game.

## Panel types

- **Windows** - Visible only while the Sledge overlay is open. They include a background and accept player input, so use them for things such as changing a player's team, position, or script variables.

- **Widgets** - Stay visible even when the overlay is closed, and have no background. Ideal for information the player would want to see while playing, such as frame rate, position, or speed.

## How panels work

To create a panel, provide a name and a callback function to Sledge. While the panel is open, Sledge runs the callback every frame to draw its contents.

!!! warning "State persistance"

    Because the callback runs every frame, any variable that needs to change or persist must be declared outside the callback function. Variables declared inside the callback will reset every frame.

## Registering panels

Register windows with [`sledge.register_window`](../../../api/lua/namespaces.sledge.md#register_window) and widgets with [`sledge.register_widget`](../../../api/lua/namespaces.sledge.md#register_widget) at the root level of `mod.lua`.

=== "Window"

    ```lua title="mod.lua"
    sledge.register_window("My Window", function()
        gui.text("This is a text label.")
        gui.button("Press me", function()
            sledge.log("A button was pressed.")
        end)
    end)
    ```

=== "Widget"

    ```lua title="mod.lua"
    sledge.register_widget("My Widget", function()
        gui.text("This is a text label.")
    end)
    ```

The [`gui`](../../../api/lua/namespaces.gui.md) namespace provides functions for drawing the panel's contents. See how to [draw elements](drawing-elements.md).

## Panel options

The registration functions accept an optional table of configuration settings as their last argument:

```lua title="mod.lua"
sledge.register_window("My Window", function()
    gui.text("This is a text label.")
end, { requires_gameplay = true })
```

See the `options` parameter documentation for the full list.

!!! warning "Preventing script errors"

    Panels can be opened at any time, including from the main menu, before game objects exist. If your panel modifies the player through `rfg.get_player()` without safeguarding against this, it will cause script errors. See [Preventing script errors](script-errors.md).
