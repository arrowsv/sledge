--- @meta

--- @class types.object
--- @field position types.vector
--- @field orientation types.matrix
--- @field havok_handle number
--- @field handle number
types.object = {}

--- Sets an object's and its children's visibility.
--- @param visible boolean
function types.object:set_visible(visible) end