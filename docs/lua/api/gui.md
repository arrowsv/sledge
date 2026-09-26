# gui

## Functions

### `set_next_item_width`

Sets the width of the next widget.

```lua
gui.set_next_item_width(width)
```

**Parameters**

* `width` (`number`)

---

### `push_item_width`

Sets the width of all widgets until `pop_item_width` is called.

```lua
gui.push_item_width(width)
```

**Parameters**

* `width` (`number`)

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

* `width` (`number`)
* `height` (`number`)

---

### `separator`

Creates a horizontal separator.

```lua
gui.separator(label?)
```

**Parameters**

* `label` (`string`, optional)

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

* `width` (`number`, optional)

---

### `unindent`

Moves the content position to the left.

```lua
gui.unindent(width?)
```

**Parameters**

* `width` (`number`, optional)

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

* `text` (`string`)

---

### `text_disabled`

Creates text with a disabled colour.

```lua
gui.text_disabled(text)
```

**Parameters**

* `text` (`string`)

---

### `text_wrapped`

Creates text that wraps when it reaches the content's edge.

```lua
gui.text_wrapped(text)
```

**Parameters**

* `text` (`string`)

---

### `text_bullet`

Creates text next to a bullet.

```lua
gui.text_bullet(text)
```

**Parameters**

* `text` (`string`)

---

### `button`

Creates a button.

```lua
gui.button(label, pressed)
```

**Parameters**

* `label` (`string`)
* `pressed` (`function`)

---

### `checkbox`

Creates a checkbox.

```lua
gui.checkbox(label?, value, changed)
```

**Parameters**

* `label` (`string`, optional)
* `value` (`boolean`)
* `changed` (`function(new_value: boolean)`)

---

### `set_tooltip`

Sets the previous widget's tooltip.

```lua
gui.set_tooltip(text)
```

**Parameters**

* `text` (`string`)

---

### `tooltip`

Sets the previous widget's tooltip.

```lua
gui.tooltip(body)
```

**Parameters**

* `body` (`function`)

---

### `set_help_marker`

Sets the previous widget's help marker.

```lua
gui.set_help_marker(text)
```

**Parameters**

* `text` (`string`)

---

### `help_marker`

Sets the previous widget's help marker.

```lua
gui.help_marker(body)
```

**Parameters**

* `body` (`function`)

---

### `tab_bar`

Creates a tab bar.

```lua
gui.tab_bar(id, body)
```

**Parameters**

* `id` (`string`)
* `body` (`function`)

---

### `tab_item`

Creates a tab item.

```lua
gui.tab_item(label, body)
```

**Parameters**

* `label` (`string`)
* `body` (`function`)

---

### `input_text`

Creates a text input widget.

```lua
gui.input_text(label?, value, changed)
```

**Parameters**

* `label` (`string`, optional)
* `value` (`string`)
* `changed` (`function(new_value: string)`)

---

### `input_int`

Creates a integer input widget.

```lua
gui.input_int(label?, value, changed)
```

**Parameters**

* `label` (`string`, optional)
* `value` (`integer`)
* `changed` (`function(new_value: integer)`)

---

### `input_float`

Creates a floating-point input widget.

```lua
gui.input_float(label?, value, changed)
```

**Parameters**

* `label` (`string`, optional)
* `value` (`number`)
* `changed` (`function(new_value: number)`)

---

### `slider_int`

Creates a integer slider widget.

```lua
gui.slider_int(label?, value, minimum, maximum, changed)
```

**Parameters**

* `label` (`string`, optional)
* `value` (`integer`)
* `minimum` (`integer`)
* `maximum` (`integer`)
* `changed` (`function(new_value: integer)`)

---

### `slider_float`

Creates a floating-point slider widget.

```lua
gui.slider_float(label?, value, minimum, maximum, changed)
```

**Parameters**

* `label` (`string`, optional)
* `value` (`number`)
* `minimum` (`number`)
* `maximum` (`number`)
* `changed` (`function(new_value: number)`)

---

### `property_table`

Creates a property table.

```lua
gui.property_table(id, body)
```

**Parameters**

* `id` (`string`)
* `body` (`function`)

---

### `property_row`

Creates a property table row. This must be called inside the body of a property table.

```lua
gui.property_row(label, body)
```

**Parameters**

* `label` (`string`)
* `body` (`function`)

