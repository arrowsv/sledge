local metal_amount = mod:get_option("Metal")
local ore_amount = mod:get_option("Ore")
local chemical_amount = mod:get_option("Chemical")

mod:register_event(defines.event.parse_xml, function(data)
    local table = data.document:get("root"):get("Table")
    if not table then return end

    local metal = table:get_from_path("Material[Name='metal']")
    if metal then
        metal:get("Value"):set(metal_amount)
    end

    local ore = table:get_from_path("Material[Name='ore']")
    if ore then
        ore:get("Value"):set(ore_amount)
    end

    local chemical = table:get_from_path("Material[Name='chemical']")
    if chemical then
        chemical:get("Value"):set(chemical_amount)
    end
end, { filter = "salvage.xtbl" })
