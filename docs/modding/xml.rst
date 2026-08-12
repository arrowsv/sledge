==================
XML Editing
==================

This page explains how to edit XML files through the :doc:`events/parse_xml` event.

Currently, there is no built-in interface for viewing XML files. This will be added in a future version of Sledge. The easiest way to view XML files is through the `Terraform Patch archive <https://github.com/CamoRF/Red-Faction-Guerrilla-Terraform-Patch/tree/main/misc.vpp_pc/.vanilla>`_ on GitHub. Otherwise, use the `RFGM.Archiver <https://www.factionfiles.com/ff.php?action=file&id=8095>`_ tool to unpack the ``misc.vpp_pc`` file in the game's ``data`` folder.

Completely replacing files is not currently supported but may be a feature in a future version. It will not recommended to use as it can cause compatibility issues between mods that edit the same file.

For a full list of available functions, see the :lua:class:`types.xml_node` class. 

.. important::

    Knowledge of the XPath syntax is required for the :lua:meth:`types.xml_node.get_from_path` and :lua:meth:`types.xml_node.get_multiple_from_path` functions, which is explained `here <https://www.w3schools.com/xml/xpath_syntax.asp>`_.

.. note::

    All the examples following this note will use this snippet of ``spawn_group_vehicle.xtbl`` to demonstrate XML editing:

    .. code-block:: xml

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

Retrieving nodes
-----------------

Nodes are retrieved using the following functions:

* :lua:meth:`types.xml_node.get` - Returns a node's child by its name.
* :lua:meth:`types.xml_node.get_from_path` - Returns the first node that matches the given XPath.
* :lua:meth:`types.xml_node.get_multiple_from_path` - Returns all nodes that match the given XPath.
* :lua:meth:`types.xml_node.children` - Returns all children of the node.
* :lua:meth:`types.xml_node.value` - Returns the value of the node.

.. code-block:: lua

    mod:register_event(defines.event.parse_xml, function(data)
        local table = data.document:get("root"):get("Table")
    
        -- Get the <spawn_group_vehicle> node that has the name "Amb_Parker".
        local group = table:get_from_path("spawn_group_vehicle[Name='Amb_Parker']")

        -- Get the <Name> node and log its value.
        local group_name = group:get("Name"):value()
        mod:log(group_name)

        -- Get the <vehicle_list> node.
        local vehicle_list = group:get("vehicle_list")

        -- Get the children of the list and log the value of each.
        local vehicle_types = vehicle_list:children()
        for _, type in ipairs(vehicle_types) do
            mod:log(type:value())
        end

        -- The <vehicle_type> nodes can also be retrieved by using
        -- the get_multiple_from_path function, even though the children
        -- function does what we want.
        local vehicle_types = group:get_multiple_from_path("vehicle_list/vehicle_type")
        for _, type in ipairs(vehicle_types) do
            mod:log(type:value())
        end
        
    end, { filter = "spawn_group_vehicle.xtbl" })

Modifying nodes
----------------

Nodes are modified using the following functions:

* :lua:meth:`types.xml_node.set` - Sets the value of the node.
* :lua:meth:`types.xml_node.add` - Adds a new child node.
* :lua:meth:`types.xml_node.delete` - Deletes the node.

.. code-block:: lua

    mod:register_event(defines.event.parse_xml, function(data)
        local table = data.document:get("root"):get("Table")
    
        -- Get the <spawn_group_vehicle> node that has the name "Amb_Parker".
        local group = table:get_from_path("spawn_group_vehicle[Name='Amb_Parker']")

        -- Get the existing <vehicle_list> node and delete it.
        group:get("vehicle_list"):delete()

        -- Create a new <vehicle_list> node.
        local vehicle_list = group:add("vehicle_list")

        -- Add new vehicles.
        vehicle_list:add("vehicle_type", "Col_FuelTanker_1")
        vehicle_list:add("vehicle_type", "Col_FixedFlatbed")

        -- Get the <vehicle_type> node with Col_FuelTanker_1 as the value and modify it.
        vehicle_list:get_from_path("vehicle_type='Col_FuelTanker_1'"):set("Min_Emergency_1")
        
    end, { filter = "spawn_group_vehicle.xtbl" })

Mod examples
--------------

The following examples show existing XML mods made using ``modinfo.xml`` and their ``mod.lua`` equivalent.

`More Salvage <https://www.factionfiles.com/ff.php?action=file&id=7725>`_
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. tab-set::

    .. tab-item:: modinfo.xml

        .. code-block:: xml

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


    .. tab-item:: mod.lua

        .. code-block:: lua

            mod:register_event(defines.event.parse_xml, function(data)
                local table = data.document:get("root"):get("Table")
                
                local metal = table:get_from_path("Material[Name='metal']")
                metal:get("Value"):set("20")

                local ore = table:get_from_path("Material[Name='ore']")
                ore:get("Value"):set("35")

                local chemical = table:get_from_path("Material[Name='chemical']")
                chemical:get("Value"):set("45")
            end, { filter = "salvage.xtbl" })

.. dropdown:: Relevant section of salvage.xtbl

    .. code-block:: xml

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

`Nano Assault Rifle <https://www.factionfiles.com/ff.php?action=file&id=2839>`_
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. tab-set::

    .. tab-item:: modinfo.xml

        .. code-block:: xml

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

    .. tab-item:: mod.lua

        .. code-block:: lua

            mod:register_event(defines.event.parse_xml, function(data)
                local table = data.document:get("root"):get("Table")
                
                local nano_rifle = table:get_from_path("Weapon[Name='nano_rifle']")
                nano_rifle:get("Trigger_Type"):set("automatic")
                nano_rifle:get("Magazine_Size"):set("60")
                nano_rifle:get("Max_Rounds"):set("250")
                nano_rifle:get("Range_Max"):set("150")
                nano_rifle:get("Range_Red"):set("250")
                nano_rifle:get("Default_Refire_Delay"):set("100")
                nano_rifle:get("Ammo_Box_Restock"):set("150")
                nano_rifle:get("Num_Magazines"):set("6")
                nano_rifle:get("Reload_Delay"):set("200")
            end, { filter = "weapons.xtbl" })

.. dropdown:: Relevant section of weapons.xtbl

    .. code-block:: xml

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