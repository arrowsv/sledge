sledge.register_xml_edit("weapons.xtbl", function(document)
    local nano_rifle = document:get_from_path("//Weapon[Name='nano_rifle']")
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
