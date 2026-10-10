# rfg

## Properties

### <small><code>fog_visible</code></small> <small>:lucide-move-right: <code>boolean</code></small> { #fog_visible data-toc-label="fog_visible" }

:   
    Whether fog is visible.

---

### <small><code>hud_visible</code></small> <small>:lucide-move-right: <code>boolean</code></small> { #hud_visible data-toc-label="hud_visible" }

:   
    Whether the HUD is visible.

---

### <small><code>overriding_camera_orientation</code></small> <small>:lucide-move-right: <code>boolean</code></small> { #overriding_camera_orientation data-toc-label="overriding_camera_orientation" }

:   
    Whether the game is prevented from updating the camera orientation every frame.

---

### <small><code>overriding_camera_position</code></small> <small>:lucide-move-right: <code>boolean</code></small> { #overriding_camera_position data-toc-label="overriding_camera_position" }

:   
    Whether the game is prevented from updating the camera position every frame.

---

### <small><code>time_frozen</code></small> <small>:lucide-move-right: <code>boolean</code></small> { #time_frozen data-toc-label="time_frozen" }

:   
    Whether the time of day is frozen.

---

### <small><code>unlimited_ammo</code></small> <small>:lucide-move-right: <code>boolean</code></small> { #unlimited_ammo data-toc-label="unlimited_ammo" }

:   
    Whether unlimited ammo is enabled.

---

### <small><code>unlimited_magazine_ammo</code></small> <small>:lucide-move-right: <code>boolean</code></small> { #unlimited_magazine_ammo data-toc-label="unlimited_magazine_ammo" }

:   
    Whether unlimited magazine ammo is enabled.

---

### <small><code>wind_visible</code></small> <small>:lucide-move-right: <code>boolean</code></small> { #wind_visible data-toc-label="wind_visible" }

:   
    Whether wind is visible. If false, wind sounds are also disabled.

## Functions

### <small><code>get_alert_level</code></small> <small>:lucide-move-right: <code>[enums.alert_level](enums.alert_level.md)</code></small> { #get_alert_level data-toc-label="get_alert_level" }

:   
    Returns the current alert level.

    ```lua
    local result = rfg.get_alert_level()
    ```

---

### <small><code>get_alert_level_cap</code></small> <small>:lucide-move-right: <code>minimum ([enums.alert_level](enums.alert_level.md)), maximum ([enums.alert_level](enums.alert_level.md))</code></small> { #get_alert_level_cap data-toc-label="get_alert_level_cap" }

:   
    Returns the current alert level cap.

    ```lua
    local minimum, maximum = rfg.get_alert_level_cap()
    ```

---

### <small><code>get_camera</code></small> <small>:lucide-move-right: <code>[types.camera](types.camera.md)</code></small> { #get_camera data-toc-label="get_camera" }

:   
    Returns the player's camera.

    ```lua
    local result = rfg.get_camera()
    ```

---

### <small><code>get_player</code></small> <small>:lucide-move-right: <code>[types.player](types.player.md)|nil</code></small> { #get_player data-toc-label="get_player" }

:   
    Returns the player.

    ```lua
    local result = rfg.get_player()
    ```

---

### <small><code>get_time</code></small> <small>:lucide-move-right: <code>[types.game_clock](types.game_clock.md)</code></small> { #get_time data-toc-label="get_time" }

:   
    Returns the current game clock state.

    ```lua
    local result = rfg.get_time()
    ```

---

### <small><code>get_time_of_day</code></small> <small>:lucide-move-right: <code>hour (number), minutes (number), seconds (number)</code></small> { #get_time_of_day data-toc-label="get_time_of_day" }

:   
    Returns the current time of day.

    ```lua
    local hour, minutes, seconds = rfg.get_time_of_day()
    ```

---

### <small><code>is_in_gameplay</code></small> <small>:lucide-move-right: <code>boolean</code></small> { #is_in_gameplay data-toc-label="is_in_gameplay" }

:   
    Returns whether the player is currently in gameplay.

    ```lua
    local result = rfg.is_in_gameplay()
    ```

---

### <small><code>is_key_down</code></small> <small>:lucide-move-right: <code>boolean</code></small> { #is_key_down data-toc-label="is_key_down" }

:   
    Returns whether a key is being held down in the current frame.

    Scripts where smooth movement is necessary (e.g. freecam mod) can register to the `player_do_frame` event and use this function to check if a key is being held down.

    In all other cases, registering to the `key_down` event is recommended to reduce the amount of per-frame scripts.

    ```lua
    local result = rfg.is_key_down(key)
    ```

    **Parameters**

    * `key` (<code>[enums.key](enums.key.md)</code>)

---

### <small><code>release_alert_level_cap</code></small> { #release_alert_level_cap data-toc-label="release_alert_level_cap" }

:   
    Releases the current alert level cap.

    ```lua
    rfg.release_alert_level_cap()
    ```

---

### <small><code>set_alert_level</code></small> { #set_alert_level data-toc-label="set_alert_level" }

:   
    Sets the current alert level.

    ```lua
    rfg.set_alert_level(level)
    ```

    **Parameters**

    * `level` (<code>[enums.alert_level](enums.alert_level.md)</code>)

---

### <small><code>set_alert_level_cap</code></small> { #set_alert_level_cap data-toc-label="set_alert_level_cap" }

:   
    Sets the current alert level cap.

    ```lua
    rfg.set_alert_level_cap(minimum, maximum)
    ```

    **Parameters**

    * `minimum` (<code>[enums.alert_level](enums.alert_level.md)</code>)
    * `maximum` (<code>[enums.alert_level](enums.alert_level.md)</code>)

---

### <small><code>set_time_of_day</code></small> { #set_time_of_day data-toc-label="set_time_of_day" }

:   
    Sets the current time of day.

    ```lua
    rfg.set_time_of_day(hour, minutes, seconds)
    ```

    **Parameters**

    * `hour` (<code>number</code>)
    * `minutes` (<code>number</code>)
    * `seconds` (<code>number</code>)

---

### <small><code>show_message</code></small> { #show_message data-toc-label="show_message" }

:   
    Shows a message in the top-left of the screen. This message only shows while in gameplay.

    ```lua
    rfg.show_message(text, options?)
    ```

    **Parameters**

    * `text` (<code>string</code>)
    * `options` (<code>table</code>) <small>optional</small>
        * `animated` (<code>boolean</code>) <small>optional</small> - If `true`, the message will have an animated background. This is used by the game when notifying the player about mission and handbook unlocks. Defaults to `false`.
        * `duration` (<code>number</code>) <small>optional</small> - Defaults to `3.0`.
