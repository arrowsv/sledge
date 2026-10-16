The following examples show existing mods made in the older `modinfo.xml` format alongside their `mod.toml` and `mod.lua` equivalents. 

## Differences

- **File names** - `modinfo.xml` required full file paths (e.g., `data\misc.vpp_pc\salvage.xtbl`), whereas `sledge.register_xml_edit` only requires the file name (`salvage.xtbl`).
- **Matching entries** - Instead of using `LIST_ACTION="COMBINE_BY_FIELD:Name"`, you find entries in Lua using explicit XPath conditions (e.g., `Material[Name='metal']`).

## Examples

### Nano Assault Rifle

=== "Old"

    ```
    📁 mods/
    └── 📁 Nano Assault Rifle/
        └── 📄 modinfo.xml
    ```

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

=== "New"

    ```
    📁 mods/
    └── 📁 acespacer.nano_assault_rifle/
        ├── 📄 mod.toml
        └── 📄 mod.lua
    ```
    
    ```toml title="mod.toml"
    id = "acespacer.nano_assault_rifle"
    name = "Nano Assault Rifle"
    authors = ["Ace Spacer"]
    description = "Turns the nano rifle into an assault rifle."
    version = "1.0.0"
    api_version = "1.0.0"
    ```

    ```lua title="mod.lua"
    sledge.register_xml_edit("weapons.xtbl", function(document)
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

### No Tutorial

=== "Old"

    ```
    📁 mods/
    └── 📁 No Tutorial/
        ├── 📁 file/
        │   └── 📄 terr01_tutorial.scriptx
        └── 📄 modinfo.xml
    ```

    ```xml title="modinfo.xml"
    <Mod Name="No Tutorial">
        <Author>arrows, moneyl</Author>
        <Description>Skips the tutorial when starting a new game.</Description>
        <Changes>
		    <Replace File="data\zonescript_terr01.vpp\terr01_tutorial.scriptx" NewFile="file\terr01_tutorial.scriptx" />
        </Changes>
    </Mod>
    ```

=== "New"

    ```
    📁 mods/
    └── 📁 arrows.no_tutorial/
        ├── 📁 files/
        │   └── 📄 terr01_tutorial.scriptx
        ├── 📄 mod.toml
        └── 📄 mod.lua
    ```

    ```toml title="mod.toml"
    id = "arrows.no_tutorial"
    name = "No Tutorial"
    authors = ["arrows", "moneyl"]
    description = "Skips the tutorial when starting a new game."
    version = "1.0.0"
    api_version = "1.0.0"
    ```

    ```lua title="mod.lua"
    sledge.register_file("files/terr01_tutorial.xtbl")
    ```

### Safehouse Vehicle Selector

=== "Old"

    ```
    📁 mods/
    └── 📁 Safehouse Vehicle Selector/
        └── 📄 modinfo.xml
    ```

    ```xml title="modinfo.xml"
    <Mod Name="Safehouse Vehicle Selector">
        <Author>Hazard (hazard_x@gmx.net)</Author>
        <Description>Allows you to select which kind of vehicle you would like to have at each safehouse.</Description>
        <WebLink Name="Hazardous Mods">http://www.megamods.de</WebLink>
        <UserInput>
            <ListBox Name="VehicleTypeParker" DisplayName="Vehicle for Parker Safehouse">
                <Option Name="Rocket Truck">
                    <vehicle_type>Col_TrashTruck_MG1</vehicle_type>
                </Option>
                <Option Name="EDF APC">
                    <vehicle_type>EDF_APC-A_1</vehicle_type>
                    <vehicle_type>EDF_APC-A_2</vehicle_type>
                    <vehicle_type>EDF_APC-A_3</vehicle_type>
                    <vehicle_type>EDF_APC-A_4</vehicle_type>
                </Option>
                <Option Name="Machinegun Rover">
                    <vehicle_type>Min_Rover-A_DMG1</vehicle_type>
                    <vehicle_type>Min_Rover-A_DMG2</vehicle_type>
                    <vehicle_type>Min_Rover-A_DMG3</vehicle_type>
                </Option>
                <Option Name="Light Walker">
                    <vehicle_type>Walker_Min</vehicle_type>
                    <vehicle_type>Walker_Min2</vehicle_type>
                    <vehicle_type>Walker_Min3</vehicle_type>
                </Option>
                <Option Name="Heavy Walker">
                    <vehicle_type>Walker_Civilian</vehicle_type>
                    <vehicle_type>Walker_Civilian2</vehicle_type>
                    <vehicle_type>Walker_Civilian3</vehicle_type>
                </Option>
                <Option Name="Combat Walker">
                    <vehicle_type>Walker_Flamer</vehicle_type>
                </Option>
                <Option Name="Tank">
                    <vehicle_type>EDF_MediumTank-A_1</vehicle_type>
                    <vehicle_type>EDF_MediumTank-A_2</vehicle_type>
                    <vehicle_type>EDF_MediumTank-A_3</vehicle_type>
                </Option>
                <Option Name="Heavy Tank">
                    <vehicle_type>EDF_HeavyTank-A_1</vehicle_type>
                    <vehicle_type>EDF_HeavyTank-A_2</vehicle_type>
                    <vehicle_type>EDF_HeavyTank-A_3</vehicle_type>
                    <vehicle_type>EDF_HeavyTank-A_4</vehicle_type>
                </Option>
                <Option Name="Rocket Tank">
                    <vehicle_type>EDF_ArtTank_1</vehicle_type>
                </Option>
                <Option Name="Heavy Rocket Tank">
                    <vehicle_type>EDF_ArtTank_2</vehicle_type>
                </Option>
            </ListBox>

            <ListBox Name="VehicleTypeDust" DisplayName="Vehicle for Dust Safehouse" SameOptionsAs="VehicleTypeParker" />
            <ListBox Name="VehicleTypeBadlands" DisplayName="Vehicle for Badlands Safehouse" SameOptionsAs="VehicleTypeParker" />
            <ListBox Name="VehicleTypeOASIS" DisplayName="Vehicle for OASIS Safehouse" SameOptionsAs="VehicleTypeParker" />
            <ListBox Name="VehicleTypeEOS" DisplayName="Vehicle for EOS Safehouse" SameOptionsAs="VehicleTypeParker" />
        </UserInput>
        <Changes>
            <Edit File="data\misc.vpp\spawn_group_vehicle.xtbl" LIST_ACTION="COMBINE_BY_FIELD:Name">
                <spawn_group_vehicle>
                    <Name>Amb_0410Safehouse</Name>
                    <vehicle_list LIST_ACTION="REPLACE">
                    <USER_INPUT>VehicleTypeParker</USER_INPUT>
                    </vehicle_list>
                </spawn_group_vehicle>

                <spawn_group_vehicle>
                    <Name>Amb_DustSafehouse</Name>
                    <vehicle_list LIST_ACTION="REPLACE">
                    <USER_INPUT>VehicleTypeDust</USER_INPUT>
                    </vehicle_list>
                </spawn_group_vehicle>

                <spawn_group_vehicle>
                    <Name>Amb_BadlandsSafehouse</Name>
                    <vehicle_list LIST_ACTION="REPLACE">
                    <USER_INPUT>VehicleTypeBadlands</USER_INPUT>
                    </vehicle_list>
                </spawn_group_vehicle>

                <spawn_group_vehicle>
                    <Name>Amb_EosSafehouse</Name>
                    <vehicle_list LIST_ACTION="REPLACE">
                    <USER_INPUT>VehicleTypeEOS</USER_INPUT>
                    </vehicle_list>
                </spawn_group_vehicle>

                <spawn_group_vehicle>
                    <Name>Amb_OasisSafehouse</Name>
                    <vehicle_list LIST_ACTION="REPLACE">
                    <USER_INPUT>VehicleTypeOASIS</USER_INPUT>
                    </vehicle_list>
                </spawn_group_vehicle>
            </Edit>
        </Changes>
        </Mod>
    ```

=== "New"

    ```
    📁 mods/
    └── 📁 hazard.safehouse_vehicle_selector/
        ├── 📄 mod.toml
        └── 📄 mod.lua
    ```

    ```toml title="mod.toml"
    id = "hazard.safehouse_vehicle_selector"
    name = "Safehouse Vehicle Selector"
    authors = ["Hazard"]
    description = "Select which vehicle spawns at each safehouse."
    version = "1.0.0"
    api_version = "1.1.0"

    [[options]]
    name = "Parker"
    type = "multiple"
    choices = [
        { name = "EDF APC", value = ["EDF_APC_noturret", "EDF_APC_noturret2", "EDF_APC_noturret3", "EDF_APC_noturret4"] },

        { name = "EDF APC (Turret)", value = ["EDF_APC-A_1", "EDF_APC-A_2", "EDF_APC-A_3", "EDF_APC-A_4", "EDF_APC-A_Gauss", "EDF_APC-A_Gauss2", "EDF_APC-A_Gauss3", "EDF_APC-A_Gauss4"] },

        { name = "EDF Scout", value = ["EDF_ScoutNoTurret", "EDF_ScoutNoTurret2", "EDF_ScoutNoTurret3", "EDF_ScoutNoTurret4"] },

        { name = "EDF Scout (Turret)", value = ["EDF_Scout_1", "EDF_Scout_2", "EDF_Scout_3", "EDF_Scout_4", "EDF_Scout_Gauss", "EDF_Scout_Gauss2", "EDF_Scout_Gauss3", "EDF_Scout_Gauss4"] },

        { name = "EDF Staff", value = ["EDF_StaffCar_NoTurret", "EDF_StaffCar_NoTurret2", "EDF_StaffCar_NoTurret3"] },

        { name = "EDF Staff (Turret)", value = ["EDF_StaffCar_1", "EDF_StaffCar_2", "EDF_StaffCar_3", "EDF_StaffCar_Gauss", "EDF_StaffCar_Gauss2", "EDF_StaffCar_Gauss3"] },

        { name = "EDF Supply Truck", value = ["EDF_Supplytruck_NoTurret", "EDF_Supplytruck_NTurret2", "EDF_Supplytruck_NTurret3"] },

        { name = "EDF Supply Truck (Turret)", value = ["EDF_Supplytruck_1", "EDF_Supplytruck_2", "EDF_Supplytruck_3", "EDF_Supplytruck_Gauss", "EDF_Supplytruck_Gauss2", "EDF_Supplytruck_Gauss3"] },

        { name = "EDF Flyer", value = ["EDF_AAXAir_1", "EDF_AAXAir_2", "EDF_AAXAir_Gauss"] },

        { name = "EDF Bomber", value = ["EDF_ABXAir_1"] },

        { name = "Civilian Supply Truck", value = ["Min_SupplyTruck_1", "Min_SupplyTruck_2", "Min_SupplyTruck_3"] },

        { name = "Civilian Supply Truck (Turret)", value = ["Min_SupplyTruck_MG1", "Min_SupplyTruck_MG2", "Min_SupplyTruck_MG3"] },

        { name = "Civilian Garbage Truck", value = ["Col_TrashTruck_1"] },

        { name = "Civilian Garbage Truck (Turret)", value = ["Col_TrashTruck_MG1"] },

        { name = "Civilian Dump Truck", value = ["Min_DumpTruck_1", "Min_DumpTruck_2", "Min_DumpTruck_3"] },

        { name = "Civilian Pickup", value = ["Min_LightPickup_1", "Min_LightPickup_2", "Min_LightPickup_3"] },

        { name = "Civilian Pickup (Turret)", value = ["Min_LightPickup_MG1", "Min_LightPickup_MG2", "Min_LightPickup_MG3"] },

        { name = "Civilian Mining ATV", value = ["Min_ATV_1", "Min_ATV_2", "Min_ATV_3"] },

        { name = "Civilian Mining ATV (Turret)", value = ["Min_ATV_MG1", "Min_ATV_MG2", "Min_ATV_MG3"] },

        { name = "Civilian Mini Hauler", value = ["Col_Mini_Hauler_1", "Col_Mini_Hauler_2", "Col_Mini_Hauler_3"] },

        { name = "Civilian Rover", value = ["Min_Rover-A_1", "Min_Rover-A_2", "Min_Rover-A_3"] },

        { name = "Civilian Rover (Turret)", value = ["Min_Rover-A_DMG1", "Min_Rover-A_DMG2", "Min_Rover-A_DMG3", "Min_Rover-A_MG1", "Min_Rover-A_MG2", "Min_Rover-A_MG3", "Min_Rover-A_DRR1", "Min_Rover-A_DRR2", "Min_Rover-A_DRR3"] },

        { name = "Civilian Emergency Rover", value = ["Min_Emergency_1"] },

        { name = "Civilian Flatbed", value = ["Col_FixedFlatbed", "Col_FixedFlatbed2", "Col_FixedFlatbed3"] },

        { name = "Civilian Flatbed (Turret)", value = ["Col_FixedFlatbed_2"] },

        { name = "Civilian Fuel Tanker", value = ["Col_FuelTanker_1", "Col_FuelTanker_2", "Col_FuelTanker_3"] },

        { name = "Civilian Supercar", value = ["Civ_ResRunner_1"] },

        { name = "Civilian Luxury Coupé", value = ["Civ_ResRunner-C_1"] },

        { name = "Civilian Luxury SUV", value = ["Civ_ResLuxury-C_1"] },

        { name = "Civilian Luxury Taxi", value = ["Col_Taxi_1", "Col_Taxi_2", "Col_Taxi_3"] },

        { name = "Civilian Luxury Bus", value = ["Col_Caravan_1", "Col_Caravan_2", "Col_Caravan_3"] },

        { name = "Jenkins' Jetter", value = ["Min_Jetter_1"] },

        { name = "Marauder Jetter", value = ["Mar_Jetter_1"] },

        { name = "Marauder Raider", value = ["Mar_Raider_1"] },

        { name = "Light Walker", value = ["Walker_Min", "Walker_Min2", "Walker_Min3"] },

        { name = "Heavy Walker", value = ["Walker_Civilian", "Walker_Civilian2", "Walker_Civilian3"] },

        { name = "Combat Walker", value = ["Walker_Flamer"] },

        { name = "Tank", value = ["EDF_MediumTank-A_1", "EDF_MediumTank-A_2", "EDF_MediumTank-A_3", "EDF_MediumTank-A_4"] },

        { name = "Heavy Tank", value = ["EDF_HeavyTank-A_1", "EDF_HeavyTank-A_2", "EDF_HeavyTank-A_3", "EDF_HeavyTank-A_4"] },

        { name = "Rocket Tank", value = ["EDF_ArtTank_1"] },

        { name = "Heavy Rocket Tank", value = ["EDF_ArtTank_2"] },

        { name = "Bulldozer", value = ["Min_Bulldozer_1"] },

        { name = "Mars Rover", value = ["MarsRover1"] }
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

    ```lua title="mod.lua"
    local parker_choice = mod.options["Parker"]
    local dust_choice = mod.options["Dust"]
    local badlands_choice = mod.options["Badlands"]
    local oasis_choice = mod.options["Oasis"]
    local eos_choice = mod.options["Eos"]

    sledge.register_xml_edit("spawn_group_vehicle.xtbl", function(document)
        local spawn_group = document:get_from_path("//spawn_group_vehicle[Name='Amb_0410Safehouse']")
        spawn_group:get("vehicle_list"):delete()
        local vehicle_list = spawn_group:add("vehicle_list")
        for _, vehicle in ipairs(parker_choice) do
            vehicle_list:add("vehicle_type", vehicle)
        end

        local spawn_group = document:get_from_path("//spawn_group_vehicle[Name='Amb_DustSafehouse']")
        spawn_group:get("vehicle_list"):delete()
        local vehicle_list = spawn_group:add("vehicle_list")
        for _, vehicle in ipairs(dust_choice) do
            vehicle_list:add("vehicle_type", vehicle)
        end

        local spawn_group = document:get_from_path("//spawn_group_vehicle[Name='Amb_BadlandsSafehouse']")
        spawn_group:get("vehicle_list"):delete()
        local vehicle_list = spawn_group:add("vehicle_list")
        for _, vehicle in ipairs(badlands_choice) do
            vehicle_list:add("vehicle_type", vehicle)
        end

        local spawn_group = document:get_from_path("//spawn_group_vehicle[Name='Amb_OasisSafehouse']")
        spawn_group:get("vehicle_list"):delete()
        local vehicle_list = spawn_group:add("vehicle_list")
        for _, vehicle in ipairs(oasis_choice) do
            vehicle_list:add("vehicle_type", vehicle)
        end

        local spawn_group = document:get_from_path("//spawn_group_vehicle[Name='Amb_EosSafehouse']")
        spawn_group:get("vehicle_list"):delete()
        local vehicle_list = spawn_group:add("vehicle_list")
        for _, vehicle in ipairs(eos_choice) do
            vehicle_list:add("vehicle_type", vehicle)
        end
    end)
    ```