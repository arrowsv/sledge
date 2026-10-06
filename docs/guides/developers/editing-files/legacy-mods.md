The following examples show existing mods made in the older `modinfo.xml` format alongside their `mod.toml` and `mod.lua` equivalents. 

!!! info

    Ensure you have read the [`sledge.register_xml_edit`](editing-xml-files) and [`sledge.register_file`](overriding-files) pages before continuing.

## Differences

- **File names** - A `modinfo.xml` edit gives the file's full path, such as `data\misc.vpp_pc\salvage.xtbl`. `sledge.register_xml_edit` only needs the file's name, such as `salvage.xtbl`.
- **Matching entries** - The `LIST_ACTION` attribute tells the game how to match entries in the file. For example, `COMBINE_BY_FIELD:Name` means "find the entry whose `Name` matches, and edit it". In Lua you do this yourself by finding the node with an XPath, such as `Material[Name = 'metal']`, and then changing its values. When `LIST_ACTION` lists several fields, such as `Name,_Editor\Category`, combine them in the XPath with `and`, such as `Weapon[Name = 'nano_rifle' and _Editor/Category = 'Entries:Guerilla']`.

## Examples

### [More Salvage](https://www.factionfiles.com/ff.php?action=file&id=7725)

This mod changes how much salvage the player gets from three materials. Each amount is an option the player can configure, and the script reads the options and applies them to the matching materials.

=== "Old"

    ```xml title="modinfo.xml"
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

    ```
    📁 mods/
    └── 📁 More Salvage/
        └── 📄 modinfo.xml
    ```

=== "New"

    ```toml title="mod.toml"
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

    ```lua title="mod.lua"
    local metal_amount = mod.options["Metal"]
    local ore_amount = mod.options["Ore"]
    local chemical_amount = mod.options["Chemical"]

    sledge.register_xml_edit("salvage.xtbl", function(document)
        local table = document:get("root"):get("Table")

        local metal = table:get_from_path("Material[Name='metal']")
        metal:get("Value").value = metal_amount

        local ore = table:get_from_path("Material[Name='ore']")
        ore:get("Value").value = ore_amount

        local chemical = table:get_from_path("Material[Name='chemical']")
        chemical:get("Value").value = chemical_amount
    end)
    ```

    ```
    📁 mods/
    └── 📁 arrows.more_salvage/
        ├── 📄 mod.toml
        └── 📄 mod.lua
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

### [Nano Assault Rifle](https://www.factionfiles.com/ff.php?action=file&id=2839)

This mod edits several fields on one weapon. In `modinfo.xml`, `COMBINE_BY_FIELD:Name,_Editor\Category` matches the weapon by both its `Name` and its `_Editor/Category`. In Lua, the same match is written as one XPath with both conditions joined by `and`. This is needed because the file contains more than one weapon named `nano_rifle`, and only the one in the `Entries:Guerilla` category should be edited.

=== "Old"

    ```xml title="modinfo.xml"
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

    ```
    📁 mods/
    └── 📁 Nano Assault Rifle/
        └── 📄 modinfo.xml
    ```

=== "New"

    ```toml title="mod.toml"
    id = "acespacer.nano_assault_rifle"
    name = "Nano Assault Rifle"
    authors = ["Ace Spacer"]
    description = "Turns the nano rifle into an assault rifle."
    version = "1.0.0"
    ```

    ```lua title="mod.lua"
    sledge.register_xml_edit("weapons.xtbl", function(document)
        -- Match the weapon by both its <Name> and its <_Editor><Category>.
        local nano_rifle = document:get_from_path("//Weapon[Name = 'nano_rifle' and _Editor/Category = 'Entries:Guerilla']")

        nano_rifle:get("Trigger_Type").value = "automatic"
        nano_rifle:get("Magazine_Size").value = 60
        nano_rifle:get("Max_Rounds").value = 250
        nano_rifle:get("Range_Max").value = 150
        nano_rifle:get("Range_Red").value = 250
        nano_rifle:get("Default_Refire_Delay").value = 100
        nano_rifle:get("Ammo_Box_Restock").value = 150
        nano_rifle:get("Num_Magazines").value = 6
        nano_rifle:get("Reload_Delay").value = 200
    end)
    ```

    ```
    📁 mods/
    └── 📁 acespacer.nano_assault_rifle/
        ├── 📄 mod.toml
        └── 📄 mod.lua
    ```

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

### [Extreme Hammer](https://www.factionfiles.com/ff.php?action=file&id=4695)

This mod replaces the `melee.xtbl` file using `<Replace>` to increase the Sledgehammer's impact level. Ideally, the mod would have used `<Edit>` to make its changes because it is an `.xtbl` file, but this is for demonstration purposes.

=== "Old"

    ```xml
    <Mod Name="Extreme Hammer">
        <Author>SimpleArrows</Author>
        <Description> Increases the impact of the hammer on NPC's and vehicles to an extreme level!</Description>
        <Changes>
            <Replace File="data\misc.vpp\melee.xtbl" NewFile="file\melee.xtbl" />
        </Changes>
    </Mod>
    ```

    ```
    📁 mods/
    └── 📁 Extreme Hammer/
        ├── 📁 file/
        │   └── 📄 melee.xtbl
        └── 📄 modinfo.xml
    ```

=== "New"

    ```toml title="mod.toml"
    id = "arrows.extreme_hammer"
    name = "Extreme Hammer"
    authors = ["arrows"]
    description = "Increases the impact of the hammer on NPC's and vehicles to an extreme level!"
    version = "1.0.0"
    ```

    ```lua title="mod.lua"
    sledge.register_file("files/melee.xtbl")
    ```

    ```
    📁 mods/
    └── 📁 arrows.extreme_hammer/
        ├── 📁 files/
        │   └── 📄 melee.xtbl
        ├── 📄 mod.toml
        └── 📄 mod.lua
    ```