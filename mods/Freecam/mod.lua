direction = { forward = 1, back = 2, left = 3, right = 4, up = 5, down = 6 }

function lerp(a, b, t)
    return a + (b - a) * t
end

local state = {}
state.freecam_toggle_key = mod:get_option("Freecam key")
state.freecam_position = types.vector.new(0, 0, 0)
state.freecam_enabled = false

state.freecam_speed = 0.3
state.freecam_speed_minimum = 0.01
state.freecam_speed_maximum = 5
state.freecam_speed_modifier = 0.8

state.freecam_smoothing = 0.125
state.freecam_smoothing_minimum = 0.001
state.freecam_smoothing_maximum = 1

state.freecam_return_to_original_position = false
state.freecam_make_player_invisible = true
state.freecam_keep_player_with_camera = true
state.freecam_lock_player_controls = true

-- Originals of properties that the freecam restores once disabled.
state.player_original_position = types.vector.new(0, 0, 0)
state.player_original_invulnerable_flag = false
state.player_original_ai_ignore_flag = false
state.player_original_no_ragdoll_flag = false
state.player_original_hit_points = 0.0

local function camera_move(desired_direction)
    local modified_speed = state.freecam_speed

    if game.is_key_down(defines.key.shift) then
        modified_speed = modified_speed + state.freecam_speed_modifier
        if modified_speed > state.freecam_speed_maximum then
            modified_speed = state.freecam_speed_maximum
        end
    elseif game.is_key_down(defines.key.control) then
        modified_speed = modified_speed - state.freecam_speed_modifier
        if modified_speed < state.freecam_speed_minimum then
            modified_speed = state.freecam_speed_minimum
        end
    end

    if desired_direction == direction.forward then
        local orientation = game.get_camera().orientation.forward
        state.freecam_position = state.freecam_position + (orientation * modified_speed)
    elseif desired_direction == direction.back then
        local orientation = game.get_camera().orientation.forward
        state.freecam_position = state.freecam_position + (orientation * -modified_speed)
    elseif desired_direction == direction.left then
        local orientation = game.get_camera().orientation.right
        state.freecam_position = state.freecam_position + (orientation * -modified_speed)
    elseif desired_direction == direction.right then
        local orientation = game.get_camera().orientation.right
        state.freecam_position = state.freecam_position + (orientation * modified_speed)
    end
end

sledge.register_event(defines.event.player_do_frame, function(e)
    if state.freecam_enabled then
        if game.is_key_down(defines.key.w) or game.is_key_down(defines.key.arrow_up) then
            camera_move(direction.forward)
        end
        if game.is_key_down(defines.key.s) or game.is_key_down(defines.key.arrow_down) then
            camera_move(direction.back)
        end
        if game.is_key_down(defines.key.a) or game.is_key_down(defines.key.arrow_left) then
            camera_move(direction.left)
        end
        if game.is_key_down(defines.key.d) or game.is_key_down(defines.key.arrow_right) then
            camera_move(direction.right)
        end

        local camera = game.get_camera()
        camera.position = lerp(camera.position, state.freecam_position, state.freecam_smoothing)

        if state.freecam_keep_player_with_camera then
            e.player:teleport(types.vector.new(camera.position.x, camera.position.y + 5, camera.position.z))
        end

        e.player.hit_points = 99999999999
    end
end)

sledge.register_event(defines.event.key_down, function(e)
    if not game.is_in_gameplay() then return end

    local player = game.get_player()
    if not player then return end

    if e.key == state.freecam_toggle_key then
        state.freecam_enabled = not state.freecam_enabled
        if state.freecam_enabled then
            state.player_original_position = types.vector.new(player.position)

            state.player_original_invulnerable_flag = player.flags.invulnerable
            state.player_original_ai_ignore_flag = player.flags.ignored_by_ai
            state.player_original_no_ragdoll_flag = player.flags.disallow_flinches_and_ragdolls
            state.player_original_hit_points = player.hit_points

            player.flags.invulnerable = true
            player.flags.ignored_by_ai = true
            player.flags.disallow_flinches_and_ragdolls = true

            game.input_enabled = false

            if state.freecam_make_player_invisible then
                player:set_visible(false)
            end

            state.freecam_position = types.vector.new(player.position.x, player.position.y + 2, player.position.z)
            game.overriding_camera_position = true
        else
            game.overriding_camera_position = false
            player:set_visible(true)

            if state.freecam_return_to_original_position then
                player:teleport(state.player_original_position)
            else
                player:teleport(
                    types.vector.new(state.freecam_position.x, state.freecam_position.y - 2, state.freecam_position.z)
                )
            end

            game.input_enabled = true

            player.flags.invulnerable = state.player_original_invulnerable_flag
            player.flags.ignored_by_ai = state.player_original_ai_ignore_flag
            player.flags.disallow_flinches_and_ragdolls = state.player_original_no_ragdoll_flag
            player.hit_points = state.player_original_hit_points
        end
    end
end)

sledge.register_event(defines.event.mouse_wheel, function(e)
    if state.freecam_enabled then
        state.freecam_speed = state.freecam_speed + e.delta * 0.001
        if state.freecam_speed < state.freecam_speed_minimum then
            state.freecam_speed = state.freecam_speed_minimum
        elseif state.freecam_speed > state.freecam_speed_maximum then
            state.freecam_speed = state.freecam_speed_maximum
        end
    end
end)

sledge.register_window("Freecam", function()
    if not game.is_in_gameplay() then
        gui.text("A save must be loaded before using this menu.")
        return
    end

    gui.property_table("Options", function()
        gui.property_row("Speed", function()
            gui.slider_float(state.freecam_speed, state.freecam_speed_minimum, state.freecam_speed_maximum, function(v)
                state.freecam_speed = v
            end)
        end)

        gui.property_row("Smoothing", function()
            gui.slider_float(state.freecam_smoothing, state.freecam_smoothing_minimum, state.freecam_smoothing_maximum, function(v)
                state.freecam_smoothing = v
            end)
            gui.set_tooltip("Determines the interpolation rate between the freecam's current and new position. Smaller values produce smoother movement, while larger values produce quicker movement. Default is 0.125.")
        end)

        gui.property_row("Invisible player", function()
            gui.checkbox(state.freecam_make_player_invisible, function(v)
                state.freecam_make_player_invisible = v
            end)
            gui.set_tooltip("Hides the player model while the freecam is active. Useful to prevent the player from casting shadows. Equipping certain weapons (e.g. remote charges) while invisible causes the equip animation/sound to loop.")
        end)

        gui.property_row("Keep player with camera", function()
            gui.checkbox(state.freecam_keep_player_with_camera, function(v)
                state.freecam_keep_player_with_camera = v
            end)
            gui.set_tooltip("Teleports the player above the camera's position every frame. Disabling this can cause issues if the camera is too far from the player.")
        end)

        gui.property_row("Return to original position", function()
            gui.checkbox(state.freecam_return_to_original_position, function(v)
                state.freecam_return_to_original_position = v
            end)
            gui.set_tooltip("Returns the player to their original position after disabling the freecam.")
        end)
    end)
end, { width = 500, height = 200 })
