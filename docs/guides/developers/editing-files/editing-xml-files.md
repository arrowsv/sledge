Use [`sledge.register_xml_edit`](../../../api/lua/namespaces.sledge.md#register_xml_edit) to modify XML values safely so multiple mods can coexist without overwriting each other.

The following formats are supported:

- `.xtbl`
- `.dtodx`
- `.gtodx`

!!! warning "Unsupported"

    `.scriptx` files are not supported because they use a non-standard XML format made specifically for the game's scripting system. Instead, use [`sledge.register_file`](overriding-files.md) to fully replace the file with your edits included.

!!! info "Call at the root level"

    Always place `sledge.register_xml_edit` at the root level of `mod.lua`, outside of any event callback, so Sledge registers it immediately at launch.

## Registering an edit

Pass the file name and a callback function that receives an XML document as a [`types.xml_node`](../../../api/lua/types.xml_node.md):

``` lua title="mod.lua"
sledge.register_xml_edit("spawn_group_vehicle.xtbl", function(document)
    local group = document:get_from_path("//spawn_group_vehicle[Name='Amb_Parker']")
    sledge.log("Found group name: " .. group:get("Name").value)
end)
```

## Navigating nodes

Use [XPath queries](https://www.w3schools.com/xml/xpath_syntax.asp) or node methods to traverse the document:

| Method                                                                                            | Description                                     |
| ------------------------------------------------------------------------------------------------- | ----------------------------------------------- |
| [`node:get(name)`](../../../api/lua/types.xml_node.md#get)                                        | Returns a node's child by name.                 |
| [`node:get_from_path(query)`](../../../api/lua/types.xml_node.md#get_from_path)                   | Returns the first node matching an XPath query. |
| [`node:get_multiple_from_path(query)`](../../../api/lua/types.xml_node.md#get_multiple_from_path) | Returns all nodes matching an XPath query.      |
| [`node:children()`](../../../api/lua/types.xml_node.md#children)                                  | Returns all children of the node.               |
| [`node:parent()`](../../../api/lua/types.xml_node.md#parent)                                      | Returns the parent node.                        |
| [`node:exists()`](../../../api/lua/types.xml_node.md#exists)                                      | Returns whether the node exists.                |

## Modifying nodes

Use these functions and fields to alter nodes:

| Field/Method | Description |
| --- | --- |
| [`node.name`](../../../api/lua/types.xml_node.md#name) | Get or set a node's name. |
| [`node.value`](../../../api/lua/types.xml_node.md#value) | Get or set a node's text value. |
| [`node:add(name, value)`](../../../api/lua/types.xml_node.md#add) | Adds a new child node and returns it. |
| [`node:add(node)`](../../../api/lua/types.xml_node.md#add) | Copies and adds a node as a child. |
| [`node:delete()`](../../../api/lua/types.xml_node.md#delete) | Deletes the node. |

## Examples

The examples below all work on this file. It has been shortened for readability:

``` xml title="spawn_group_vehicle.xtbl"
<root>
<Table>
    <spawn_group_vehicle>
        <Name>Amb_Parker</Name>
        <vehicle_list>
            <vehicle_type>Min_LightPickup_1</vehicle_type>
            <vehicle_type>Col_Mini_Hauler_1</vehicle_type>
            <vehicle_type>Min_DumpTruck_1</vehicle_type>
            <vehicle_type>Min_SupplyTruck_1</vehicle_type>
        </vehicle_list>
    </spawn_group_vehicle>
    <spawn_group_vehicle>
        <Name>Amb_Manufacturing</Name>
        <vehicle_list>
            <vehicle_type>Min_Rover-A_1</vehicle_type>
            <vehicle_type>Col_TrashTruck_1</vehicle_type>
            <vehicle_type>Col_Mini_Hauler_1</vehicle_type>
        </vehicle_list>
    </spawn_group_vehicle>
</Table>
</root>
```

Every example goes inside `sledge.register_xml_edit`. The callback receives `document`, the root of the file. The snippets below assume this setup:

```lua title="mod.lua"
sledge.register_xml_edit("spawn_group_vehicle.xtbl", function(document)
    local group = document:get_from_path("//spawn_group_vehicle[Name='Amb_Parker']")

    -- Snippets go here.
end)
```

!!! note
    A path starting with `//` searches the whole document. A path without it, like `vehicle_list/vehicle_type`, starts from the node you call it on.

### Reading nodes

```lua
-- Get a direct child by name.
local vehicle_list = group:get("vehicle_list")
sledge.log(group:get("Name").value) -- Amb_Parker

-- Loop over all children.
for _, vehicle in ipairs(vehicle_list:children()) do
    sledge.log(vehicle.value) -- Min_LightPickup_1, Col_Mini_Hauler_1, Min_DumpTruck_1, Min_SupplyTruck_1
end

-- Get all matches for an XPath. Same as children(), but it
-- also works when the nodes you want are nested deeper or need filtering.
local vehicles = group:get_multiple_from_path("vehicle_list/vehicle_type")

-- Go up one level.
local same_group = vehicle_list:parent() -- the <spawn_group_vehicle> node
```

A query that finds nothing will still return a node rather than `nil`. Use `node:exists()` to check:

```lua
local missing = group:get_from_path("not_a_real_node")
if not missing:exists() then
    sledge.log("Not found.")
end
```

!!! note

    If the `XML warnings enabled` config option is enabled, warnings will appear in `sledge.log` when a script uses `get`, `get_from_path`, or `get_multiple_from_path` and the resulting node doesn't exist.

### Adding a node

```lua
group:get("vehicle_list"):add("vehicle_type", "Col_FuelTanker_1")
```

```xml
<vehicle_list>
    <vehicle_type>Min_LightPickup_1</vehicle_type>
    <vehicle_type>Col_Mini_Hauler_1</vehicle_type>
    <vehicle_type>Min_DumpTruck_1</vehicle_type>
    <vehicle_type>Min_SupplyTruck_1</vehicle_type>
    <vehicle_type>Col_FuelTanker_1</vehicle_type> <!-- added -->
</vehicle_list>
```

### Changing a value

```lua
local node = group:get_from_path("vehicle_list/vehicle_type[.='Min_DumpTruck_1']")
node.value = "Min_Emergency_1"
```

```xml
<vehicle_type>Min_Emergency_1</vehicle_type> <!-- was Min_DumpTruck_1 -->
```

### Deleting a node

```lua
group:get_from_path("vehicle_list/vehicle_type[.='Col_Mini_Hauler_1']"):delete()
```

```xml
<vehicle_list>
    <vehicle_type>Min_LightPickup_1</vehicle_type>
    <vehicle_type>Min_Emergency_1</vehicle_type>
    <vehicle_type>Min_SupplyTruck_1</vehicle_type>
</vehicle_list>
```

### Replacing a whole list

Replace a list by deleting and recreating the node.

``` lua
local manufacturing = document:get_from_path("//spawn_group_vehicle[Name='Amb_Manufacturing']")

manufacturing:get("vehicle_list"):delete()

local list = manufacturing:add("vehicle_list")
list:add("vehicle_type", "Col_FuelTanker_1")
list:add("vehicle_type", "Col_FixedFlatbed")
```

``` xml
<vehicle_list>
    <vehicle_type>Col_FuelTanker_1</vehicle_type>
    <vehicle_type>Col_FixedFlatbed</vehicle_type>
</vehicle_list>
```

!!! tip
    If you only need to change some nodes within a list, edit or delete them in place instead of replacing the whole list. That keeps any entries you didn't touch, and it plays better with other mods that edit the same file.