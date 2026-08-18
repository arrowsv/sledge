local speed = mod:get_option("Speed")

mod:register_event(defines.event.parse_xml, function(data)
    local table = data.document:get("root"):get("Table")
    local rfg_PC = table:get_from_path(".//Character[Name='rfg_PC']")
    rfg_PC:get("max_speed"):set(speed)
end, { filter = "character.xtbl" })
