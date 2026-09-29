# gui

## Functions

### `set_next_item_width`

Sets the width of the next widget.

```lua
gui.set_next_item_width(width)
```

**Parameters**

* `width` (<code>number</code>)

---

### `push_item_width`

Sets the width of all widgets until `pop_item_width` is called.

```lua
gui.push_item_width(width)
```

**Parameters**

* `width` (<code>number</code>)

---

### `pop_item_width`

Restores the item width.

```lua
gui.pop_item_width()
```

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

### `separator`

Creates a horizontal separator.

```lua
gui.separator(label?)
```

**Parameters**

* `label` (<code>string</code>, optional)

---

### `same_line`

Places the next widget on the same line.

```lua
gui.same_line()
```

---

### `new_line`

Forces a new line.

```lua
gui.new_line()
```

---

### `spacing`

Adds vertical spacing.

```lua
gui.spacing()
```

---

### `indent`

Moves the content position to the right.

```lua
gui.indent(width?)
```

**Parameters**

* `width` (<code>number</code>, optional)

---

### `unindent`

Moves the content position to the left.

```lua
gui.unindent(width?)
```

**Parameters**

* `width` (<code>number</code>, optional)

---

### `bullet`

Creates a small circle and keeps the next widget on the same line.

```lua
gui.bullet()
```

---

### `text`

Creates text.

```lua
gui.text(text)
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

### `text_bullet`

Creates text next to a bullet.

```lua
gui.text_bullet(text)
```

**Parameters**

* `text` (<code>string</code>)

---

### `button`

Creates a button.

```lua
gui.button(label, pressed)
```

**Parameters**

* `label` (<code>string</code>)
* `pressed` (<code>function</code>)

---

### `checkbox`

Creates a checkbox.

```lua
gui.checkbox(label?, value, changed)
```

**Parameters**

* `label` (<code>string</code>, optional)
* `value` (<code>boolean</code>)
* `changed` (<code>function(new_value: boolean)</code>)

---

### `set_tooltip`

Sets the previous widget's tooltip.

```lua
gui.set_tooltip(text)
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

### `set_help_marker`

Sets the previous widget's help marker.

```lua
gui.set_help_marker(text)
```

**Parameters**

* `text` (<code>string</code>)

---

### `help_marker`

Sets the previous widget's help marker.

```lua
gui.help_marker(body)
```

**Parameters**

* `body` (<code>function</code>)

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

### `input_text`

Creates a text input widget.

```lua
gui.input_text(label?, value, changed)
```

**Parameters**

* `label` (<code>string</code>, optional)
* `value` (<code>string</code>)
* `changed` (<code>function(new_value: string)</code>)

---

### `input_int`

Creates a integer input widget.

```lua
gui.input_int(label?, value, changed)
```

**Parameters**

* `label` (<code>string</code>, optional)
* `value` (<code>integer</code>)
* `changed` (<code>function(new_value: integer)</code>)

---

### `input_float`

Creates a floating-point input widget.

```lua
gui.input_float(label?, value, changed)
```

**Parameters**

* `label` (<code>string</code>, optional)
* `value` (<code>number</code>)
* `changed` (<code>function(new_value: number)</code>)

---

### `slider_int`

Creates a integer slider widget.

```lua
gui.slider_int(label?, value, minimum, maximum, changed)
```

**Parameters**

* `label` (<code>string</code>, optional)
* `value` (<code>integer</code>)
* `minimum` (<code>integer</code>)
* `maximum` (<code>integer</code>)
* `changed` (<code>function(new_value: integer)</code>)

---

### `slider_float`

Creates a floating-point slider widget.

```lua
gui.slider_float(label?, value, minimum, maximum, changed)
```

**Parameters**

* `label` (<code>string</code>, optional)
* `value` (<code>number</code>)
* `minimum` (<code>number</code>)
* `maximum` (<code>number</code>)
* `changed` (<code>function(new_value: number)</code>)

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

### `property_row`

Creates a property table row. This must be called inside the body of a property table.

```lua
gui.property_row(label, body)
```

**Parameters**

* `label` (<code>string</code>)
* `body` (<code>function</code>)

