# game

## Fields

### `fog_visible`

Whether fog is visible.

**Returns**

* `result` (<code>boolean</code>)

---

### `hud_visible`

Whether the HUD is visible.

**Returns**

* `result` (<code>boolean</code>)

---

### `overriding_camera_orientation`

Whether the game is prevented from updating the camera orientation every frame.

**Returns**

* `result` (<code>boolean</code>)

---

### `overriding_camera_position`

Whether the game is prevented from updating the camera position every frame.

**Returns**

* `result` (<code>boolean</code>)

---

### `time_frozen`

Whether the time of day is frozen.

**Returns**

* `result` (<code>boolean</code>)

---

### `unlimited_ammo`

Whether unlimited ammo is enabled.

**Returns**

* `result` (<code>boolean</code>)

---

### `unlimited_magazine_ammo`

Whether unlimited magazine ammo is enabled.

**Returns**

* `result` (<code>boolean</code>)

---

### `wind_visible`

Whether wind is visible. If false, wind sounds are also disabled.

**Returns**

* `result` (<code>boolean</code>)

## Functions

### `get_alert_level`

Returns the current alert level.

```lua
local result = game.get_alert_level()
```

**Returns**

* `result` (<code>[defines.alert_level](/lua/api/defines/alert_level)</code>)

---

### `get_alert_level_cap`

Returns the current alert level cap.

```lua
local minimum, maximum = game.get_alert_level_cap()
```

**Returns**

* `minimum` (<code>[defines.alert_level](/lua/api/defines/alert_level)</code>)
* `maximum` (<code>[defines.alert_level](/lua/api/defines/alert_level)</code>)

---

### `get_camera`

Returns the player's camera.

```lua
local result = game.get_camera()
```

**Returns**

* `result` (<code>[types.camera](/lua/api/types/camera)</code>)

---

### `get_player`

Returns the player.

```lua
local result = game.get_player()
```

**Returns**

* `result` (<code>[types.player](/lua/api/types/player), nil</code>)

---

### `get_time`

Returns the current game clock state.

```lua
local result = game.get_time()
```

**Returns**

* `result` (<code>[types.game_clock](/lua/api/types/game_clock)</code>)

---

### `get_time_of_day`

Returns the current time of day.

```lua
local hour, minutes, seconds = game.get_time_of_day()
```

**Returns**

* `hour` (<code>number</code>)
* `minutes` (<code>number</code>)
* `seconds` (<code>number</code>)

---

### `is_in_gameplay`

Returns whether the player is currently in gameplay.

```lua
local result = game.is_in_gameplay()
```

**Returns**

* `result` (<code>boolean</code>)

---

### `is_key_down`

  Returns whether a key is being held down in the current frame.

  Scripts where smooth movement is necessary (e.g. freecam mod) can register to the `player_do_frame` event and use this function to check if a key is being held down.
  
  In all other cases, registering to the `key_down` event is recommended to reduce the amount of per-frame scripts.
  

```lua
local result = game.is_key_down(key)
```

**Parameters**

* `key` (<code>[defines.key](/lua/api/defines/key)</code>)

**Returns**

* `result` (<code>boolean</code>)

---

### `release_alert_level_cap`

Releases the current alert level cap.

```lua
game.release_alert_level_cap()
```

---

### `set_alert_level`

Sets the current alert level.

```lua
game.set_alert_level(level)
```

**Parameters**

* `level` (<code>[defines.alert_level](/lua/api/defines/alert_level)</code>)

---

### `set_alert_level_cap`

Sets the current alert level cap.

```lua
game.set_alert_level_cap(minimum, maximum)
```

**Parameters**

* `minimum` (<code>[defines.alert_level](/lua/api/defines/alert_level)</code>)
* `maximum` (<code>[defines.alert_level](/lua/api/defines/alert_level)</code>)

---

### `set_time_of_day`

Sets the current time of day.

```lua
game.set_time_of_day(hour, minutes, seconds)
```

**Parameters**

* `hour` (<code>number</code>)
* `minutes` (<code>number</code>)
* `seconds` (<code>number</code>)

---

### `show_message`

Shows a message in the top-left of the screen. This message only shows while in gameplay.

```lua
game.show_message(text, options?)
```

**Parameters**

* `text` (<code>string</code>)
* `options` (<code>table</code>) <small>optional</small> 
    * `animated` (<code>boolean</code>) <small>optional</small>  - If `true`, the message will have an animated background. This is used by the game when notifying the player about mission and handbook unlocks. Defaults to `false`.
    * `duration` (<code>number</code>) <small>optional</small>  - Defaults to `3.0`.

