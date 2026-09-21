sledge.register_xml_edit("weapons.xtbl", function(document)
    local artillery = document:get_from_path("//Weapon[Name='ab_rpg_kill_player']")
    local projectile = artillery:get("Projectile_Info")
    projectile:get("Max_Speed").value = 1
    projectile:get("Gravity").value = 0
    projectile:get("Start_Speed").value = 0
end)
