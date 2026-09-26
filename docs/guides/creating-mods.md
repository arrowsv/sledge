# Creating mods

Create a folder with the name of the mod in the `sledge/mods` folder. Inside the newly created mod folder, create two files named `mod.toml` and `mod.lua`.

```
📁 mods/
└── 📁 My Mod/
    ├── 📄 mod.toml
    └── 📄 mod.lua
```

## mod.toml

This file is used to define the mod's metadata. The following fields are available:

- `id` - The identifier of the mod. Write in all lowercase, no special characters, and replace spaces with underscores. Format the identifier as `"<author>.<name>"`.
- `name` - The display name of the mod.
- `authors` - The authors of the mod as an array.
- `description` - The description of the mod.
- `version` - The version of the mod. Follow the `<major>.<minor>.<patch>` format from the [Semantic Versioning](https://semver.org) specification. For an initial release, start at `1.0.0` (major is `1`, minor is `0`, patch is `0`). Increment the major version when a breaking change is made, the minor version when a new feature is added, and the patch version when a bug is fixed without adding a new feature.

```toml title="mod.toml"
id = "my_name.my_mod"
name = "My Mod"
authors = ["my_name"]
description = "A description of my mod."
version = "1.0.0"
```

### Defining options

Mods can define options that the user can configure within the launcher. The following fields are available:

- `name` - The name of the option.
- `tooltip` - The tooltip that appears when hovering over the option.
- `type` - The type of the option. The following types are available:
    - `multiple` - A multiple choice box with defined values.
    - `key` - A multiple choice box with [`defines.key`](../lua/api/defines/key.md) values.
    - `checkbox` - A checkbox that allows a `true` or `false` value.
    - `custom` - A text box that allows a custom value.
- `default` - The default choice of the option. If it is not defined, it will default to empty or the first value in the multiple choice box.
- `choices` - The array of choices available in the multiple choice box. This is only applicable to the `multiple` type. If desired, an option can copy the choices of another option by writing the name of the option instead of an array. The option being copied must also be of type `multiple`.

=== "multiple"

    ```toml title="mod.toml"
    [[options]]
    name = "My choices"
    type = "multiple"
    default = "Choice 2"
    choices = [
        "Choice 1", 
        "Choice 2"
    ]

    [[options]]
    name = "My copied choices"
    type = "multiple"
    choices = "My choices"
    ```

=== "key"

    ```toml title="mod.toml"
    [[options]]
    name = "Toggle key"
    type = "key"
    default = "f3"
    ```

=== "checkbox"

    ```toml title="mod.toml"
    [[options]]
    name = "Enable feature"
    tooltip = "Description of the feature."
    type = "checkbox"
    default = false
    ```

=== "custom"

    ```toml title="mod.toml"
    [[options]]
    name = "Multiplier"
    type = "custom"
    default = "4"
    ```

??? example "Example using the Safehouse Vehicle Selector mod"

    ```toml title="mod.toml"
    id = "arrows.safehouse_vehicle_selector"
    name = "Safehouse Vehicle Selector"
    authors = ["arrows"]
    description = "Select which vehicle spawns at each safehouse."
    version = "1.0.0"

    [[options]]
    name = "Parker"
    type = "multiple"
    choices = [
        "EDF APC",
        "EDF APC (Turret)",
        "EDF Scout",
        "EDF Scout (Turret)",
        "EDF Staff",
        "EDF Staff (Turret)",
        "EDF Supply Truck",
        "EDF Supply Truck (Turret)",
        "EDF Flyer",
        "EDF Bomber",
        "Civilian Supply Truck",
        "Civilian Supply Truck (Turret)",
        "Civilian Garbage Truck",
        "Civilian Garbage Truck (Turret)",
        "Civilian Dump Truck",
        "Civilian Pickup",
        "Civilian Pickup (Turret)",
        "Civilian Mining ATV",
        "Civilian Mining ATV (Turret)",
        "Civilian Mini Hauler",
        "Civilian Rover",
        "Civilian Rover (Turret)",
        "Civilian Emergency Rover",
        "Civilian Flatbed",
        "Civilian Flatbed (Turret)",
        "Civilian Fuel Tanker",
        "Civilian Supercar",
        "Civilian Luxury Coupé",
        "Civilian Luxury SUV",
        "Civilian Luxury Taxi",
        "Civilian Luxury Bus",
        "Marauder Jetter",
        "Marauder Raider",
        "Light Walker",
        "Heavy Walker",
        "Combat Walker",
        "Tank",
        "Heavy Tank",
        "Rocket Tank",
        "Heavy Rocket Tank",
        "Bulldozer",
        "Mars Rover"
    ]

    [[options]]
    name = "Dust"
    type = "multiple"
    choices = "Parker"

    [[options]]
    name = "Badlands"
    type = "multiple"
    choices = "Parker"

    [[options]]
    name = "Oasis"
    type = "multiple"
    choices = "Parker"

    [[options]]
    name = "Eos"
    type = "multiple"
    choices = "Parker"
    ```

## mod.lua

This file is used as the entry point for the mod. It is executed in its entirety after the game launches and all mods have been parsed.

Code that modifies game variables and objects (e.g. `game.get_player().salvage = 100000`) cannot be written directly into the script as they will not be valid at the time that Sledge runs it, resulting in errors. Instead, a callback function can be registered to specific game events. When a game event is triggered, the callback function will be run and execute the code inside it.

For example, to properly edit the player's salvage, an event that guarantees the player will be valid must be chosen, such as [`defines.event.save_loaded`](../lua/api/defines/event.md#save_loaded):

```lua title="mod.lua"
-- The function that will be called when the save_loaded event is triggered.
local function save_loaded_callback()
    -- Get the player and edit their salvage.
    game.get_player().salvage = 100000

    -- Optionally log the player's salvage after we edited it.
    sledge.log("The player's salvage is now " .. game.get_player().salvage)
end

-- Register the callback function to the save_loaded event.
sledge.register_event(defines.event.save_loaded, save_loaded_callback)
```

### Writing log messages

Use the following functions to log messages:

- [`sledge.log`](../lua/api/sledge.md#log)
- [`sledge.log_warn`](../lua/api/sledge.md#log)
- [`sledge.log_error`](../lua/api/sledge.md#log)

All log messages are automatically prefixed by the mod's ID and written to the `sledge.log` file:

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

### Retrieving options

!!! note

    All mods have a [`mod`](../lua/api/global.md#mod) variable of the [`types.mod_info`](../lua/api/types/mod_info.md) type in their script environments. Use this variable to access the metadata of the script's associated mod.

If a mod has defined options in its metadata, access it through the [`types.mod_info.options`](../lua/api/types/mod_info.md#options) table, using the option's name as a key. Its return value will depend on the type of option it was defined as, where `checkbox` returns a `boolean`, `key` returns a [`defines.key`](../lua/api/defines/key.md), and `multiple` and `custom` return a `string`.

For example, here is how to define all four types of options in the metadata and retrieve them in Lua:

```toml title="mod.toml"
id = "my_name.my_mod"
name = "My Mod"
authors = ["my_name"]
version = "1.0.0"

[[options]]
name = "Toggle choice"
type = "checkbox"
default = false

[[options]]
name = "Key choice"
type = "key"
choices = "Parker"

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

-- This is nil because it doesn't exist.
local non_existing_choice = mod.options["Another choice"]
```