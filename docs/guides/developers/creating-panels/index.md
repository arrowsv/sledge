Panels are the windows and widgets a mod can draw on screen. Use them to show information, or to let the player change settings in-game beyond what the mod's metadata options offer.

There are two kinds of panel:

- **Windows** - Only visible while the Sledge overlay is open. They have a background and accept player input, so use them for things the player changes, such as their team, their position, or a variable defined in your script.

- **Widgets** - Stay visible when the overlay is closed, and have no background. Use them for information the player wants to see while playing, such as frames per second, position, or speed.

## How panels work

To register a panel, provide a name and a callback function. While the panel is visible, Sledge calls the callback every frame to draw its contents, so any changes to the data it displays appear immediately.

Because the callback runs every frame, anything that needs to persist between frames, such as a setting the player changes, must be stored in a variable outside the callback. Variables declared inside it are created again on every frame.

## Registering a panel

Register a window with [`sledge.register_window`](../../../api/lua/namespaces.sledge.md#register_window), or a widget with [`sledge.register_widget`](../../../api/lua/namespaces.sledge.md#register_widget). Both take a name and a callback function. Call them at the root level of `mod.lua`.

=== "Window"

    ``` lua title="mod.lua"
    local function draw_my_window()
        gui.text("This is a text label.")
        gui.button("Press me", function()
            sledge.log("A button was pressed.")
        end)
    end

    sledge.register_window("My Window", draw_my_window)
    ```

=== "Widget"

    ``` lua title="mod.lua"
    local function draw_my_widget()
        gui.text("This is a text label.")
    end

    sledge.register_widget("My Widget", draw_my_widget)
    ```

The functions inside the `gui` namespace draw the panel's contents. See [Drawing elements](drawing-elements.md) for how to use them.

## Panel options

Both functions accept a table of options as an optional last argument. For example, to stop the player from resizing a window:

``` lua title="mod.lua"
sledge.register_window("My Window", draw_my_window, { no_resize = true })
```

The most commonly used option is `requires_gameplay`, which helps to prevent errors when your window uses game objects, such as the player. See the [Preventing script errors](script-errors.md) page for more information.

See the `options` parameter in the documentation for [`sledge.register_window`](../../../api/lua/namespaces.sledge.md#register_window) and [`sledge.register_widget`](../../../api/lua/namespaces.sledge.md#register_widget) for the full list.

!!! warning

    Panels can be opened at any time, including from the main menu, before the game's objects exist. A panel that calls `rfg.get_player()` without handling this will cause script errors. See the [Preventing script errors](script-errors.md) page for more information.
