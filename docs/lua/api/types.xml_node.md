# types.xml_node

## Fields

### `name`

Name of the node.

**Returns**

* `result` (<code>string</code>)

---

### `value`

Value of the node.

**Returns**

* `result` (<code>string</code>)

## Methods

### `add`

Adds a new child node.

```lua
local result = object:add(name, value?)
```

**Parameters**

* `name` (<code>string</code>)
* `value` (<code>string</code>) <small>optional</small>

**Returns**

* `result` (<code>[types.xml_node](types.xml_node.md)</code>)

---

### `children`

Returns all children of the node.

```lua
local result = object:children()
```

**Returns**

* `result` (<code>[types.xml_node](types.xml_node.md)[]</code>)

---

### `delete`

Deletes the node.

```lua
object:delete()
```

---

### `exists`

Returns whether the node exists.

```lua
local result = object:exists()
```

**Returns**

* `result` (<code>boolean</code>)

---

### `get`

Returns a node's child by its name.

```lua
local result = object:get(name)
```

**Parameters**

* `name` (<code>string</code>)

**Returns**

* `result` (<code>[types.xml_node](types.xml_node.md)</code>)

---

### `get_from_path`

Returns the first node that matches the given XPath.

```lua
local result = object:get_from_path(query)
```

**Parameters**

* `query` (<code>string</code>)

**Returns**

* `result` (<code>[types.xml_node](types.xml_node.md)</code>)

---

### `get_multiple_from_path`

Returns all nodes that match the given XPath.

```lua
local result = object:get_multiple_from_path(query)
```

**Parameters**

* `query` (<code>string</code>)

**Returns**

* `result` (<code>[types.xml_node](types.xml_node.md)[]</code>)

---

### `parent`

Returns the parent of the node.

```lua
local result = object:parent()
```

**Returns**

* `result` (<code>[types.xml_node](types.xml_node.md)[]</code>)
