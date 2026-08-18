local vehicle_choices = {
    ["EDF APC"] = {"EDF_APC_noturret", "EDF_APC_noturret2", "EDF_APC_noturret3", "EDF_APC_noturret4"},
    ["EDF APC (Turret)"] = {"EDF_APC-A_1", "EDF_APC-A_2", "EDF_APC-A_3", "EDF_APC-A_4", "EDF_APC-A_Gauss", "EDF_APC-A_Gauss2", "EDF_APC-A_Gauss3", "EDF_APC-A_Gauss4"},

    ["EDF Scout"] = {"EDF_ScoutNoTurret", "EDF_ScoutNoTurret2", "EDF_ScoutNoTurret3", "EDF_ScoutNoTurret4"},
    ["EDF Scout (Turret)"] = {"EDF_Scout_1", "EDF_Scout_2", "EDF_Scout_3", "EDF_Scout_4", "EDF_Scout_Gauss", "EDF_Scout_Gauss2", "EDF_Scout_Gauss3", "EDF_Scout_Gauss4"},

    ["EDF Staff"] = {"EDF_StaffCar_NoTurret", "EDF_StaffCar_NoTurret2", "EDF_StaffCar_NoTurret3"},
    ["EDF Staff (Turret)"] = {"EDF_StaffCar_1", "EDF_StaffCar_2", "EDF_StaffCar_3", "EDF_StaffCar_Gauss", "EDF_StaffCar_Gauss2", "EDF_StaffCar_Gauss3"},

    ["EDF Supply Truck"] = {"EDF_Supplytruck_NoTurret", "EDF_Supplytruck_NTurret2", "EDF_Supplytruck_NTurret3"},
    ["EDF Supply Truck (Turret)"] = {"EDF_Supplytruck_1", "EDF_Supplytruck_2", "EDF_Supplytruck_3", "EDF_Supplytruck_Gauss", "EDF_Supplytruck_Gauss2", "EDF_Supplytruck_Gauss3"},

    ["EDF Flyer"] = {"EDF_AAXAir_1", "EDF_AAXAir_2", "EDF_AAXAir_Gauss"},

    ["EDF Bomber"] = {"EDF_ABXAir_1"},

    ["Civilian Supply Truck"] = {"Min_SupplyTruck_1", "Min_SupplyTruck_2", "Min_SupplyTruck_3"},
    ["Civilian Supply Truck (Turret)"] = {"Min_SupplyTruck_MG1", "Min_SupplyTruck_MG2", "Min_SupplyTruck_MG3"},

    ["Civilian Garbage Truck"] = {"Col_TrashTruck_1"},
    ["Civilian Garbage Truck (Turret)"] = {"Col_TrashTruck_MG1"},

    ["Civilian Dump Truck"] = {"Min_DumpTruck_1", "Min_DumpTruck_2", "Min_DumpTruck_3"},

    ["Civilian Pickup"] = {"Min_LightPickup_1", "Min_LightPickup_2", "Min_LightPickup_3"},
    ["Civilian Pickup (Turret)"] = {"Min_LightPickup_MG1", "Min_LightPickup_MG2", "Min_LightPickup_MG3"},

    ["Civilian Mining ATV"] = {"Min_ATV_1", "Min_ATV_2", "Min_ATV_3"},
    ["Civilian Mining ATV (Turret)"] = {"Min_ATV_MG1", "Min_ATV_MG2", "Min_ATV_MG3"},

    ["Civilian Mini Hauler"] = {"Col_Mini_Hauler_1", "Col_Mini_Hauler_2", "Col_Mini_Hauler_3"},

    ["Civilian Rover"] = {"Min_Rover-A_1", "Min_Rover-A_2", "Min_Rover-A_3"},
    ["Civilian Rover (Turret)"] = {"Min_Rover-A_DMG1", "Min_Rover-A_DMG2", "Min_Rover-A_DMG3", "Min_Rover-A_MG1", "Min_Rover-A_MG2", "Min_Rover-A_MG3", "Min_Rover-A_DRR1", "Min_Rover-A_DRR2", "Min_Rover-A_DRR3"},

    ["Civilian Emergency Rover"] = {"Min_Emergency_1"},

    ["Civilian Flatbed"] = {"Col_FixedFlatbed", "Col_FixedFlatbed2", "Col_FixedFlatbed3"},
    ["Civilian Flatbed (Turret)"] = {"Col_FixedFlatbed_2"},

    ["Civilian Fuel Tanker"] = {"Col_FuelTanker_1", "Col_FuelTanker_2", "Col_FuelTanker_3"},

    ["Civilian Supercar"] = {"Civ_ResRunner_1"},

    ["Civilian Luxury Coupé"] = {"Civ_ResRunner-C_1"},

    ["Civilian Luxury SUV"] = {"Civ_ResLuxury-C_1"},

    ["Civilian Luxury Taxi"] = {"Col_Taxi_1", "Col_Taxi_2", "Col_Taxi_3"},

    ["Civilian Luxury Bus"] = {"Col_Caravan_1", "Col_Caravan_2", "Col_Caravan_3"},

    ["Marauder Jetter"] = {"Mar_Jetter_1"},

    ["Marauder Raider"] = {"Mar_Raider_1"},

    ["Light Walker"] = {"Walker_Min", "Walker_Min2", "Walker_Min3"},

    ["Heavy Walker"] = {"Walker_Civilian", "Walker_Civilian2", "Walker_Civilian3"},

    ["Combat Walker"] = {"Walker_Flamer"},

    ["Tank"] = {"EDF_MediumTank-A_1", "EDF_MediumTank-A_2", "EDF_MediumTank-A_3", "EDF_MediumTank-A_4"},

    ["Heavy Tank"] = {"EDF_HeavyTank-A_1", "EDF_HeavyTank-A_2", "EDF_HeavyTank-A_3", "EDF_HeavyTank-A_4"},

    ["Rocket Tank"] = {"EDF_ArtTank_1"},

    ["Heavy Rocket Tank"] = {"EDF_ArtTank_2"},

    ["Bulldozer"] = {"Min_Bulldozer_1"},

    ["Mars Rover"] = {"MarsRover1"},
}

