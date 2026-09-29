# player_do_frame

This event is triggered every single frame the player is processed. This will not be triggered when the game is paused or in the main menu.

```lua
local function player_do_frame_callback(data)
end

sledge.register_event(defines.event.player_do_frame, player_do_frame_callback)
```

## Event data

* `player` (<code>[types.player](/lua/api/types/player.md)</code>)
