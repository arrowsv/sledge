# types.xml_node

## Properties

### <small><code>name</code></small> <small>:lucide-move-right: <code>string</code></small> { #name data-toc-label="name" }

:   
    Name of the node.

---

### <small><code>value</code></small> <small>:lucide-move-right: <code>string</code></small> { #value data-toc-label="value" }

:   
    Value of the node.

## Methods

### <small><code>add</code></small> <small>:lucide-move-right: <code>[types.xml_node](types.xml_node.md)</code></small> { #add data-toc-label="add" }

:   
    Adds a new child node to the end of the node's children list.

    ```lua
    local result = object:add(name, value?)
    ```

    **Parameters**

    * `name` (<code>string</code>)
    * `value` (<code>string</code>) <small>optional</small>

---

### <small><code>add</code></small> <small>:lucide-move-right: <code>[types.xml_node](types.xml_node.md)</code></small> { #add data-toc-label="add" }

:   
    Copies an existing node to the end of the node's children list.

    ```lua
    local result = object:add(node)
    ```

    **Parameters**

    * `node` (<code>[types.xml_node](types.xml_node.md)</code>)

---

### <small><code>children</code></small> <small>:lucide-move-right: <code>[types.xml_node](types.xml_node.md)[]</code></small> { #children data-toc-label="children" }

:   
    Returns all children of the node.

    ```lua
    local result = object:children()
    ```

---

### <small><code>delete</code></small> { #delete data-toc-label="delete" }

:   
    Deletes the node.

    ```lua
    object:delete()
    ```

---

### <small><code>exists</code></small> <small>:lucide-move-right: <code>boolean</code></small> { #exists data-toc-label="exists" }

:   
    Returns whether the node exists.

    ```lua
    local result = object:exists()
    ```

---

### <small><code>get</code></small> <small>:lucide-move-right: <code>[types.xml_node](types.xml_node.md)</code></small> { #get data-toc-label="get" }

:   
    Returns a node's child by its name.

    ```lua
    local result = object:get(name)
    ```

    **Parameters**

    * `name` (<code>string</code>)

---

### <small><code>get_from_path</code></small> <small>:lucide-move-right: <code>[types.xml_node](types.xml_node.md)</code></small> { #get_from_path data-toc-label="get_from_path" }

:   
    Returns the first node that matches the given XPath.

    ```lua
    local result = object:get_from_path(query)
    ```

    **Parameters**

    * `query` (<code>string</code>)

---

### <small><code>get_multiple_from_path</code></small> <small>:lucide-move-right: <code>[types.xml_node](types.xml_node.md)[]</code></small> { #get_multiple_from_path data-toc-label="get_multiple_from_path" }

:   
    Returns all nodes that match the given XPath.

    ```lua
    local result = object:get_multiple_from_path(query)
    ```

    **Parameters**

    * `query` (<code>string</code>)

---

### <small><code>parent</code></small> <small>:lucide-move-right: <code>[types.xml_node](types.xml_node.md)[]</code></small> { #parent data-toc-label="parent" }

:   
    Returns the parent of the node.

    ```lua
    local result = object:parent()
    ```
