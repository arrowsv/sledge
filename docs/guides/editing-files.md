# Editing files

Files are edited by completely overriding files or editing certain parts of XML files.

Unlike other mod managers, Sledge does not permanently overwrite the game's files or require backups. Mods can be instantly toggled through the launcher.

## Adding or overriding files

The [`sledge.register_file`](../lua/api/sledge.md#register_file) and [`sledge.register_packfile`](../lua/api/sledge.md#register_packfile) functions are used for adding or overriding files. These are akin to the `<Replace>` feature from the `modinfo.xml` format.

These functions should be written at the root level of a script to ensure it is called immediately by Sledge at launch. While it is technically possible for these functions to be be called later, its results can be unpredictable.

!!! warning

    Overriding `.xtbl` files will cause compatibility issues between mods that override the same file and result in edits being overwritten. Instead, use the [`sledge.register_xml_edit`](#editing-xml-files) function.

### sledge.register_file

Registering with this function can either add a new file or override an existing file depending on whether the file name already exists in the game. Use the function by placing the file inside the mod's folder (alongside `mod.toml` and `mod.lua` or a subfolder) and pass the path to the file to the function.

!!! note

    If a file is registered that does not already exist in the game, it is considered "added", but it won't be used unless the game explicitly looks for a file with that name.

To demonstrate, we will use the `No Tutorial` mod that replaces a `.scriptx` file:

```
📁 mods/
└── 📁 No Tutorial/
    ├── 📁 files/
    │   └── 📄 terr01_tutorial.scriptx
    ├── 📄 mod.toml
    └── 📄 mod.lua
```

```lua title="mod.lua"
sledge.register_file("files/terr01_tutorial.scriptx")
```

### sledge.register_packfile

!!! note

    Files registered with `sledge.register_file` always take precedence over files registered with `sledge.register_packfile`, even if the packfile was registered after. This may change in the future.

Registering with this function is identical to `sledge.register_file` but only allows `.vpp_pc` files. All files within the packfile will be added to the game. For example:

```
📁 mods/
└── 📁 My Mod/
    ├── 📁 files/
    │   └── 📄 custom.vpp_pc
    ├── 📄 mod.toml
    └── 📄 mod.lua
```

```lua title="mod.lua"
sledge.register_packfile("files/custom.vpp_pc")
```

## Editing XML files

The [`sledge.register_xml_edit`](../lua/api/sledge.md#register_xml_edit) function is used for editing XML files. This is akin to the `<Edit>` feature from the `modinfo.xml` format, allowing multiple mods to edit XML files without overwriting each other. The following file formats are supported for XML editing:

- `.xtbl`
- `.dtodx`
- `.gtodx`

!!! note

    `.scriptx` files are not supported as they have a non-standard XML format made specifically for the game's scripting system. Use the `sledge.register_file` function instead and fully replace the file with any desired edits.

The `sledge.register_xml_edit` function requires the name of the file to edit and a callback function that takes a [`types.xml_node`](../lua/api/types/xml_node.md) parameter:

```lua title="mod.lua"
sledge.register_xml_edit("character.xtbl", function(document) end)
```

Sledge will pass the XML document to the callback function as a `types.xml_node`, allowing the script to modify its contents before it is sent back to the game.

We will use a snippet of `spawn_group_vehicle.xtbl` to demonstrate navigating and modifying the document:

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

### Retrieving nodes
XML nodes are retrieved using the following functions:

- [`types.xml_node:get`](../lua/api/types/xml_node.md#get)
- [`types.xml_node:get_from_path`](../lua/api/types/xml_node.md#get_from_path)
- [`types.xml_node:get_multiple_from_path`](../lua/api/types/xml_node.md#get_multiple_from_path)
- [`types.xml_node:children`](../lua/api/types/xml_node.md#children)
- [`types.xml_node:parent`](../lua/api/types/xml_node.md#parent)

!!! info

    The `types.xml_node:get_from_path` and `types.xml_node:get_multiple_from_path` functions use an XPath string to find nodes. Learn more about the XPath syntax [here](https://www.w3schools.com/xml/xpath_syntax.asp).

```lua title="mod.lua"
sledge.register_xml_edit("spawn_group_vehicle.xtbl", function(document) 
    -- Get the <spawn_group_vehicle> node with the <Name> "Amb_Parker".
    --
    -- Note that "//" is placed at the beginning of the XPath string. This
    -- finds nodes from the current node that match the selection no matter
    -- where they are. In this case, we haven't retrieved the <root><Table> 
    -- nodes yet to get to the <spawn_group_vehicle> nodes, but 
    -- using "//" will bypass them and search through the entire document.
    local group = document:get_from_path("//spawn_group_vehicle[Name='Amb_Parker']")

    -- Get the <Name> node and log its value, which will be "Amb_Parker".
    local group_name = group:get("Name").value
    sledge.log("Group name: " .. group_name)

    -- Get the <vehicle_list> node.
    local vehicle_list = group:get("vehicle_list")

    -- Get the children of <vehicle_list> as a table and log the value of each.
    local vehicle_types = vehicle_list:children()
    sledge.log("Vehicle list (children):")
    for _, type in ipairs(vehicle_types) do
        sledge.log("Vehicle type: " .. type.value)
    end

    -- The <vehicle_type> nodes can also be retrieved using the
    -- get_multiple_from_path function, even though the children
    -- function does what we want.
    local vehicle_types = group:get_multiple_from_path("vehicle_list/vehicle_type")
    sledge.log("Vehicle list (get_multiple_from_path):")
    for _, type in ipairs(vehicle_types) do
        sledge.log("Vehicle type: " .. type.value)
    end
end)
```

### Modifying nodes
XML nodes are modified using the following fields and functions:

- [`types.xml_node.value`](../lua/api/types/xml_node.md#value)
- [`types.xml_node:add`](../lua/api/types/xml_node.md#add)
- [`types.xml_node:delete`](../lua/api/types/xml_node.md#delete)

```lua title="mod.lua"
sledge.register_xml_edit("spawn_group_vehicle.xtbl", function(document) 
    -- Get the <spawn_group_vehicle> node with the <Name> "Amb_Manufacturing".
    local group = document:get_from_path("//spawn_group_vehicle[Name='Amb_Manufacturing']")

    -- Get the existing <vehicle_list> node and delete it.
    group:get("vehicle_list"):delete()

    -- Create a new <vehicle_list> node.
    local vehicle_list = group:add("vehicle_list")
    
    -- Add new <vehicle_type> nodes to the <vehicle_list> node.
    local first_vehicle = vehicle_list:add("vehicle_type", "Col_FuelTanker_1")
    local second_vehicle = vehicle_list:add("vehicle_type", "Col_FixedFlatbed")

    -- Change the first vehicle's value to "Min_Emergency_1".
    first_vehicle.value = "Min_Emergency_1"

    -- Find the second vehicle we added and delete it.
    vehicle_list:get_from_path("vehicle_type='Col_FixedFlatbed'"):delete()
end)
```

### More examples

The following examples show existing mods made in the `modinfo.xml` format and their `mod.toml` and `mod.lua` equivalents.

#### [More Salvage](https://www.factionfiles.com/ff.php?action=file&id=7725)

=== "modinfo.xml"

    ```xml
    <Mod Name="More Salvage">
        <Author>arrows</Author>
        <Description>Increases the amount of salvage gathered when picked up. Does not affect mission completion rewards.</Description>
        <Changes>
            <Edit File="data\misc.vpp_pc\salvage.xtbl" LIST_ACTION="COMBINE_BY_FIELD:Name">
                <Material>
                    <Name>metal</Name>
                    <Value>20</Value>
                </Material>
                <Material>
                    <Name>ore</Name>
                    <Value>35</Value>
                </Material>
                <Material>
                    <Name>chemical</Name>
                    <Value>45</Value>
                </Material>
            </Edit>
        </Changes>
    </Mod>
    ```

=== "mod.toml"

    ```toml
    id = "arrows.more_salvage"
    name = "More Salvage"
    authors = ["arrows"]
    description = "Increases the amount of salvage given when it is picked up."
    version = "1.0.0"

    [[options]]
    name = "Metal"
    type = "custom"
    default = "20"

    [[options]]
    name = "Ore"
    type = "custom"
    default = "35"

    [[options]]
    name = "Chemical"
    type = "custom"
    default = "45"
    ```

=== "mod.lua"

    ```lua
    local metal_amount = mod.options["Metal"]
    local ore_amount = mod.options["Ore"]
    local chemical_amount = mod.options["Chemical"]

    sledge.register_xml_edit("salvage.xtbl", function(document)
        local table = document:get("root"):get("Table")

        local metal = table:get_from_path("Material[Name='metal']")
        if metal:exists() then
            metal:get("Value").value = metal_amount
        end

        local ore = table:get_from_path("Material[Name='ore']")
        if ore:exists() then
            ore:get("Value").value = ore_amount
        end

        local chemical = table:get_from_path("Material[Name='chemical']")
        if chemical:exists() then
            chemical:get("Value").value = chemical_amount
        end
    end)
    ```

??? note "Snippet of salvage.xtbl"

    ```xml
    <root>
    <Table>
        <Material>
            <Name>metal</Name>
            <_Editor>
                <Category>Entries</Category>
                </_Editor>
            <Item_list>
                <Item_3d>spawned_salvage</Item_3d>
                <Item_3d>spawned_salvage2</Item_3d>
                <Item_3d>spawned_salvage3</Item_3d>
                <Item_3d>spawned_salvage4</Item_3d>
                <Item_3d>spawned_salvage5</Item_3d>
                <Item_3d>spawned_salvage6</Item_3d>
                <Item_3d>spawned_salvage7</Item_3d>
                <Item_3d>spawned_salvage8</Item_3d>
                </Item_list>
            <Value>1</Value>
            </Material>
        <Material>
            <Name>ore</Name>
            <_Editor>
                <Category>Entries</Category>
                </_Editor>
            <Item_list>
                <Item_3d>ore_salvage_1</Item_3d>
                </Item_list>
            <Value>5</Value>
            </Material>
        <Material>
            <Name>chemical</Name>
            <_Editor>
                <Category>Entries</Category>
                </_Editor>
            <Item_list>
                <Item_3d>placed_salvage</Item_3d>
                </Item_list>
            <Value>2</Value>
            </Material>
        </Table>
    </root>
    ```

#### [Nano Assault Rifle](https://www.factionfiles.com/ff.php?action=file&id=2839)

=== "modinfo.xml"

    ```xml
    <Mod Name="Nano Assault Rifle">
        <Author>Ace Spacer</Author>
        <Description>Turn the Nano rifle in to more of an assault rifle!</Description>
        <WebLink Name="factionfiles link">http://www.factionfiles.com/</WebLink>
        <Changes>
            <Edit File="build\pc\cache\misc.vpp\weapons.xtbl" LIST_ACTION="COMBINE_BY_FIELD:Name,_Editor\Category">

            <Weapon>
                <Name>nano_rifle</Name>
                <Trigger_Type>automatic</Trigger_Type>
                <Magazine_Size>60</Magazine_Size>
                <Max_Rounds>250</Max_Rounds>
                <Range_Max>150</Range_Max>
                <Range_Red>250</Range_Red>
                <Default_Refire_Delay>100</Default_Refire_Delay>
                <_Editor>
                    <Category>Entries:Guerilla</Category>
                    </_Editor>
                <Ammo_Box_Restock>150</Ammo_Box_Restock>
                <Num_Magazines>6</Num_Magazines>
                <Reload_Delay>200</Reload_Delay>
            </Weapon>

            </Edit>

        </Changes>
    </Mod>
    ```

=== "mod.toml"

    ```toml
    id = "acespacer.nano_assault_rifle"
    name = "Nano Assault Rifle"
    authors = ["Ace Spacer"]
    description = "Turns the nano rifle into an assault rifle."
    version = "1.0.0"
    ```

=== "mod.lua"

    ```lua
    sledge.register_xml_edit("weapons.xtbl", function(document)
        local nano_rifle = document:get_from_path("//Weapon[Unique_ID='17']")
        nano_rifle:get("Trigger_Type").value = "automatic"
        nano_rifle:get("Magazine_Size").value = "60"
        nano_rifle:get("Max_Rounds").value = "250"
        nano_rifle:get("Range_Max").value = "150"
        nano_rifle:get("Range_Red").value = "250"
        nano_rifle:get("Default_Refire_Delay").value = "100"
        nano_rifle:get("Ammo_Box_Restock").value = "150"
        nano_rifle:get("Num_Magazines").value = "6"
        nano_rifle:get("Reload_Delay").value = "200"
    end)
    ```

    !!! note

        The `nano_rifle` `<Weapon>` node is retrieved using its `<Unique_ID>` value because most weapons have a duplicate entry with an indentical `<Name>` value that is used only for the multiplayer version of a weapon.

??? note "Snippet of weapons.xtbl"

    ```xml
    <root>
    <Table>
        <Weapon>
            <Name>nano_rifle</Name>
            <Weapon_Class>nano_rifle</Weapon_Class>
            <Trigger_Type>single</Trigger_Type>
            <Ammo_Type>bullet</Ammo_Type>
            <Magazine_Size>5</Magazine_Size>
            <Max_Rounds>15</Max_Rounds>
            <Range_Max>120</Range_Max>
            <Range_Red>200</Range_Red>
            <Default_Refire_Delay>350</Default_Refire_Delay>
            <Damage_Scaling_Max>
                <NPC_Damage>450</NPC_Damage>
                <Player_Damage>180</Player_Damage>
                <Vehicle_Damage>1200</Vehicle_Damage>
                <Threshold>100</Threshold>
                <Player_Vehicle_Damage>-1</Player_Vehicle_Damage>
            </Damage_Scaling_Max>
            <Explosion>nano_rifle_exp</Explosion>
            <Spread_Max>1.3</Spread_Max>
            <Spread_Min>0.3</Spread_Min>
            <_Editor>
                <Category>Entries:Guerilla</Category>
            </_Editor>
            <Animation_Group>Nano</Animation_Group>
            <Flags>
                <Flag>shatter</Flag>
                <Flag>can fine aim</Flag>
                <Flag>mp selectable</Flag>
                <Flag>is obvious weapon</Flag>
            </Flags>
            <Min_Engagement_Distance>0.0</Min_Engagement_Distance>
            <Max_Engagement_Distance>120</Max_Engagement_Distance>
            <NPC_Spread_Max>2.0</NPC_Spread_Max>
            <NPC_Spread_Min>0.4</NPC_Spread_Min>
            <To_Spread_Max>2</To_Spread_Max>
            <To_Spread_Min>1250</To_Spread_Min>
            <Item_3d>nano_rifle</Item_3d>
            <Inventory_Item>nano_rifle</Inventory_Item>
            <MeleeAttacks>
                <StandingPrimary>ar_melee</StandingPrimary>
                <StandingSecondary>ar_melee2</StandingSecondary>
                <CrouchingPrimary>ar_melee</CrouchingPrimary>
                <CrouchingSecondary>ar_melee2</CrouchingSecondary>
            </MeleeAttacks>
            <Sounds>
                <Sound_Group>assault rifle</Sound_Group>
                <Fire_Sound>WEP_NANO_RIFLE_PC_FIRE</Fire_Sound>
                <Sound_Radius>50</Sound_Radius>
                <No_Ammo_Sound>WEP_NANO_RIFLE_DRYFIRE_PC</No_Ammo_Sound>
                <Special_Sound>WEP_NANO_RIFLE_CLOUD</Special_Sound>
                <Secondary_Sound>WEP_NANO_RIFLE_CLOUD_FLESH</Secondary_Sound>
                <Upgrade_Sound>WEP_NANO_RIFLE_CLOUD_VEHICLE</Upgrade_Sound>
                <NPC_Fire_Sounds>
                    <NPC_Fire_Sound>WEP_NANO_RIFLE_NPC_FIRE</NPC_Fire_Sound>
                </NPC_Fire_Sounds>
            </Sounds>
            <Visuals>
                <Muzzle_Flash>wep_nanorifle_flash_a</Muzzle_Flash>
                <Fire_Camera_Shake>weapon_fire_nano</Fire_Camera_Shake>
                <Fire_Camera_Shake_Ignore_Disabled>true</Fire_Camera_Shake_Ignore_Disabled>
                <Tracer_Frequency>1</Tracer_Frequency>
                <Tracer_Effect>wep_nanorifle_trail_a</Tracer_Effect>
                <Player_Hit_Camera_Shake>npc_nano_rifle</Player_Hit_Camera_Shake>
            </Visuals>
            <Recoil_Kick>0.2</Recoil_Kick>
            <Spread_Fine_Aim_Min>0.15</Spread_Fine_Aim_Min>
            <Spread_Fine_Aim_Max>0.75</Spread_Fine_Aim_Max>
            <Spread_Multiplier_Run>0.8</Spread_Multiplier_Run>
            <NPC_Firing_Pattern>Default Pistol</NPC_Firing_Pattern>
            <Ammo_Box_Restock>15</Ammo_Box_Restock>
            <Num_Magazines>3</Num_Magazines>
            <Max_AI_Penetrating_Distance>40.0</Max_AI_Penetrating_Distance>
            <icon_name>ui_hud_weapon_icon_nano</icon_name>
            <reticule_name>ui_hud_reti_nano</reticule_name>
            <dummy>False</dummy>
            <Damage_Scaling_Min>
                <Threshold>0</Threshold>
                <NPC_Damage>450</NPC_Damage>
                <Player_Damage>180</Player_Damage>
                <Vehicle_Damage>1200</Vehicle_Damage>
                <Player_Vehicle_Damage>-1</Player_Vehicle_Damage>
            </Damage_Scaling_Min>
            <mp_kill_phrase>HM_KILL_PHRASE_NANO</mp_kill_phrase>
            <Headshot_Multiplier>2.0</Headshot_Multiplier>
            <Unique_ID>17</Unique_ID>
            <Melee_Group>Large_Ranged_Melee_Set</Melee_Group>
            <Reload_Delay>250</Reload_Delay>
            <Default_team>Guerilla</Default_team>
            <Zoom_Magnification>1.65</Zoom_Magnification>
            <fine_aim_reticule>ui_hud_reti_nano2</fine_aim_reticule>
            <Max_Rounds_Upgrade>30</Max_Rounds_Upgrade>
            <aim_assist>1.0</aim_assist>
        </Weapon>
    </Table>
    </root>
    ```
