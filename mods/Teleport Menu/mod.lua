local teleports = mod:import("teleports")
local position = types.vector.new(0, 0, 0)

sledge.register_window("Teleports", function()
    if not game.is_in_gameplay() then
        gui.text('A save must be loaded before using this menu.')
        return
    end

    local player = game.get_player()
    if not player then return end

    gui.property_table('Position', function()
        gui.property_row('X', function()
            local width = gui.get_available_space()
            gui.set_next_item_width(width)
            gui.input_float(position.x, function(v)
                position.x = v
            end)
        end)

        gui.property_row('Y', function()
            local width = gui.get_available_space()
            gui.set_next_item_width(width)
            gui.input_float(position.y, function(v)
                position.y = v
            end)
        end)

        gui.property_row('Z', function()
            local width = gui.get_available_space()
            gui.set_next_item_width(width)
            gui.input_float(position.z, function(v)
                position.z = v
            end)
        end)
    end)

    local width = gui.get_available_space()
    gui.button('Teleport', function()
        player:teleport(position)
    end, {width = width})
    gui.button('Sync current position', function()
        position = types.vector.new(player.position)
    end, {width = width})

    gui.separator('Presets')
    gui.tab_bar('Teleports', function()
        for _, data in ipairs(teleports) do
            local sector = data.sector
            local locations = data.locations

            gui.tab_item(sector, function()
                for _, info in ipairs(locations) do
                    gui.button(info.name, function()
                        position = info.position
                    end, {width = width})
                    gui.tooltip(function()
                        gui.text('X: ' .. info.position.x)
                        gui.text('Y: ' .. info.position.y)
                        gui.text('Z: ' .. info.position.z)
                    end)
                end
            end)
        end
    end)
end)