mod:register_event(defines.event.parse_xml, function(e)
    local table = e.document:get("root"):get("Table")

    local spawn_group = table:get_from_path("//spawn_group_vehicle[Name='Amb_0410Safehouse']")
    if spawn_group then
        spawn_group:get("vehicle_list"):delete()
        local vehicle_list = spawn_group:add("vehicle_list")
        for _, vehicle in ipairs(vehicle_choices[mod:get_option("Parker")]) do
            vehicle_list:add("vehicle_type", vehicle)
        end
    end

    local spawn_group = table:get_from_path("//spawn_group_vehicle[Name='Amb_DustSafehouse']")
    if spawn_group then
        spawn_group:get("vehicle_list"):delete()
        local vehicle_list = spawn_group:add("vehicle_list")
        for _, vehicle in ipairs(vehicle_choices[mod:get_option("Dust")]) do
            vehicle_list:add("vehicle_type", vehicle)
        end
    end

    local spawn_group = table:get_from_path("//spawn_group_vehicle[Name='Amb_BadlandsSafehouse']")
    if spawn_group then
        spawn_group:get("vehicle_list"):delete()
        local vehicle_list = spawn_group:add("vehicle_list")
        for _, vehicle in ipairs(vehicle_choices[mod:get_option("Badlands")]) do
            vehicle_list:add("vehicle_type", vehicle)
        end
    end

    local spawn_group = table:get_from_path("//spawn_group_vehicle[Name='Amb_OasisSafehouse']")
    if spawn_group then
        spawn_group:get("vehicle_list"):delete()
        local vehicle_list = spawn_group:add("vehicle_list")
        for _, vehicle in ipairs(vehicle_choices[mod:get_option("Oasis")]) do
            vehicle_list:add("vehicle_type", vehicle)
        end
    end

    local spawn_group = table:get_from_path("//spawn_group_vehicle[Name='Amb_EosSafehouse']")
    if spawn_group then
        spawn_group:get("vehicle_list"):delete()
        local vehicle_list = spawn_group:add("vehicle_list")
        for _, vehicle in ipairs(vehicle_choices[mod:get_option("Eos")]) do
            vehicle_list:add("vehicle_type", vehicle)
        end
    end
end, {filter = "spawn_group_vehicle.xtbl"})
