Use the [`sledge.register_xml_edit`](/lua/api/sledge#register_xml_edit) function to edit XML files. Instead of replacing a whole file, your mod changes only the values and entries it needs, so multiple mods can edit the same file without overwriting each other. If you're coming from the `modinfo.xml` format, this takes the place of `<Edit>`.

The following file formats are supported:

- `.xtbl`
- `.dtodx`
- `.gtodx`

!!! warning

    `.scriptx` files are not supported because they use a non-standard XML format made specifically for the game's scripting system. Instead, use [`sledge.register_file`](overriding-files) to fully replace the file with your edits included.

!!! info "Call this function at the root level"

    Write this function at the root level of `mod.lua`, not inside an event callback, so Sledge calls them immediately at launch. Calling them later is technically possible, but the results can be unpredictable.

## Registering an edit

The `sledge.register_xml_edit` function takes the name of the file to edit and a callback function. Sledge calls the callback when the game loads that file, passing the XML document as a [`types.xml_node`](/lua/api/types/xml_node). The callback can then modify the document before Sledge sends it back to the game.

```lua title="mod.lua"
sledge.register_xml_edit("spawn_group_vehicle.xtbl", function(document)
    -- Read and modify the document here.
end)
```

Pass only the file's name, such as `spawn_group_vehicle.xtbl`, and not its path inside the game's data files. Like the other file functions, call `sledge.register_xml_edit` at the top level of `mod.lua`.

The rest of this page uses a snippet of `spawn_group_vehicle.xtbl` to demonstrate navigating and modifying a document:

```xml title="spawn_group_vehicle.xtbl"
<root>
<Table>
    <spawn_group_vehicle>
        <Name>Amb_Parker</Name>
        <vehicle_list>
            <vehicle_type>Min_LightPickup_1</vehicle_type>
            <vehicle_type>Min_LightPickup_2</vehicle_type>
            <vehicle_type>Min_LightPickup_3</vehicle_type>
            <vehicle_type>Col_Mini_Hauler_1</vehicle_type>
            <vehicle_type>Col_Mini_Hauler_2</vehicle_type>
            <vehicle_type>Col_Mini_Hauler_3</vehicle_type>
            <vehicle_type>Min_DumpTruck_1</vehicle_type>
            <vehicle_type>Min_DumpTruck_2</vehicle_type>
            <vehicle_type>Min_DumpTruck_3</vehicle_type>
            <vehicle_type>Min_SupplyTruck_1</vehicle_type>
            <vehicle_type>Min_SupplyTruck_2</vehicle_type>
            <vehicle_type>Min_SupplyTruck_3</vehicle_type>
        </vehicle_list>
    </spawn_group_vehicle>
    <spawn_group_vehicle>
        <Name>Amb_Manufacturing</Name>
        <vehicle_list>
            <vehicle_type>Min_Rover-A_1</vehicle_type>
            <vehicle_type>Min_Rover-A_2</vehicle_type>
            <vehicle_type>Min_Rover-A_3</vehicle_type>
            <vehicle_type>Min_SupplyTruck_1</vehicle_type>
            <vehicle_type>Min_SupplyTruck_2</vehicle_type>
            <vehicle_type>Min_SupplyTruck_3</vehicle_type>
            <vehicle_type>Col_TrashTruck_1</vehicle_type>
            <vehicle_type>Col_Mini_Hauler_1</vehicle_type>
            <vehicle_type>Col_Mini_Hauler_2</vehicle_type>
            <vehicle_type>Col_Mini_Hauler_3</vehicle_type>
        </vehicle_list>
    </spawn_group_vehicle>
</Table>
</root>
```

## Retrieving nodes

Use these functions to navigate the document:

[`types.xml_node:get`](/lua/api/types/xml_node#get)
:   Returns a node's child by its name.

---

[`types.xml_node:get_from_path`](/lua/api/types/xml_node#get_from_path)
:   Returns the first node that matches the given XPath.

---

[`types.xml_node:get_multiple_from_path`](/lua/api/types/xml_node#get_multiple_from_path)
:   Returns all nodes that match the given XPath.

---

[`types.xml_node:children`](/lua/api/types/xml_node#children)
:   Returns all children of the node.

---

[`types.xml_node:parent`](/lua/api/types/xml_node#parent)
:   Returns the parent of the node.

---

[`types.xml_node:exists`](/lua/api/types/xml_node#exists)
:   Returns whether the node exists.

!!! info

    The `get_from_path` and `get_multiple_from_path` functions find nodes using an [XPath](https://www.w3schools.com/xml/xpath_syntax.asp) string.

    An XPath beginning with `//` searches the entire document from the current node, no matter how deeply nested the matches are. This lets you skip navigating through `<root>` and `<Table>` to reach the `<spawn_group_vehicle>` nodes.

```lua title="mod.lua"
sledge.register_xml_edit("spawn_group_vehicle.xtbl", function(document)
    -- Get the <spawn_group_vehicle> node with the <Name> "Amb_Parker".
    local group = document:get_from_path("//spawn_group_vehicle[Name='Amb_Parker']")

    -- Get the <Name> node and log its value, which is "Amb_Parker".
    local group_name = group:get("Name").value
    sledge.log("Group name: " .. group_name)

    -- Get the <vehicle_list> node.
    local vehicle_list = group:get("vehicle_list")

    -- Get the children of <vehicle_list> and log the value of each.
    sledge.log("Vehicle list (children):")
    for _, vehicle in ipairs(vehicle_list:children()) do
        sledge.log("Vehicle type: " .. vehicle.value)
    end

    -- The same <vehicle_type> nodes can be retrieved with an XPath. Here,
    -- children is simpler, but get_multiple_from_path is useful when the
    -- nodes you want aren't all direct children.
    sledge.log("Vehicle list (get_multiple_from_path):")
    for _, vehicle in ipairs(group:get_multiple_from_path("vehicle_list/vehicle_type")) do
        sledge.log("Vehicle type: " .. vehicle.value)
    end

    -- Get the parent of <vehicle_list>, which is the <spawn_group_vehicle> node.
    local same_group = vehicle_list:parent()

    -- Check whether a node exists.
    local missing = group:get_from_path("not_a_real_node")
    if not missing:exists() then
        sledge.log("not_a_real_node was not found.")
    end
end)
```

## Modifying nodes

Use these fields and functions to change the document:

[`types.xml_node.name`](/lua/api/types/xml_node#name)
:   Name of the node.

---

[`types.xml_node.value`](/lua/api/types/xml_node#value)
:   Value of the node.

---

[`types.xml_node:add`](/lua/api/types/xml_node#add)
:   Adds a new child node and returns it.

---

[`types.xml_node:delete`](/lua/api/types/xml_node#delete)
:   Deletes the node.

The most common edit is adding to or changing an existing entry. For example, to add a vehicle to the `Amb_Parker` group:

```lua title="mod.lua"
sledge.register_xml_edit("spawn_group_vehicle.xtbl", function(document)
    local group = document:get_from_path("//spawn_group_vehicle[Name = 'Amb_Parker']")
    local vehicle_list = group:get("vehicle_list")

    -- Add a new <vehicle_type> node with a value to the end of the list.
    vehicle_list:add("vehicle_type", "Col_FuelTanker_1")
end)
```

Nodes can also be changed in place, removed, and rebuilt. This example replaces the entire `Amb_Manufacturing` vehicle list:

```lua title="mod.lua"
sledge.register_xml_edit("spawn_group_vehicle.xtbl", function(document)
    local group = document:get_from_path("//spawn_group_vehicle[Name='Amb_Manufacturing']")

    -- Delete the existing <vehicle_list> node.
    group:get("vehicle_list"):delete()

    -- Create a new <vehicle_list> node and add <vehicle_type> nodes to it.
    local vehicle_list = group:add("vehicle_list")
    local first_vehicle = vehicle_list:add("vehicle_type", "Col_FuelTanker_1")
    vehicle_list:add("vehicle_type", "Col_FixedFlatbed")

    -- Change the first vehicle's value.
    first_vehicle.value = "Min_Emergency_1"

    -- Find the "Col_FixedFlatbed" node we added and delete it.
    vehicle_list:get_from_path("vehicle_type='Col_FixedFlatbed'"):delete()

    -- Log the name of the node, which is "vehicle_type".
    sledge.log(first_vehicle.name)
end)
```

## Using options in an edit

Edits are often driven by a mod's options. Read the options with `mod.options`, then assign the result to a node's `value`. See [Mapping options to values](mod_lua#mapping-options-to-values) if the display names in your options differ from the values the game needs.

For complete mods that combine options and XML edits, see [Converting from modinfo.xml](converting-from-modinfo).