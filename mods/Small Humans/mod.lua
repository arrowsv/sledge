mod:register_event(defines.event.parse_xml, function(data)
    local table = data.document:get("root"):get("Table")
    local heights = table:get_multiple_from_path(".//Height")
    for _, height in ipairs(heights) do
        height:set("0.5")
    end
end, {filter = "character.xtbl"})
