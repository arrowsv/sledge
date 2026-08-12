--- @meta

--- @class types.xml_node
types.xml_node = {}

--- Returns a node's child by its name.
--- @param name string
--- @return types.xml_node|nil
function types.xml_node:get(name) end

--- Returns the first node that matches the given XPath.
--- @param query string
--- @return types.xml_node|nil
function types.xml_node:get_from_path(query) end

--- Returns all nodes that match the given XPath.
--- @param query string
--- @return types.xml_node[]
function types.xml_node:get_multiple_from_path(query) end

--- Returns the value of the node.
--- @return string value
function types.xml_node:value() end

--- Sets the value of the node.
--- @param value string
function types.xml_node:set(value) end

--- Adds a new child node.
---
--- .. code-block:: lua
---
---     -- Equivalent to <vehicle>Min_LightPickup_1</vehicle>.
---     node:add("vehicle", "Min_LightPickup_1")
---
--- @param name string
--- @param value? string
function types.xml_node:add(name, value) end

--- Deletes the node.
function types.xml_node:delete() end

--- Returns all children of the node.
---
--- .. code-block:: lua
---
---     local children = node:children()
---     for _, child_node in ipairs(children) do
---         mod:log(child_node:value())
---     end
---
--- @return types.xml_node[]
function types.xml_node:children() end

--- @class types.xml_document : types.xml_node
types.xml_document = {}
