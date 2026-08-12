---@meta

-- --- @class defines.event
-- --- @field player_do_frame defines.event
-- --- @field alert_level_changed defines.event
-- --- @field save_loaded defines.event
-- --- @field key_down defines.event
-- --- @field key_up defines.event
-- --- @field mouse_wheel defines.event
-- --- @field parse_xml defines.event
-- defines.event = {}

---@enum defines.event
defines.event = {
  player_do_frame = 1,
  alert_level_changed = 2,
  save_loaded = 3,
  key_down = 4,
  key_up = 5,
  mouse_wheel = 6,
  parse_xml = 7
}
