The `mod.toml` file is a metadata file used by Sledge to identify and load mods. It goes in the root of your mod's folder, next to `mod.lua`.

The format of this file is part of the mod API, so changes to it are listed in the [API's changelog](changelog.md).

```toml title="mod.toml"
id = "my_name.my_mod"
name = "My Mod"
authors = ["My Name", "Another Name"]
description = "A description of my mod."
version = "1.0.0"
api_version = "1.1.0"
```

## Fields

| <div style="width: 100px;">Field</div> | Type | Required | Description |
| --- | --- | --- | --- |
| `id`          | `string` | :lucide-check: | Unique identifier in `my_name.my_mod` format (lowercase `a-z`, `0-9`, `.`, `_`). Should match your folder name.|
| `name`        | `string` | :lucide-check: | The display name of your mod. |
| `authors`     | `string[]` | :lucide-check: | List of authors. |
| `version`     | `string` | :lucide-check: | Version following [Semantic Versioning](https://semver.org) (`major.minor.patch`). See [versioning rules](#versioning-rules).
| `api_version` | `string` | :lucide-check: | Target mod API version (`major.minor.patch`). Warns users if major version mismatches or minor is lower. |
| `description` | `string` | :lucide-x: | A short summary of your mod.

### Versioning rules

When updating the `version` field:

- Increment the major version (`1.0.0` -> `2.0.0`) when breaking changes are made.
- Increment the minor version (`1.0.0` -> `1.1.0`) when new features are added.
- Increment the patch version (`1.0.0` -> `1.0.1`) when bug fixes are made.

## Options

Options are settings configured by players in the launcher. Each value can be read by your mod's Lua script. Each option entry begins with `[[options]]`.

```toml
[[options]]
name = "Vehicle choice"
type = "multiple"
default = "EDF Scout"
choices = ["EDF APC", "EDF Scout"]
```

### Fields

| Field | <div style="width: 200px;">Type</div> | Required | Description |
| --- | --- | --- | --- |
| `name`        | `string` | :lucide-check:     | The name of the option. |
| `type`        | `string[]` | :lucide-check:   | The type of the option (see [available types](#available-types)). |
| `choices`     | `string|(string|table)[]` | :lucide-minus: | Selection list (see [writing multiple choices](#writing-multiple-choices)). Required when `type = "multiple"`. |
| `tooltip`     | `string` | :lucide-x:         | Tooltip shown when hovering over the option. |
| `default`     | `string` | :lucide-x:         | Initial value. Differs based on type (see [available types](#available-types)). |

### Available types

| Type | Default | Description |
| --- | --- | --- |
| `multiple`  | First entry in `choices` | Dropdown choice box populated using `choices`. |
| `key`       | `"none"`                 | Dropdown choice box populated with [`enums.key`](lua/enums.key.md) values. |
| `checkbox`  | `"false"`                | Toggle switch allowing a `true` or `false` value. |
| `integer `  | `"0"`                    | Integer input box. |
| `floating`  | `"0.0"`                  | Floating-point input box. |
| `custom`    | `""`                     | Unrestricted text input box. |

### Writing multiple choices

The `choices` field defines the selection list or copies choices from another option. It is applicable only when `type = "multiple"`.

- **String array** - Each string acts as both the display name and the script value.
- **Table array** - Each table defines a custom display name and value using `{ name = "Display", value = ... }`.

```toml
# String values
choices = [
    "Choice 1", 
    "Choice 2"
]

# Custom display names for string values
choices = [
    { name = "Low", value = "1" },
    { name = "Medium", value = "2" },
    { name = "High", value = "3" },
    "4" # String values can still be used alongside a table
]

# Array values
choices = [
    { name = "Supply Truck", value = ["Min_SupplyTruck_1", "Min_SupplyTruck_2", "Min_SupplyTruck_3"] },
    { name = "Supply Truck (Turret)", value = ["Min_SupplyTruck_MG1", "Min_SupplyTruck_MG2", "Min_SupplyTruck_MG3"] }
]

# Copy choices from another option
choices = "Other option name"
```

!!! warning "Consistent return types"
    Avoid mixing string values and array values within the same `choices` list. Keep choice values as either all strings or all arrays of strings so your Lua script can safely handle the return type.

!!! info "Copying choices"
    An option can copy another option's choices by passing that option's name as a string. The target option must also be of type `multiple`.

### Examples

=== "multiple"

    ```toml title="mod.toml"
    [[options]]
    name = "Choices"
    type = "multiple"
    default = "Choice 2"
    choices = [
        "Choice 1",
        "Choice 2"
    ]

    [[options]]
    name = "Copied choices"
    type = "multiple"
    choices = "Choices"

    [[options]]
    name = "Custom display names"
    type = "multiple"
    default = "Medium"
    choices = [
        { name = "Low", value = "1" },
        { name = "Medium", value = "2" },
        { name = "High", value = "3" }
    ]

    [[options]]
    name = "Array choice values"
    type = "multiple"
    default = "Option A"
    choices = [
        { name = "Option A", value = ["1", "2"] },
        { name = "Option B", value = ["3", "4"] }
    ]
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

    [[options]]
    name = "Enable another feature"
    type = "checkbox"
    default = true
    ```

=== "integer"

    ```toml title="mod.toml"
    [[options]]
    name = "Amount"
    type = "integer"
    default = 100
    ```

=== "floating"

    ```toml title="mod.toml"
    [[options]]
    name = "Height"
    type = "floating"
    default = 5.2
    ```

=== "custom"

    ```toml title="mod.toml"
    [[options]]
    name = "Character name"
    type = "custom"
    default = "Samanya"
    ```

## Full example

```toml title="mod.toml"
id = "arrows.toggle_hud_weather"
name = "Toggle HUD/Weather"
authors = ["arrows"]
version = "1.0.1"
api_version = "1.0.0"

[[options]]
name = "HUD key"
type = "key"
default = "numpad_1"

[[options]]
name = "Fog key"
type = "key"
default = "numpad_2"

[[options]]
name = "Wind key"
type = "key"
default = "numpad_3"
```