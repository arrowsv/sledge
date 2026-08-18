local hud_toggle_key = mod:get_option("HUD key")
local fog_toggle_key = mod:get_option("Fog key")
local wind_toggle_key = mod:get_option("Wind key")

mod:register_event(defines.event.key_down, function(e)
    if e.key == hud_toggle_key then
        game.hud_visible = not game.hud_visible
    elseif e.key == fog_toggle_key then
        game.fog_visible = not game.fog_visible
    elseif e.key == wind_toggle_key then
        game.wind_visible = not game.wind_visible
    end
end)
