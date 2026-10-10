# gui

## Functions

### <small><code>bullet</code></small> { #bullet data-toc-label="bullet" }

:   
    Creates a small circle and keeps the next widget on the same line.

    ```lua
    gui.bullet()
    ```

---

### <small><code>button</code></small> { #button data-toc-label="button" }

:   
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

### <small><code>checkbox</code></small> { #checkbox data-toc-label="checkbox" }

:   
    Creates a checkbox.

    ```lua
    gui.checkbox(label?, value, changed)
    ```

    **Parameters**

    * `label` (<code>string</code>) <small>optional</small>
    * `value` (<code>boolean</code>)
    * `changed` (<code>function(new_value: boolean)</code>)

---

### <small><code>get_available_space</code></small> <small>:lucide-move-right: <code>width (number), height (number)</code></small> { #get_available_space data-toc-label="get_available_space" }

:   
    Returns the available space in the window.

    ```lua
    local width, height = gui.get_available_space()
    ```

---

### <small><code>help_marker</code></small> { #help_marker data-toc-label="help_marker" }

:   
    Creates a help marker next to the previous widget.

    ```lua
    gui.help_marker(text)
    ```

    **Parameters**

    * `text` (<code>string</code>)

---

### <small><code>help_marker</code></small> { #help_marker data-toc-label="help_marker" }

:   
    Creates a help marker next to the previous widget.

    ```lua
    gui.help_marker(body)
    ```

    **Parameters**

    * `body` (<code>function</code>)

---

### <small><code>indent</code></small> { #indent data-toc-label="indent" }

:   
    Moves the content position to the right.

    ```lua
    gui.indent(width?)
    ```

    **Parameters**

    * `width` (<code>number</code>) <small>optional</small>

---

### <small><code>input_float</code></small> { #input_float data-toc-label="input_float" }

:   
    Creates a floating-point input widget.

    ```lua
    gui.input_float(label?, value, changed)
    ```

    **Parameters**

    * `label` (<code>string</code>) <small>optional</small>
    * `value` (<code>number</code>)
    * `changed` (<code>function(new_value: number)</code>)

---

### <small><code>input_int</code></small> { #input_int data-toc-label="input_int" }

:   
    Creates a integer input widget.

    ```lua
    gui.input_int(label?, value, changed)
    ```

    **Parameters**

    * `label` (<code>string</code>) <small>optional</small>
    * `value` (<code>integer</code>)
    * `changed` (<code>function(new_value: integer)</code>)

---

### <small><code>input_text</code></small> { #input_text data-toc-label="input_text" }

:   
    Creates a text input widget.

    ```lua
    gui.input_text(label?, value, changed)
    ```

    **Parameters**

    * `label` (<code>string</code>) <small>optional</small>
    * `value` (<code>string</code>)
    * `changed` (<code>function(new_value: string)</code>)

---

### <small><code>new_line</code></small> { #new_line data-toc-label="new_line" }

:   
    Forces a new line.

    ```lua
    gui.new_line()
    ```

---

### <small><code>pop_item_width</code></small> { #pop_item_width data-toc-label="pop_item_width" }

:   
    Restores the item width.

    ```lua
    gui.pop_item_width()
    ```

---

### <small><code>property_row</code></small> { #property_row data-toc-label="property_row" }

:   
    Creates a property table row. This must be called inside the body of a property table.

    ```lua
    gui.property_row(label, body)
    ```

    **Parameters**

    * `label` (<code>string</code>)
    * `body` (<code>function</code>)

---

### <small><code>property_table</code></small> { #property_table data-toc-label="property_table" }

:   
    Creates a property table.

    ```lua
    gui.property_table(id, body)
    ```

    **Parameters**

    * `id` (<code>string</code>)
    * `body` (<code>function</code>)

---

### <small><code>push_item_width</code></small> { #push_item_width data-toc-label="push_item_width" }

:   
    Sets the width of all widgets until `pop_item_width` is called.

    ```lua
    gui.push_item_width(width)
    ```

    **Parameters**

    * `width` (<code>number</code>)

---

### <small><code>same_line</code></small> { #same_line data-toc-label="same_line" }

:   
    Places the next widget on the same line.

    ```lua
    gui.same_line()
    ```

---

### <small><code>separator</code></small> { #separator data-toc-label="separator" }

:   
    Creates a horizontal separator.

    ```lua
    gui.separator(label?)
    ```

    **Parameters**

    * `label` (<code>string</code>) <small>optional</small>

---

### <small><code>set_next_item_width</code></small> { #set_next_item_width data-toc-label="set_next_item_width" }

:   
    Sets the width of the next widget.

    ```lua
    gui.set_next_item_width(width)
    ```

    **Parameters**

    * `width` (<code>number</code>)

---

### <small><code>slider_float</code></small> { #slider_float data-toc-label="slider_float" }

:   
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

### <small><code>slider_int</code></small> { #slider_int data-toc-label="slider_int" }

:   
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

### <small><code>spacing</code></small> { #spacing data-toc-label="spacing" }

:   
    Adds vertical spacing.

    ```lua
    gui.spacing()
    ```

---

### <small><code>tab_bar</code></small> { #tab_bar data-toc-label="tab_bar" }

:   
    Creates a tab bar.

    ```lua
    gui.tab_bar(id, body)
    ```

    **Parameters**

    * `id` (<code>string</code>)
    * `body` (<code>function</code>)

---

### <small><code>tab_item</code></small> { #tab_item data-toc-label="tab_item" }

:   
    Creates a tab item.

    ```lua
    gui.tab_item(label, body)
    ```

    **Parameters**

    * `label` (<code>string</code>)
    * `body` (<code>function</code>)

---

### <small><code>text</code></small> { #text data-toc-label="text" }

:   
    Creates text.

    ```lua
    gui.text(text)
    ```

    **Parameters**

    * `text` (<code>string</code>)

---

### <small><code>text_bullet</code></small> { #text_bullet data-toc-label="text_bullet" }

:   
    Creates text next to a bullet.

    ```lua
    gui.text_bullet(text)
    ```

    **Parameters**

    * `text` (<code>string</code>)

---

### <small><code>text_disabled</code></small> { #text_disabled data-toc-label="text_disabled" }

:   
    Creates text with a disabled colour.

    ```lua
    gui.text_disabled(text)
    ```

    **Parameters**

    * `text` (<code>string</code>)

---

### <small><code>text_wrapped</code></small> { #text_wrapped data-toc-label="text_wrapped" }

:   
    Creates text that wraps when it reaches the content's edge.

    ```lua
    gui.text_wrapped(text)
    ```

    **Parameters**

    * `text` (<code>string</code>)

---

### <small><code>tooltip</code></small> { #tooltip data-toc-label="tooltip" }

:   
    Sets the previous widget's tooltip.

    ```lua
    gui.tooltip(text)
    ```

    **Parameters**

    * `text` (<code>string</code>)

---

### <small><code>tooltip</code></small> { #tooltip data-toc-label="tooltip" }

:   
    Sets the previous widget's tooltip.

    ```lua
    gui.tooltip(body)
    ```

    **Parameters**

    * `body` (<code>function</code>)

---

### <small><code>unindent</code></small> { #unindent data-toc-label="unindent" }

:   
    Moves the content position to the left.

    ```lua
    gui.unindent(width?)
    ```

    **Parameters**

    * `width` (<code>number</code>) <small>optional</small>
