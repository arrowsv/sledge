# game

## Fields

### `overriding_camera_position`

Type: `boolean`

Whether the game is prevented from updating the camera position every frame.

---

### `overriding_camera_orientation`

Type: `boolean`

Whether the game is prevented from updating the camera orientation every frame.

---

### `time_frozen`

Type: `boolean`

Whether the time of day is frozen.

---

### `unlimited_ammo`

Type: `boolean`

Whether unlimited ammo is enabled.

---

### `unlimited_magazine_ammo`

Type: `boolean`

Whether unlimited magazine ammo is enabled.

---

### `fog_visible`

Type: `boolean`

Whether fog is visible.

---

### `hud_visible`

Type: `boolean`

Whether the HUD is visible.

---

### `wind_visible`

Type: `boolean`

Whether wind is visible. If false, wind sounds are also disabled.

## Functions

### `get_player`

Returns the player.

```lua
local result = game.get_player()
```

**Returns**

* `result` (`types.player, nil`)

---

### `is_in_gameplay`

Returns whether the player is currently in gameplay.

```lua
local result = game.is_in_gameplay()
```

**Returns**

* `result` (`boolean`)

---

### `get_camera`

Returns the player's camera.

```lua
local result = game.get_camera()
```

**Returns**

* `result` (`types.camera`)

---

### `get_time`

Returns the current game clock state.

```lua
local result = game.get_time()
```

**Returns**

* `result` (`types.game_clock`)

---

### `get_time_of_day`

Returns the current time of day.

```lua
local hour, minutes, seconds = game.get_time_of_day()
```

**Returns**

* `hour` (`number`)
* `minutes` (`number`)
* `seconds` (`number`)

---

### `set_time_of_day`

Sets the current time of day.

```lua
game.set_time_of_day(hour, minutes, seconds)
```

**Parameters**

* `hour` (`number`)
* `minutes` (`number`)
* `seconds` (`number`)

---

### `get_alert_level`

Returns the current alert level.

```lua
local result = game.get_alert_level()
```

**Returns**

* `result` (`defines.alert_level`)

---

### `set_alert_level`

Sets the current alert level.

```lua
game.set_alert_level(level)
```

**Parameters**

* `level` (`defines.alert_level`)

---

### `get_alert_level_cap`

Returns the current alert level cap.

```lua
local minimum, maximum = game.get_alert_level_cap()
```

**Returns**

* `minimum` (`defines.alert_level`)
* `maximum` (`defines.alert_level`)

---

### `set_alert_level_cap`

Sets the current alert level cap.

```lua
game.set_alert_level_cap(minimum, maximum)
```

**Parameters**

* `minimum` (`defines.alert_level`)
* `maximum` (`defines.alert_level`)

---

### `release_alert_level_cap`

Releases the current alert level cap.

```lua
game.release_alert_level_cap()
```

---

### `show_message`

Shows a message in the top-left of the screen. This message only shows while in gameplay.

```lua
game.show_message(text, options?)
```

**Parameters**

* `text` (`string`)
* `options` (`table`, optional)
  * `animated` (`boolean`, optional) - If `true`, the message will have an animated background. This is used by the game when notifying the player about mission and handbook unlocks. Defaults to `false`.
  * `duration` (`number`, optional) - Defaults to `3.0`.

---

### `is_key_down`

  Returns whether a key is being held down in the current frame.

  Scripts where smooth movement is necessary (e.g. freecam mod) can register to the `player_do_frame` event and use this function to check if a key is being held down.
  
  In all other cases, registering to the `key_down` event is recommended to reduce the amount of per-frame scripts.
  

```lua
local result = game.is_key_down(key)
```

**Parameters**

* `key` (`defines.key`)

**Returns**

* `result` (`boolean`)

