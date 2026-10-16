`mod.lua` is your mod's main entry point, run once by Sledge before the game starts loading. Use it to set up options, register events, panels, file overrides, and XML edits.

## Handling events

Because the script runs early, game objects (like the player) don't exist yet. Direct modifications at the top level will cause errors. Instead, register callback functions to game events using [`sledge.register_event`](../../api/lua/namespaces.sledge.md#register_event).

```lua title="mod.lua"
-- Runs every time a save is loaded, which guarantees the player exists
local function save_loaded_callback()
    rfg.get_player().salvage = 100000
    sledge.log("The player's salvage is now " .. rfg.get_player().salvage)
end

-- Register the callback function to the event
sledge.register_event(enums.event.save_loaded, save_loaded_callback)
```

See [`enums.event`](../../api/lua/enums.event.md) for the full list of events.

### Using event data

Some events pass an extra data table to your callback function. For example, the [`enums.event.key_down`](../../api/lua/events.key_down.md) event lets you check what key was pressed:

```lua title="mod.lua"
local function key_down_callback(data)
    if data.key == enums.key.f5 then
        if data.shift_down then
            sledge.log("Shift + F5 was pressed.")
        else
            sledge.log("F5 was pressed.")
        end
    end
end

sledge.register_event(enums.event.key_down, key_down_callback)
```

## Writing log messages

Write messages to the `sledge.log` file:

```lua title="mod.lua"
sledge.log("Info message.")
sledge.log_warn("Warning message.")
sledge.log_error("Error message.")
```

```log title="sledge.log"
[0000-00-00 00:00:00.000] [info] [my_name.my_mod] Info message.
[0000-00-00 00:00:00.000] [warn] [my_name.my_mod] Warning message.
[0000-00-00 00:00:00.000] [error] [my_name.my_mod] Error message.
```

## Retrieving options

Use the global [`mod`](../../api/lua/namespaces.global.md#mod) variable to read options configured by players. Option values depend on their type:

- `multiple` :lucide-move-right: `string|string[]`
- `key` :lucide-move-right: [`enums.key`](../../api/lua/enums.key.md)
- `checkbox` :lucide-move-right: `boolean`
- `custom` :lucide-move-right: `string`

Access the value using the option's name as a key:

```toml title="mod.toml"
id = "my_name.my_mod"
name = "My Mod"
authors = ["My Name"]
version = "1.0.0"
api_version = "1.1.0"

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
name = "Multiple array choice"
type = "multiple"
choices = [
    { name = "Choice 1", value = ["1", "2"] },
    { name = "Choice 2", value = ["3", "4"] }
]

[[options]]
name = "Custom choice"
type = "custom"
default = "Default value"
```

```lua title="mod.lua"
local enabled = mod.options["Toggle choice"] -- boolean
local key = mod.options["Key choice"] -- enums.key
local choice = mod.options["Multiple choices"] -- string
local choice_array = mod.options["Multiple array choice"] -- string[]
local custom_val = mod.options["Custom choice"] -- string
```

Next, learn how to [edit files](editing-files/index.md), [create panels](creating-panels/index.md), or explore the [Lua API](../../api/overview.md).