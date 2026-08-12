---@meta

---@enum defines.team
defines.team = {
  none = 0,
  guerrilla = 0,
  edf = 0,
  civilian = 0,
  marauder = 0
}

---@class types.human_flags
---@field invulnerable                   boolean
---@field no_damage                      boolean
---@field ignored_by_ai                  boolean
---@field disallow_vehicle_exit          boolean
---@field in_vehicle_invisible           boolean
---@field disallow_flinches_and_ragdolls boolean
types.human_flags = {}

---@class types.human: types.object
---@field flags           types.human_flags
---@field hit_points      number
---@field team            defines.team
---@field undercover_team defines.team
types.human = {}

--- Teleports the human.
---@param position types.vector
function types.human:teleport(position) end
