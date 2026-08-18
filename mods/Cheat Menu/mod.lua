local state = { salvage_amount = 0, infinite_jetpack = false, desired_alert_level = defines.alert_level.green, lock_alert_level = false }

local function draw_window()
    if not game.is_in_gameplay() then
        gui.text('A save must be loaded before using this menu.')
        return
    end

    local player = game.get_player()
    if not player then return end

    if (gui.begin_tab_bar('CheatsTabBar')) then
        if (gui.begin_tab_item('Info')) then
            gui.separator_text('Position')

            gui.text("X:")
            gui.same_line()
            gui.text(player.position.x)

            gui.text("Y:")
            gui.same_line()
            gui.text(player.position.y)

            gui.text("Z:")
            gui.same_line()
            gui.text(player.position.z)

            gui.separator_text('Statistics')

            local new_value, changed = gui.input_int("Salvage", player.salvage)
            if changed then
                player.salvage = new_value
            end

            local new_value, changed = gui.input_int("Mined ores", player.mining_count)
            if changed then
                player.mining_count = new_value
            end

            local new_value, changed = gui.input_int("Destroyed crates", player.supply_crate_count)
            if changed then
                player.supply_crate_count = new_value
            end

            gui.separator_text("Team")

            local current_team = player.team
            local team_text = ""

            if current_team == defines.team.guerrilla then
                team_text = "Guerrilla"
            elseif current_team == defines.team.edf then
                team_text = "EDF"
            elseif current_team == defines.team.civilian then
                team_text = "Civilian"
            elseif current_team == defines.team.marauder then
                team_text = "Marauder"
            else
                team_text = "Unknown"
            end

            gui.text("Current team:")
            gui.same_line()
            gui.text(team_text)

            if gui.button("Guerrilla") then player.team = defines.team.guerrilla end
            gui.same_line()
            if gui.button("EDF") then player.team = defines.team.edf end
            gui.same_line()
            if gui.button("Civilian") then player.team = defines.team.civilian end
            gui.same_line()
            if gui.button("Marauder") then player.team = defines.team.marauder end

            local player = game.get_player()

            if not game.is_in_gameplay() or not player then
                gui.text("A save must be loaded before using this menu.")
                return
            end
        end

        if (gui.begin_tab_item('Flags')) then
            local new_value, changed = gui.checkbox("Unlimited ammo", game.unlimited_ammo)
            if changed then
                game.unlimited_ammo = new_value
            end

            local new_value, changed = gui.checkbox("Unlimited magazine ammo", game.unlimited_magazine_ammo)
            if changed then
                game.unlimited_magazine_ammo = new_value
            end

            local new_value, changed = gui.checkbox("Infinite jetpack", state.infinite_jetpack)
            if changed then
                state.infinite_jetpack = new_value
            end

            local new_value, changed = gui.checkbox("Invulnerable", player.flags.invulnerable)
            if changed then
                player.flags.invulnerable = new_value
            end

            local new_value, changed = gui.checkbox("Disable ragdoll", player.flags.disallow_flinches_and_ragdolls)
            if changed then
                player.flags.disallow_flinches_and_ragdolls = new_value
            end

            local new_value, changed = gui.checkbox("Ignored by AI", player.flags.ignored_by_ai)
            if changed then
                player.flags.ignored_by_ai = new_value
            end

            local new_value, changed = gui.checkbox("Input enabled", game.input_enabled)
            if changed then
                game.input_enabled = new_value
            end

            local new_value, changed = gui.checkbox("Camera input enabled", game.camera_input_enabled)
            if changed then
                game.camera_input_enabled = new_value
            end

            gui.end_tab_item()
        end

        if (gui.begin_tab_item('World')) then
            gui.separator_text('Time of day')
            local hours, minutes, seconds = game.get_time_of_day()

            local new_value, changed = gui.slider_int("Hours", hours, 0, 23)
            if changed then
                game.set_time_of_day(new_value, minutes, seconds)
            end
            local new_value, changed = gui.slider_int("Minutes", minutes, 0, 59)
            if changed then
                game.set_time_of_day(hours, new_value, seconds)
            end
            local new_value, changed = gui.slider_int("Seconds", seconds, 0, 59)
            if changed then
                game.set_time_of_day(hours, minutes, new_value)
            end

            local new_value, changed = gui.checkbox("Lock time of day", game.time_frozen)
            if changed then
                game.time_frozen = new_value
            end

            gui.separator_text('Alert level')

            local alert_level = game.get_alert_level()
            local alert_level_text = 'Unknown'

            if alert_level == defines.alert_level.green then
                alert_level_text = 'Green'
            elseif alert_level == defines.alert_level.yellow then
                alert_level_text = 'Yellow'
            elseif alert_level == defines.alert_level.orange then
                alert_level_text = 'Orange'
            elseif alert_level == defines.alert_level.red then
                alert_level_text = 'Red'
            end

            gui.text("Desired alert level:")
            gui.same_line()
            gui.text(alert_level_text)
            if gui.button("Green") then
                state.desired_alert_level = defines.alert_level.green
                game.set_alert_level(defines.alert_level.green)
            end

            gui.same_line()
            if gui.button("Yellow") then
                state.desired_alert_level = defines.alert_level.yellow
                game.set_alert_level(defines.alert_level.yellow)
            end

            gui.same_line()
            if gui.button("Orange") then
                state.desired_alert_level = defines.alert_level.orange
                game.set_alert_level(defines.alert_level.orange)
            end

            gui.same_line()
            if gui.button("Red") then
                state.desired_alert_level = defines.alert_level.red
                game.set_alert_level(defines.alert_level.red)
            end

            local new_value, changed = gui.checkbox("Lock alert level", state.lock_alert_level)
            if changed then
                state.lock_alert_level = new_value
            end

            gui.end_tab_item()
        end

        gui.end_tab_bar()
    end
end

mod:register_window("Cheats", draw_window)

mod:register_event(defines.event.player_do_frame, function (e)
    if state.infinite_jetpack then
        e.player.jetpack_fuel_percent = 1.0
    end
end)

mod:register_event(defines.event.alert_level_changed, function (e)
    if state.lock_alert_level and e.new_alert_level ~= state.desired_alert_level then
        game.set_alert_level(state.desired_alert_level)
    end
end)
