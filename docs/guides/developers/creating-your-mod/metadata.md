The `mod.toml` file is a metadata file used by Sledge to identify and load mods. It must be placed in the root level of your mod's folder, alongside the `mod.lua` file:

```
📁 mods/
└── 📁 my_name.my_mod/
    ├── 📄 mod.toml
    └── 📄 mod.lua
```

## Fields

`id` (`string`)
:   The unique identifier of the mod. This must be formatted as `my_name.my_mod` and only contain lowercase letters `a-z`, numbers `0-9`, and the symbols `.` and `_`. Ideally, the identifier and your mod's folder name should be the same for consistency sake.

---

`name` (`string`)
:   The display name of the mod. This will be used in the launcher's mod list.

---

`authors` (`string[]`)
:   The authors of the mod, written as an array of strings.

---

`description` (`string`) <small>optional</small>
:   The description of the mod.

---

`version` (`string`)
:   The version of the mod. This must follow the `major.minor.patch` format from the [Semantic Versioning](https://semver.org) specification. For a mod's initial release, start at `1.0.0`, where major is `1`, minor is `0`, and patch is `0`.

    - Increment the major version (`1.0.0` -> `2.0.0`) when breaking changes are made.
    - Increment the minor version (`1.0.0` -> `1.1.0`) when new features are added.
    - Increment the patch version (`1.0.0` -> `1.0.1`) when bug fixes are made.

---

`sledge_version` (`string`)
:   The versions of Sledge the mod works with, written as a version range. If a player's Sledge version is outside this range, the launcher will warn them that the mod may not work correctly. See [Version ranges](#version-ranges) for more information.


```toml title="mod.toml"
id = "my_name.my_mod"
name = "My Mod"
authors = ["My Name", "Another Name"]
description = "A description of my mod."
version = "1.0.0"
sledge_version = ">=0.2.0"
```

## Version ranges

The `sledge_version` field tells players which versions of Sledge your mod was made for. In most cases, you only need to write the oldest version your mod works on:

```toml title="mod.toml"
sledge_version = ">=0.2.0"
```

This means "Sledge 0.2.0 or newer".

### Examples

| Value                | Meaning                                         |
| -------------------- | ----------------------------------------------- |
| `">=0.2.0"`          | Version 0.2.0 or newer                          |
| `">=0.2.0 <0.4.0"`   | Version 0.2.0 or newer, but older than 0.4.0    |
| `"0.2.0"`            | Exactly version 0.2.0                           |

### Choosing a range

- Use the lowest version that has everything your mod needs. If your mod uses a feature added in 0.2.0, write `>=0.2.0`.
- Only add an upper limit if you know your mod breaks on newer versions. Guessing an upper limit will cause false warnings when new versions release.
- Avoid using `*` because it matches every version and doesn't tell the player what versions are actually compatible.

!!! tip "Updating your range"
    When you update your mod to use a newer Sledge feature, raise the lower bound and increment your mod's `version` accordingly.

## Options

Options can be defined that will be available for players to configure in the launcher. Each option's chosen value can be later accessed from your mod's script.

Each option starts with `[[options]]`, which adds a new entry to the `options` array.

### Fields

`name` (`string`)
:   The name of the option.

---

`tooltip` (`string`) <small>optional</small>
:   The tooltip that appears when hovering over the option.

---

`type` (`string`)
:   The type of the option. The following types are available:

    `multiple`
    :   A multiple choice box populated using the `choices` field.

    ---

    `key`
    :   A multiple choice box populated with [`defines.key`](../../../lua/api/defines.key.md) values.

    ---

    `checkbox`
    :   A checkbox that allows a `true` or `false` value.

    ---

    `custom`
    :   A text box that allows a custom value.

---

`default` (`string, boolean`) <small>optional</small>
:   The default choice of the option. The value to write for this field depends on the option's type:

    `multiple` (`string`)
    :   A choice from the `choices` array. If not present, defaults to the first string in the `choices` array.

    --- 

    `key` (`string`)
    :   A string representation of a [`defines.key`](../../../lua/api/defines.key.md) field (such as `"f2"`). If not present, defaults to `none`.

    ---

    `checkbox` (`boolean`)
    :   A `true` or `false` value. If not present, defaults to `false`.

    ---

    `custom` (`string`)
    :   A custom value. If not present, defaults to an empty string.

---

`choices` (`string[]`)
:   An array of strings available in the multiple choice box. This is only applicable to the `multiple` type.

    !!! info "Copying choices"
        An option can copy the choices of another option by writing that option's name as a string. The option being copied must also be of type `multiple`.

### Examples

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

## Full example

```toml title="mod.toml"
id = "arrows.safehouse_vehicle_selector"
name = "Safehouse Vehicle Selector"
authors = ["arrows"]
description = "Select which vehicle spawns at each safehouse."
version = "1.0.0"
sledge_version = ">=0.1.0"

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