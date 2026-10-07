All functions used to draw elements inside a panel are in the [`gui`](../../../lua/api/namespaces.gui.md) namespace. Call them from inside a panel's callback function, in the order you want the elements to appear. See [Creating panels](index.md) for how to register one.

## Handling input

Most input elements, such as [`gui.checkbox`](../../../lua/api/namespaces.gui.md#checkbox), [`gui.input_int`](../../../lua/api/namespaces.gui.md#input_int), and [`gui.slider_int`](../../../lua/api/namespaces.gui.md#slider_int), don't change anything by themselves. You give them the value to display, and a callback function. When the player changes the element, Sledge calls your callback with the new value, and you decide what to do with it.

```lua title="mod.lua"
-- Stored outside the callback so it persists between frames.
local show_message = false

local function draw_my_window()
    gui.checkbox("Show message", show_message, function(new_value)
        show_message = new_value
    end)

    if show_message then
        gui.text("Hello!")
    end
end

sledge.register_window("My Window", draw_my_window)
```

Here, `show_message` is the value the checkbox displays, and the callback saves the player's choice back into it. Because the panel's callback runs every frame, the checkbox is drawn with the updated value on the next frame.

Elements that edit game values work the same way. Pass in the game's current value, then write the new value back in the callback, as the [property table example](#formatting-with-property-tables) below does with `game.fog_visible`.

Buttons use the same idea. [`gui.button`](../../../lua/api/namespaces.gui.md#button) takes a label and a callback that runs when the button is pressed.

!!! info

    Variables that hold state, like `show_message` above, must be declared outside the panel's callback. If they were declared inside it, they would be reset to their starting value every frame and the player's change would be lost immediately.

## Formatting with property tables

When displaying mod configurations or numerical data (aside from standard action buttons), use property tables. They line up each setting's label and value in a consistent grid, so panels look like the rest of Sledge's interface.

Use [`gui.property_table`](../../../lua/api/namespaces.gui.md#property_table) to create the container, and [`gui.property_row`](../../../lua/api/namespaces.gui.md#property_row) to add each setting to it.

Many input functions accept an optional `label` parameter. Whether to provide it depends on where the element is placed:

- **Inside a property table** - don't provide the `label` parameter. `gui.property_row` already defines the label for that row, so omitting it prevents the text from appearing twice.
- **Outside a property table** - provide the `label` parameter.

Here is an example with elements inside and outside of a property table:

```lua title="mod.lua"
local my_custom_integer = 50
local my_custom_choice = false

local function draw_my_panel()
    gui.button("Press me", function()
        sledge.log("A button was pressed.")
    end)

    gui.separator("Settings")

    -- Inside a property table: no label parameter, since each row has one.
    gui.property_table("settings_table", function()
        gui.property_row("Show fog", function()
            gui.checkbox(game.fog_visible, function(new_value)
                game.fog_visible = new_value
            end)
        end)

        local player = game.get_player()
        gui.property_row("Salvage", function()
            gui.input_int(player.salvage, function(new_value)
                player.salvage = new_value
            end)
        end)

        gui.property_row("Custom integer", function()
            gui.slider_int(my_custom_integer, 0, 50, function(new_value)
                my_custom_integer = new_value
            end)
        end)
    end)

    -- Outside a property table: the label is the first parameter.
    gui.checkbox("My custom choice", my_custom_choice, function(new_value)
        my_custom_choice = new_value

        if my_custom_choice then
            sledge.log("My custom choice is true.")
        end
    end)
end

sledge.register_window("My Config", draw_my_panel, { requires_gameplay = true })
```

This panel uses `game.get_player()`, so it's registered with `requires_gameplay = true`. See [Preventing script errors](script-errors.md).

## Useful functions

[`gui.set_tooltip`](../../../lua/api/namespaces.gui.md#set_tooltip)
:   Shows text when the previously drawn element is hovered.

---

[`gui.set_help_marker`](../../../lua/api/namespaces.gui.md#set_help_marker)
:   Like `gui.set_tooltip`, but attaches the text to a `?` icon next to the element.

---

[`gui.separator`](../../../lua/api/namespaces.gui.md#separator)
:   Draws a horizontal dividing line, optionally with a heading, to group related elements.

---

[`gui.same_line`](../../../lua/api/namespaces.gui.md#same_line)
:   Places the next element on the same line as the previous one.

---

[`gui.new_line`](../../../lua/api/namespaces.gui.md#new_line)
:   Moves the next element down to a new line.