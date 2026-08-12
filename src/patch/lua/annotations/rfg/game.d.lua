---@meta

---@class types.game_clock
---@field year              number
---@field month             number
---@field day               number
---@field hours             number
---@field minutes           number
---@field seconds           number
---@field day_of_week       number
---@field time_scale        number
---@field current_day_ticks number
types.game_clock = {}

---@enum defines.alert_level
defines.alert_level = {
  green = 0,
  yellow = 0,
  orange = 0,
  red = 0
}

---@class game
---@field overriding_camera_position    boolean Whether the game is prevented from updating the camera position every frame.
---@field overriding_camera_orientation boolean Whether the game is prevented from updating the camera orientation every frame.
---@field time_frozen                   boolean Whether the time of day is frozen.
---@field unlimited_ammo                boolean Whether unlimited ammo is enabled.
---@field unlimited_magazine_ammo       boolean Whether unlimited magazine ammo is enabled.
---@field fog_visible                   boolean Whether fog is visible.
---@field hud_visible                   boolean Whether the HUD is visible.
---@field wind_visible                  boolean Whether wind is visible. If false, wind sounds are also disabled.
game = {}

--- Returns the player.
---@return types.player | nil
function game.get_player() end

--- Returns whether the player is currently in gameplay.
---@return boolean
function game.is_in_gameplay() end

--- Returns the player's camera.
---@return types.camera
function game.get_camera() end

--- Returns the current game clock state.
---@return types.game_clock
function game.get_time() end

--- Returns the current time of day.
---@return number hour
---@return number minutes
---@return number seconds
function game.get_time_of_day() end

--- Sets the current time of day.
---@param hour    number
---@param minutes number
---@param seconds number
function game.set_time_of_day(hour, minutes, seconds) end

--- Returns the current alert level.
---@return defines.alert_level
function game.get_alert_level() end

--- Sets the current alert level.
---@param level defines.alert_level
function game.set_alert_level(level) end

--- Returns the current alert level cap.
---@return defines.alert_level minimum
---@return defines.alert_level maximum
function game.get_alert_level_cap() end

--- Sets the current alert level cap.
---@param minimum defines.alert_level
---@param maximum defines.alert_level
function game.set_alert_level_cap(minimum, maximum) end

--- Releases the current alert level cap.
function game.release_alert_level_cap() end

---@class game.show_message_options
---@field animated boolean If true, the message will have an animated background. This is used by the game when notifying the player about mission and handbook unlocks. Default: ``false``.
---@field duration number  Default: ``3.0``.
game.show_message_options = {}

--- Shows a message in the top-left of the screen. This message only shows while in gameplay.
---@param text     string
---@param options? game.show_message_options
function game.show_message(text, options) end

--- Returns whether a key is being held down in the current frame.
---
--- Scripts where smooth movement is necessary (e.g. freecam mod) can register to the ``player_do_frame`` event and use this function to check if a key is being held down.
--- In all other cases, registering to the ``key_down`` event is recommended to reduce the amount of per-frame scripts.
---@param key defines.key
---@return boolean
function game.is_key_down(key) end
