sledge.register_xml_edit("character.xtbl", function(document)
    local table = document:get("root"):get("Table")
    local heights = table:get_multiple_from_path(".//Height")
    for _, height in ipairs(heights) do
        height.value = 0.5
    end
end)
