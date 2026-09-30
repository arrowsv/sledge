local teleports = {
    {
        sector = "Parker",
        locations = {
            { name = "Tutorial", position = types.vector.new(-2328, 30, -2318) },
            { name = "Safehouse", position = types.vector.new(-1878, 23, -1452) },
            { name = "Abandoned Safehouse", position = types.vector.new(-1813, 22, -1160) },
            { name = "Sand Sifter Factory", position = types.vector.new(-1833, 21, -1250) },
            { name = "Ore Processing Plant", position = types.vector.new(-1625, 38, -1178) },
            { name = "Mountain", position = types.vector.new(-1737, 90, -1324) },
        }
    },
    {
        sector = "Dust",
        locations = {
            { name = "Safehouse (North)", position = types.vector.new(-408, 40, -809) },
            { name = "Safehouse (South)", position = types.vector.new(-82, 31, -2425) },
            { name = "Quarry", position = types.vector.new(-887, -20, -1249) },
            { name = "Town of Dust", position = types.vector.new(108, 23, -1367) },
            { name = "Tharsis Point Windfarm", position = types.vector.new(-244, 74, -224) },
            { name = "Town Hall", position = types.vector.new(307, 50, -720) },
            { name = "EDF Executive Housing", position = types.vector.new(248, 21, -1159) },
            { name = "Chemical Depot", position = types.vector.new(-208, 3, -2298) },
            { name = "Mohole", position = types.vector.new(-801, 71, -589) },
        }
    },
    {
        sector = "Badlands",
        locations = {
            { name = "Safehouse", position = types.vector.new(2411, 58, -239) },
            { name = "Safehouse (Marauder)", position = types.vector.new(2458, 58, -1210) },
            { name = "EDF Outpost", position = types.vector.new(1098, -8, -205) },
            { name = "Mohole", position = types.vector.new(1420, -32, -734) },
            { name = "Harrington Memorial Bridge", position = types.vector.new(948, -5, -417) },
            { name = "EDF Barracks", position = types.vector.new(900, 2, -885) },
            { name = "Marauder Territory", position = types.vector.new(1072, 3, -1366) },
            { name = "Ultor Ruins", position = types.vector.new(1280, 20, -1448) },
            { name = "Irradiated Zone", position = types.vector.new(1685, 28, -1093) },
            { name = "Old Coot", position = types.vector.new(1497, -12, -766) },
            { name = "Mars Rover", position = types.vector.new(2100, 29, -484) },
        }
    },
    {
        sector = "Oasis",
        locations = {
            { name = "Safehouse", position = types.vector.new(1434, 18, 691) },
            { name = "Residential District", position = types.vector.new(1728, 17, 211) },
            { name = "Industrial District", position = types.vector.new(176, 33, 777) },
            { name = "EDF Barracks", position = types.vector.new(916, 23, 240) },
            { name = "Reactor Core", position = types.vector.new(640, 50, 384) },
        }
    },
    {
        sector = "Free Fire Zone",
        locations = {
            { name = "Minor Safehouse", position = types.vector.new(-1908, 25, -779) },
            { name = "Artillery Border (South)", position = types.vector.new(-1606, 0, -785) },
            { name = "Artillery Border (North)", position = types.vector.new(-1813, 5, -250) },
            { name = "Artillery Base", position = types.vector.new(-1752, 9, -132) },
            { name = "Artillery Gun", position = types.vector.new(-1944, 38, -65) },
        }
    },
    {
        sector = "Eos",
        locations = {
            { name = "Safehouse (West)", position = types.vector.new(-1726, 44, 438) },
            { name = "Safehouse (East)", position = types.vector.new(-1391, 30, 561) },
            { name = "South Border", position = types.vector.new(-1715, 18, 23) },
            { name = "Residential District", position = types.vector.new(-1753, -2, 764) },
            { name = "Martian Council", position = types.vector.new(-1174, 17, 1386) },
            { name = "EDF Central Command (Outside)", position = types.vector.new(-1428, 5, 2013) },
            { name = "EDF Central Command (Inside)", position = types.vector.new(-1458, 5, 2050) },
            { name = "EDF Central Command (Main Building)", position = types.vector.new(-1474, 27, 2397) },
        }
    },
    {
        sector = "Mount Vogel",
        locations = {
            { name = "Border", position = types.vector.new(-1017, 6, 2474) },
            { name = "Base", position = types.vector.new(-670, 47, 2423) },
            { name = "Peak", position = types.vector.new(-285, 183, 2423) },
        }
    }
}

local position = types.vector.new(0, 0, 0)

sledge.register_window("Teleports", function()
    local player = game.get_player()
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
end, { requires_gameplay = true })
