# Creating panels

Panels refer to windows and widgets which are used to display information and/or allow the player to configure a mod beyond what its metadata file defines while in-game.

When registering a panel, a name and callback function must be provided. While a panel is visible, its callback function will be called every frame to draw its contents, meaning any changes to the data it displays will be visible immediately.

Windows are only visible when the Sledge overlay is enabled and are for displaying information and capturing player input. For example, letting the player change their team, position, variables defined in the mod's script, etc.

Widgets stay visible when the Sledge overlay is disabled, have no background, and are for displaying information that the player may want to see while playing. For example, the player's current frames per second, position, speed, etc.

## Registering a window

Register a window with [`sledge.register_window`](/lua/api/sledge.md#register_window) by passing a name for the window and a callback function:

```lua
local function draw_my_window()
    gui.text("This is a text label.")
    gui.button("Press me", function()
        sledge.log("A button was pressed.")
    end)
end

sledge.register_window("My Window", draw_my_window)
```

A table of options can also be passed to the registration function. See the documentation of the `options` parameter for more information:

```lua
local function draw_my_window()
    gui.text("This is a text label.")
    gui.button("Press me", function()
        sledge.log("A button was pressed.")
    end)
end

sledge.register_window("My Window", draw_my_window, { no_resize = true })
```

## Registering a widget

Register a widget with [`sledge.register_widget`](/lua/api/sledge.md#register_widget) by passing a name for the widget and a callback function:

```lua
local function draw_my_widget()
    gui.text("This is a text label.")
end

sledge.register_widget("My Widget", draw_my_widget)
```

A table of options can also be passed to the registration function. See the documentation of the `options` parameter for more information.

## Preventing script errors

Code modifying game objects like [`types.player`](/lua/api/types/player.md) fails if they aren't valid, such as accessing [`game.get_player()`](/lua/api/game.md#get_player) before the player loads. Since panels can be toggled at any time, drawing contents when an object is invalid causes script errors. To prevent this, set the `requires_gameplay` field to `true` in the options table parameter. 

The following script will cause errors if the player enables the window while in the main menu, because the game's player object does not exist at that point:

```lua
sledge.register_window("My Window", function()
    local player = game.get_player()
    gui.text(player.salvage)
end)
```

The following script will not cause an error if the player enables the window while in the main menu:

```lua
sledge.register_window("My Window", function()
    local player = game.get_player()
    gui.text(player.salvage)
end, { requires_gameplay = true })
```

When `requires_gameplay` is `true`, Sledge will intercept the callback and display the message `This panel requires the player to be in gameplay.` inside the window if the player attempts to open it from the main menu. 

This option is the equivalent of using the [`game.is_in_gameplay`](/lua/api/game.md#is_in_gameplay) function and returning if it is `false`:

```lua
sledge.register_window("My Window", function()
    if not game.is_in_gameplay() then
        gui.text_disabled("This panel requires the player to be in gameplay.")
        return
    end

    local player = game.get_player()
    gui.text(player.salvage)
end)
```

It is not strictly required to use `game.is_in_gameplay`; checking for whether a type is `nil` before accessing it will also prevent errors. For example, here is how the built-in `Position` widget shows `0.0` for each coordinate when the player doesn't exist:

```lua
local x_pos
local y_pos
local z_pos

sledge.register_widget("Position", function()
    local player = game.get_player()

    if player then
        x_pos = player.position.x
        y_pos = player.position.y
        z_pos = player.position.z
    else
        x_pos = 0.0
        y_pos = 0.0
        z_pos = 0.0
    end

    gui.property_table("position", function()
        gui.property_row("X", function()
            gui.text(x_pos)
        end)
        gui.property_row("Y", function()
            gui.text(y_pos)
        end)
        gui.property_row("Z", function()
            gui.text(z_pos)
        end)
    end)
end)
```

## Drawing elements

All functions used to draw elements inside a panel are contained within the [`gui`](/lua/api/gui.md) namespace.

When displaying mod configurations or numerical data (aside from standard action buttons), it is highly recommended to use property tables which provide a cohesive layout.

### Formatting with property tables

When utilizing a property table, use [`gui.property_table`](/lua/api/gui.md#property_table) to create the container, and [`gui.property_row`](/lua/api/gui.md#property_row) to isolate individual settings.

Many input functions, such as [`gui.checkbox`](/lua/api/gui.md#checkbox), [`gui.property_table`](/lua/api/gui.md#input_int), and [`gui.input_int`](/lua/api/gui.md#slider_int) accept an optional `label` parameter. Choosing whether to provide this parameter depends on where the element is placed:

* Inside a property table: Do **not** provide the `label` parameter. The `gui.property_row` function automatically defines the label for that row, so omitting the parameter ensures the text is not duplicated.
* Outside a property table: Provide the `label` parameter.

Here is an example demonstrating elements inside and outside of a property table:

```lua
local my_custom_integer = 50
local my_custom_choice = false

local function draw_my_panel()
    gui.button("Press me", function()
        sledge.log("A button was pressed.")
    end)

    gui.separator("Settings")
    
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

    gui.checkbox("My custom choice", my_custom_choice, function(new_value)
        my_custom_choice = new_value

        if my_custom_choice then
            sledge.log("My custom choice is true.")
        end
    end)
end

sledge.register_window("My Config", draw_my_panel, { requires_gameplay = true })
```

### Useful functions

- Tooltips: Use [`gui.set_tooltip`](/lua/api/gui.md#set_tooltip) to provide information that will appear when the previously drawn element is hovered. [`gui.set_help_marker`](/lua/api/gui.md#set_help_marker) can also be used to instead attach the tooltip to a `?` icon.

- Alignment: Use [`gui.same_line`](/lua/api/gui.md#same_line) to force the next drawn element onto the same line as the previous one, or use [`gui.new_line`](/lua/api/gui.md#new_line) to push the next element down.