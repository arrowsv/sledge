# gui

## Functions

### `bullet`

Creates a small circle and keeps the next widget on the same line.

```lua
gui.bullet()
```

---

### `button`

Creates a button.

```lua
gui.button(label, pressed, options?)
```

**Parameters**

* `label` (<code>string</code>)
* `pressed` (<code>function</code>)
* `options` (<code>table</code>) <small>optional</small>
    * `width` (<code>number</code>) <small>optional</small>
    * `height` (<code>number</code>) <small>optional</small>

---

### `checkbox`

Creates a checkbox.

```lua
gui.checkbox(label?, value, changed)
```

**Parameters**

* `label` (<code>string</code>) <small>optional</small>
* `value` (<code>boolean</code>)
* `changed` (<code>function(new_value: boolean)</code>)

---

### `get_available_space`

Returns the available space in the window.

```lua
local width, height = gui.get_available_space()
```

**Returns**

* `width` (<code>number</code>)
* `height` (<code>number</code>)

---

### `help_marker`

Sets the previous widget's help marker.

```lua
gui.help_marker(body)
```

**Parameters**

* `body` (<code>function</code>)

---

### `indent`

Moves the content position to the right.

```lua
gui.indent(width?)
```

**Parameters**

* `width` (<code>number</code>) <small>optional</small>

---

### `input_float`

Creates a floating-point input widget.

```lua
gui.input_float(label?, value, changed)
```

**Parameters**

* `label` (<code>string</code>) <small>optional</small>
* `value` (<code>number</code>)
* `changed` (<code>function(new_value: number)</code>)

---

### `input_int`

Creates a integer input widget.

```lua
gui.input_int(label?, value, changed)
```

**Parameters**

* `label` (<code>string</code>) <small>optional</small>
* `value` (<code>integer</code>)
* `changed` (<code>function(new_value: integer)</code>)

---

### `input_text`

Creates a text input widget.

```lua
gui.input_text(label?, value, changed)
```

**Parameters**

* `label` (<code>string</code>) <small>optional</small>
* `value` (<code>string</code>)
* `changed` (<code>function(new_value: string)</code>)

---

### `new_line`

Forces a new line.

```lua
gui.new_line()
```

---

### `pop_item_width`

Restores the item width.

```lua
gui.pop_item_width()
```

---

### `property_row`

Creates a property table row. This must be called inside the body of a property table.

```lua
gui.property_row(label, body)
```

**Parameters**

* `label` (<code>string</code>)
* `body` (<code>function</code>)

---

### `property_table`

Creates a property table.

```lua
gui.property_table(id, body)
```

**Parameters**

* `id` (<code>string</code>)
* `body` (<code>function</code>)

---

### `push_item_width`

Sets the width of all widgets until `pop_item_width` is called.

```lua
gui.push_item_width(width)
```

**Parameters**

* `width` (<code>number</code>)

---

### `same_line`

Places the next widget on the same line.

```lua
gui.same_line()
```

---

### `separator`

Creates a horizontal separator.

```lua
gui.separator(label?)
```

**Parameters**

* `label` (<code>string</code>) <small>optional</small>

---

### `set_help_marker`

Sets the previous widget's help marker.

```lua
gui.set_help_marker(text)
```

**Parameters**

* `text` (<code>string</code>)

---

### `set_next_item_width`

Sets the width of the next widget.

```lua
gui.set_next_item_width(width)
```

**Parameters**

* `width` (<code>number</code>)

---

### `set_tooltip`

Sets the previous widget's tooltip.

```lua
gui.set_tooltip(text)
```

**Parameters**

* `text` (<code>string</code>)

---

### `slider_float`

Creates a floating-point slider widget.

```lua
gui.slider_float(label?, value, minimum, maximum, changed)
```

**Parameters**

* `label` (<code>string</code>) <small>optional</small>
* `value` (<code>number</code>)
* `minimum` (<code>number</code>)
* `maximum` (<code>number</code>)
* `changed` (<code>function(new_value: number)</code>)

---

### `slider_int`

Creates a integer slider widget.

```lua
gui.slider_int(label?, value, minimum, maximum, changed)
```

**Parameters**

* `label` (<code>string</code>) <small>optional</small>
* `value` (<code>integer</code>)
* `minimum` (<code>integer</code>)
* `maximum` (<code>integer</code>)
* `changed` (<code>function(new_value: integer)</code>)

---

### `spacing`

Adds vertical spacing.

```lua
gui.spacing()
```

---

### `tab_bar`

Creates a tab bar.

```lua
gui.tab_bar(id, body)
```

**Parameters**

* `id` (<code>string</code>)
* `body` (<code>function</code>)

---

### `tab_item`

Creates a tab item.

```lua
gui.tab_item(label, body)
```

**Parameters**

* `label` (<code>string</code>)
* `body` (<code>function</code>)

---

### `text`

Creates text.

```lua
gui.text(text)
```

**Parameters**

* `text` (<code>string</code>)

---

### `text_bullet`

Creates text next to a bullet.

```lua
gui.text_bullet(text)
```

**Parameters**

* `text` (<code>string</code>)

---

### `text_disabled`

Creates text with a disabled colour.

```lua
gui.text_disabled(text)
```

**Parameters**

* `text` (<code>string</code>)

---

### `text_wrapped`

Creates text that wraps when it reaches the content's edge.

```lua
gui.text_wrapped(text)
```

**Parameters**

* `text` (<code>string</code>)

---

### `tooltip`

Sets the previous widget's tooltip.

```lua
gui.tooltip(body)
```

**Parameters**

* `body` (<code>function</code>)

---

### `unindent`

Moves the content position to the left.

```lua
gui.unindent(width?)
```

**Parameters**

* `width` (<code>number</code>) <small>optional</small>
