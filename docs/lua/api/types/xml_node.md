# types.xml_node

## Fields

### `value`

Type: `string`

Value of the node.

---

### `name`

Type: `string`

Name of the node.

## Methods

### `exists`

Returns whether the node exists.

```lua
local result = types.xml_node:exists()
```

**Returns**

* `result` (`boolean`)

---

### `get`

Returns a node's child by its name.

```lua
local result = types.xml_node:get(name)
```

**Parameters**

* `name` (`string`)

**Returns**

* `result` (`types.xml_node`)

---

### `get_from_path`

Returns the first node that matches the given XPath.

```lua
local result = types.xml_node:get_from_path(query)
```

**Parameters**

* `query` (`string`)

**Returns**

* `result` (`types.xml_node`)

---

### `get_multiple_from_path`

Returns all nodes that match the given XPath.

```lua
local result = types.xml_node:get_multiple_from_path(query)
```

**Parameters**

* `query` (`string`)

**Returns**

* `result` (`types.xml_node[]`)

---

### `add`

Adds a new child node.

```lua
local result = types.xml_node:add(name, value?)
```

**Parameters**

* `name` (`string`)
* `value` (`string`, optional)

**Returns**

* `result` (`types.xml_node`)

---

### `delete`

Deletes the node.

```lua
types.xml_node:delete()
```

---

### `children`

Returns all children of the node.

```lua
local result = types.xml_node:children()
```

**Returns**

* `result` (`types.xml_node[]`)

---

### `parent`

Returns the parent of the node.

```lua
local result = types.xml_node:parent()
```

**Returns**

* `result` (`types.xml_node[]`)

