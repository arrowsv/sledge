local state = { infinite_jetpack = false, desired_alert_level = defines.alert_level.green, lock_alert_level = false }

sledge.register_window("Cheats", function()
    if not game.is_in_gameplay() then
        gui.text("A save must be loaded before using this menu.")
        return
    end

    local player = game.get_player()
    if not player then return end

    gui.tab_bar("Cheats", function()
        gui.tab_item("Info", function()
            gui.separator("Position")
            gui.property_table("Positions", function()
                gui.property_row("X", function()
                    gui.text(player.position.x)
                end)
                gui.property_row("Y", function()
                    gui.text(player.position.y)
                end)
                gui.property_row("Z", function()
                    gui.text(player.position.z)
                end)
            end)

            gui.separator("Statistics")
            gui.property_table("Statistics", function()
                gui.property_row("Salvage", function()
                    gui.input_int(player.salvage, function(v)
                       player.salvage = v
                    end)
                end)

                gui.property_row("Mined ores", function()
                    gui.input_int(player.mining_count, function(v)
                       player.mining_count = v
                    end)
                end)

                gui.property_row("Destroyed crates", function()
                    gui.input_int(player.supply_crate_count, function(v)
                       player.supply_crate_count = v
                    end)
                end)
            end)

            gui.separator("Team")

            local team_text = ""
            if player.team == defines.team.guerrilla then
                team_text = "Guerrilla"
            elseif player.team == defines.team.edf then
                team_text = "EDF"
            elseif player.team == defines.team.civilian then
                team_text = "Civilian"
            elseif player.team == defines.team.marauder then
                team_text = "Marauder"
            else
                team_text = "Unknown"
            end

            gui.property_table("Team", function()
                gui.property_row("Current team", function()
                   gui.text(team_text)
                end)
            end)

            gui.button("Guerrilla", function()
                player.team = defines.team.guerrilla
            end)
            gui.same_line()
            gui.button("EDF", function()
                player.team = defines.team.edf
            end)
            gui.same_line()
            gui.button("Civilian", function()
                player.team = defines.team.civilian
            end)
            gui.same_line()
            gui.button("Marauder", function()
                player.team = defines.team.marauder
            end)
        end)

        gui.tab_item("Flags", function()
            gui.property_table("Flags", function()
                gui.property_row("Unlimited ammo", function()
                    gui.checkbox(game.unlimited_ammo, function(v)
                       game.unlimited_ammo = v
                    end)
                end)

                gui.property_row("Unlimited magazine ammo", function()
                    gui.checkbox(game.unlimited_magazine_ammo, function(v)
                       game.unlimited_magazine_ammo = v
                    end)
                end)

                gui.property_row("Infinite jetpack", function()
                    gui.checkbox(state.infinite_jetpack, function(v)
                       state.infinite_jetpack = v
                    end)
                end)

                gui.property_row("Invulnerable", function()
                    gui.checkbox(player.flags.invulnerable, function(v)
                       player.flags.invulnerable = v
                    end)
                end)

                gui.property_row("Disable ragdoll", function()
                    gui.checkbox(player.flags.disallow_flinches_and_ragdolls, function(v)
                       player.flags.disallow_flinches_and_ragdolls = v
                    end)
                end)

                gui.property_row("Ignored by AI", function()
                    gui.checkbox(player.flags.ignored_by_ai, function(v)
                       player.flags.ignored_by_ai = v
                    end)
                end)

                gui.property_row("Input enabled", function()
                    gui.checkbox(game.input_enabled, function(v)
                       game.input_enabled = v
                    end)
                end)

                gui.property_row("Camera input enabled", function()
                    gui.checkbox(game.camera_input_enabled, function(v)
                       game.camera_input_enabled = v
                    end)
                end)
            end)
        end)

        gui.tab_item("World", function()
            gui.separator("Time of day")
            local hours, minutes, seconds = game.get_time_of_day()
            gui.property_table("Time of day", function()
                gui.property_row("Hours", function()
                    gui.slider_int(hours, 0, 23, function(v)
                        game.set_time_of_day(v, minutes, seconds)
                    end)
                end)
                gui.property_row("Minutes", function()
                    gui.slider_int(minutes, 0, 59, function(v)
                        game.set_time_of_day(hours, v, seconds)
                    end)
                end)
                gui.property_row("Seconds", function()
                    gui.slider_int(seconds, 0, 59, function(v)
                        game.set_time_of_day(hours, minutes, v)
                    end)
                end)
                gui.property_row("Lock time", function()
                    gui.checkbox(game.time_frozen, function(v)
                       game.time_frozen = v
                    end)
                end)
            end)

            gui.separator("Alert level")

            local alert_level = game.get_alert_level()
            local alert_level_text = "Unknown"

            if alert_level == defines.alert_level.green then
                alert_level_text = "Green"
            elseif alert_level == defines.alert_level.yellow then
                alert_level_text = "Yellow"
            elseif alert_level == defines.alert_level.orange then
                alert_level_text = "Orange"
            elseif alert_level == defines.alert_level.red then
                alert_level_text = "Red"
            end

            gui.property_table("Alert level", function()
                gui.property_row("Current level", function()
                    gui.text(alert_level_text)
                end)

                gui.property_row("Lock level", function()
                    gui.checkbox(state.lock_alert_level, function(v)
                        state.lock_alert_level = v
                    end)
                end)
            end)

            gui.button("Green", function()
                state.desired_alert_level = defines.alert_level.green
                game.set_alert_level(state.desired_alert_level)
            end)
            gui.same_line()
            gui.button("Yellow", function()
                state.desired_alert_level = defines.alert_level.yellow
                game.set_alert_level(state.desired_alert_level)
            end)
            gui.same_line()
            gui.button("Orange", function()
                state.desired_alert_level = defines.alert_level.orange
                game.set_alert_level(state.desired_alert_level)
            end)
            gui.same_line()
            gui.button("Red", function()
                state.desired_alert_level = defines.alert_level.red
                game.set_alert_level(state.desired_alert_level)
            end)
        end)
    end)
end)

sledge.register_event(defines.event.player_do_frame, function(e)
    if state.infinite_jetpack then
        e.player.jetpack_fuel_percent = 1.0
    end
end)

sledge.register_event(defines.event.alert_level_changed, function(e)
    if state.lock_alert_level and e.new_alert_level ~= state.desired_alert_level then
        game.set_alert_level(state.desired_alert_level)
    end
end)
