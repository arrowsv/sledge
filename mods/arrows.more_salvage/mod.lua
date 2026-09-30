local metal_amount = mod.options["Metal"]
local ore_amount = mod.options["Ore"]
local chemical_amount = mod.options["Chemical"]

sledge.register_xml_edit("salvage.xtbl", function(document)
    local table = document:get("root"):get("Table")

    local metal = table:get_from_path("Material[Name='metal']")
    if metal:exists() then
        metal:get("Value").value = metal_amount
    end

    local ore = table:get_from_path("Material[Name='ore']")
    if ore:exists() then
        ore:get("Value").value = ore_amount
    end

    local chemical = table:get_from_path("Material[Name='chemical']")
    if chemical:exists() then
        chemical:get("Value").value = chemical_amount
    end
end)
