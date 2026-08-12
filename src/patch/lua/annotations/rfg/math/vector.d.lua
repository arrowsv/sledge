---@meta

--- Represents 3 floating-point numbers.
---@class types.vector
---@field x number
---@field y number
---@field z number
---@operator add(number):types.vector
types.vector = {}

--- Creates a new vector.
---@param x number
---@param y number
---@param z number
---@return types.vector
function types.vector.new(x, y, z) end

--- Creates a new vector.
---@param vector types.vector
---@return types.vector
function types.vector.new(vector) end
