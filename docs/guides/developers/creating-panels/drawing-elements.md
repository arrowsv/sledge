All drawing functions belong to the [`gui`](../../../api/lua/namespaces.gui.md) namespace and should be called inside your panel's callback function in the order you want elements rendered.

## Handling input

Interactive elements (such as checkboxes, sliders, and inputs), require you to pass the current value and a callback function handles changes:

```lua title="mod.lua"
local show_message = false

sledge.register_window("My Window", function()
    gui.checkbox("Show message", show_message, function(new_value)
        show_message = new_value
    end)

    if show_message then
        gui.text("Hello!")
    end
end)
```

## Formatting with property tables

Use property tables to align the labels and values of settings into a clean, uniform grid:

- Use [`gui.property_table`](../../../api/lua/namespaces.gui.md#property_table) to create the container.
- Use [`gui.property_row`](../../../api/lua/namespaces.gui.md#property_row) to add items.


!!! warning "Label parameters"

    Do not pass explicit label parameters to input elements placed inside property tables, because `gui.property_row` handles the label for you.

``` lua title="mod.lua"
local custom_integer = 50
local custom_choice = false

sledge.register_window("My Config", function()
    gui.property_table("settings", function()
        gui.property_row("Custom integer", function()
            gui.slider_int(custom_integer, 0, 50, function(new_value)
                custom_integer = new_value
            end)
        end)
    end)

    -- Provide the label parameter because it is outside a property table.
    gui.checkbox("Custom choice", custom_choice, function(new_value)
        custom_choice = new_value
        
        if custom_choice then
            sledge.log("Custom choice is true.")
        end
    end)
end, { requires_gameplay = true })
```

## Useful functions

| Function | Description |
| --- | --- |
| [`gui.tooltip`](../../../api/lua/namespaces.gui.md#tooltip) | Displays text when the previous element is hovered. |
| [`gui.help_marker`](../../../api/lua/namespaces.gui.md#help_marker) | Attaches a `?` icon next to the previous element with hover text. |
| [`gui.separator`](../../../api/lua/namespaces.gui.md#separator) | Draws a horizontal dividing line with an optional section heading. |
| [`gui.same_line`](../../../api/lua/namespaces.gui.md#same_line) | Forces the next element to render on the same line. |
| [`gui.new_line`](../../../api/lua/namespaces.gui.md#new_line) | Moves the next element down to a new line. |