local speed = mod.options["Speed"]

sledge.register_xml_edit("character.xtbl", function(document)
    local rfg_PC = document:get_from_path("//Character[Name='rfg_PC']")
    rfg_PC:get("max_speed").value = speed
end)
