The `mod.lua` file is the main entry point for your mod. Sledge runs it only once, before the game starts loading. This is where you set up everything your mod does, such as reading and storing options from the metadata, registering event callbacks, panels, file overrides, and XML edits.

## Running code using events

Because `mod.lua` runs before the game loads, most of the game's objects don't exist yet. Code that uses them directly, such as `game.get_player().salvage = 100000`, will cause an error if it's written at the top level of the script.

Instead, your mod reacts to events. An event is something that happens in the game, such as a save being loaded. You register a callback function to an event, and Sledge calls it each time the event is triggered, when the game objects you need are ready to use.

First, write a function that contains the code you want to run, then register the function to an event with [`sledge.register_event`](../../../lua/api/namespaces.sledge.md#register_event).

For example, to set the player's salvage, use [`defines.event.save_loaded`](../../../lua/api/events.save_loaded.md). This event is triggered after a save has loaded, so the player is guaranteed to exist:

```lua title="mod.lua"
-- The function runs every time a save is loaded.
local function save_loaded_callback()
    game.get_player().salvage = 100000
    sledge.log("The player's salvage is now " .. game.get_player().salvage)
end

-- Tell Sledge to call it when the save_loaded event is triggered.
sledge.register_event(defines.event.save_loaded, save_loaded_callback)
```

Each event guarantees different things about the state of the game, so choose the one that matches what your code needs. See [`defines.event`](../../../lua/api/defines.event.md) for the full list.

### Using event data

Some events provide extra information about what happened. Sledge passes this to your callback as a table, called the event's data. Add a parameter to your callback function to receive it. The `save_loaded` callback above doesn't need one, but other events do.

For example, [`defines.event.key_down`](../../../lua/api/events.key_down.md) is triggered whenever a key is pressed. Its data contains the key that was pressed and the state of the modifier keys, so your callback can check what the player pressed:

```lua title="mod.lua"
-- The data parameter receives the table that Sledge passes in.
local function key_down_callback(data)
    if data.key == defines.key.f5 then
        if data.shift_down then
            sledge.log("Shift + F5 was pressed.")
        else
            sledge.log("F5 was pressed.")
        end
    end
end

sledge.register_event(defines.event.key_down, key_down_callback)
```

The fields available in the data are different for each event. Check the event's documentation page to see what it provides.

## Writing log messages

Use the following functions to log messages:

- [`sledge.log`](../../../lua/api/namespaces.sledge.md#log)
- [`sledge.log_warn`](../../../lua/api/namespaces.sledge.md#log)
- [`sledge.log_error`](../../../lua/api/namespaces.sledge.md#log)

All log messages are automatically prefixed with your mod's ID and written to the `sledge.log` file:

```lua title="mod.lua"
sledge.log("My message.")
sledge.log_warn("My message.")
sledge.log_error("My message.")
```

```log title="sledge.log"
[0000-00-00 00:00:00.000] [info] [my_name.my_mod] My message.
[0000-00-00 00:00:00.000] [warn] [my_name.my_mod] My message.
[0000-00-00 00:00:00.000] [error] [my_name.my_mod] My message.
```

## Retrieving options

Every mod's script environment has a [`mod`](../../../lua/api/namespaces.global.md#mod) variable of the [`types.mod_info`](../../../lua/api/types.mod_info.md) type. Use it to access the metadata of the mod the script belongs to.

If your mod defines options in its metadata, read their values from the [`types.mod_info.options`](../../../lua/api/types.mod_info.md#options) table, using the option's name as the key. The type of the returned value depends on the option's type:

- `multiple` returns a `string`.
- `key` returns a [`defines.key`](../../../lua/api/defines.key.md).
- `checkbox` returns a `boolean`.
- `custom` returns a `string`.

For example, here is how to define all four types of options in the metadata and retrieve them in Lua:

```toml title="mod.toml"
id = "my_name.my_mod"
name = "My Mod"
authors = ["My Name"]
version = "1.0.0"
sledge_version = ">=0.1.0"

[[options]]
name = "Toggle choice"
type = "checkbox"
default = false

[[options]]
name = "Key choice"
type = "key"
default = "f5"

[[options]]
name = "Multiple choice"
type = "multiple"
choices = [
    "Choice 1",
    "Choice 2"
]

[[options]]
name = "Custom choice"
type = "custom"
default = "Default value"
```

```lua title="mod.lua"
-- This is a boolean.
local toggle_choice = mod.options["Toggle choice"]

-- This is a defines.key.
local key_choice = mod.options["Key choice"]

-- This is a string.
local multiple_choice = mod.options["Multiple choice"]

-- This is a string.
local custom_choice = mod.options["Custom choice"]

-- This is nil because no option with this name exists.
local non_existing_choice = mod.options["Another choice"]
```

### Mapping options to values

A `multiple` option shows the player a list of display names, and `mod.options` returns the one they picked as a string. Sometimes the display name isn't the value your script needs. To handle this, show friendly names in the option and map each one to the real value in Lua.

Mapping uses a table where each key is a display name and each value is whatever your script needs.

#### Basic example

Say you want a "Spawn rate" option where the player picks `Low`, `Medium`, or `High`, but your script needs the numbers `1`, `2`, or `3`.

1. Define the option in your metadata, with the display names as the `choices`:

    ```toml title="mod.toml"
    [[options]]
    name = "Spawn rate"
    type = "multiple"
    choices = [
        "Low",
        "Medium",
        "High"
    ]
    ```

2. In your script, define the mapping table. Each key must exactly match one of the `choices`, including capitalization:

    ```lua title="mod.lua"
    local spawn_rates = {
        ["Low"] = 1,
        ["Medium"] = 2,
        ["High"] = 3
    }
    ```

3. Read the player's choice, then use it as the key to look up the matching value:

    ```lua title="mod.lua"
    local spawn_rate_choice = mod.options["Spawn rate"]
    local spawn_rate = spawn_rates[spawn_rate_choice]

    sledge.log("The spawn rate is " .. spawn_rate)
    ```

    !!! warning

        If a key in the table doesn't match a choice in `mod.toml`, the lookup returns `nil` and using it will cause an error. Update both whenever you rename a choice.

#### Mapping to a table of values

The value doesn't have to be a single number or string. It can be anything, including another table.

For example, the *Safehouse Vehicle Selector* mod edits `spawn_group_vehicle.xtbl`, which requires vehicle code names like `Col_Taxi_1`. Many of these aren't understandable to players, so the mod shows each vehicle's display name in the option. Each vehicle also has several variants, so each display name maps to a table of code names.

The steps are the same as before:

1. Define the option with the display names as the `choices`:

    ```toml title="mod.toml"
    [[options]]
    name = "Parker"
    type = "multiple"
    choices = [
        "Civilian Luxury Taxi",
        "Civilian Rover"
    ]
    ```

2. Define the mapping table, with each value being a table of code names:

    ```lua title="mod.lua"
    local vehicle_choices = {
        ["Civilian Luxury Taxi"] = {"Col_Taxi_1", "Col_Taxi_2", "Col_Taxi_3"},
        ["Civilian Rover"] = {"Min_Rover-A_1", "Min_Rover-A_2", "Min_Rover-A_3"}
    }
    ```

3. Look up the player's choice and iterate over the resulting table:

    ```lua title="mod.lua"
    local parker_choice = mod.options["Parker"]
    local code_names = vehicle_choices[parker_choice]

    for _, code_name in ipairs(code_names) do
        sledge.log(code_name)
    end
    ```

    In a real mod, you would use these code names to edit the game files instead of logging them.

## Next steps

After understanding the basics, see how to [edit files](../editing-files/index.md) and [create panels](../creating-panels/index.md). For more advanced mods, take a look at what's available in the namespaces of the [Lua API](../../../lua/api/namespaces.game.md).