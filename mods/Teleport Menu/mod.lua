local teleports = mod:import("teleports")
local position = types.vector.new(0, 0, 0)

local function teleports_window()
    if not game.is_in_gameplay() then
        gui.text('A save must be loaded before using this menu.')
        return
    end

    local player = game.get_player()
    if not player then return end

    local width, _height = gui.get_available_space()
    gui.push_item_width(width)

    local new_values, changed = gui.input_float_3('', { position.x, position.y, position.z })
    if changed then
        position = types.vector.new(new_values[1], new_values[2], new_values[3])
    end

    gui.pop_item_width()

    if gui.button('Teleport', width, 0) then
        player:teleport(position)
    end

    gui.separator_text('Presets')
    if (gui.begin_tab_bar('TeleportTabs')) then
        for _, data in ipairs(teleports) do
            local sector = data.sector
            local locations = data.locations

            if (gui.begin_tab_item(sector)) then
                for _, info in ipairs(locations) do
                    if gui.button(info.name, width, 0) then
                        position = info.position
                    end
                    if gui.begin_tooltip() then
                        gui.text('X: ' .. info.position.x)
                        gui.text('Y: ' .. info.position.y)
                        gui.text('Z: ' .. info.position.z)
                        gui.end_tooltip()
                    end
                end
                gui.end_tab_item()
            end
        end
        gui.end_tab_bar()
    end
end

mod:register_window("Teleports", teleports_window)