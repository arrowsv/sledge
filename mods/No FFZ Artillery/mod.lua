mod:register_event(defines.event.parse_xml, function(e)
    local table = e.document:get("root"):get("Table")
    local artillery = table:get_from_path("//Weapon[Name='ab_rpg_kill_player']")
    if artillery then
        local projectile = artillery:get("Projectile_Info")
        projectile:get("Max_Speed"):set(1)
        projectile:get("Gravity"):set(0)
        projectile:get("Start_Speed"):set(0)
    end
end, {filter = "weapons.xtbl"})
