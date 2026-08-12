---@meta

---@class gui
gui = {}

--- Sets the width of the next widget.
---@param width number
function gui.set_next_item_width(width) end

--- Sets the width of all widgets until ``gui.pop_item_width`` is called.
---@param width number
function gui.push_item_width(width) end

--- Restores the item width to the previous value pushed by ``gui.push_item_width``.
function gui.pop_item_width() end

--- Returns the available space in the window.
---@return number width
---@return number height
function gui.get_available_space() end

--- Creates a horizontal separator.
function gui.separator() end

--- Creates a horizontal separator with text.
---@param text string
function gui.separator_text(text) end

--- Places the next widget on the same line.
function gui.same_line() end

--- Forces a new line.
function gui.new_line() end

--- Adds vertical spacing.
function gui.spacing() end

--- Moves the content position to the right.
---@param width? number
function gui.indent(width) end

--- Moves the content position to the left.
---@param width? number
function gui.unindent(width) end

--- Creates a small circle and keeps the next widget on the same line.
function gui.bullet() end

--- Creates text.
---@param text string | number
function gui.text(text) end

--- Creates text with a disabled colour.
---@param text string | number
function gui.text_disabled(text) end

--- Creates text next to a bullet.
---@param text string | number
function gui.text_bullet(text) end

--- Creates text with a label.
---@param label string
---@param text  string | number
function gui.text_label(label, text) end

--- Creates a button.
---
--- .. code-block:: lua
---
---     if gui.button("Action") then
---         mod:log("Doing action.")
---     end
---
---@param label   string
---@param width?  number
---@param height? number
---@return boolean pressed
function gui.button(label, width, height) end

--- Creates a checkbox.
---
--- .. code-block:: lua
---
---     local checkbox_enabled = false
---     local function draw_window()
---         local new_value, changed = gui.checkbox("Enabled", checkbox_enabled)
---         if changed then
---             checkbox_enabled = new_value
---             mod:log("The checkbox state was changed.")
---         end
---     end
---
---@param label string
---@param value boolean
---@return boolean new_value
---@return boolean changed
function gui.checkbox(label, value) end

--- Sets the previous widget's tooltip.
---
--- .. code-block:: lua
---
---     gui.button("This widget has a tooltip.")
---     gui.set_tooltip("This will appear when hovering the previous button.")
---
---@param text string
function gui.set_tooltip(text) end

--- Starts a previous widget's tooltip. Use this to create complex layouts or non-text
--- widgets. Must call ``gui.end_tooltip`` if this returns true.
---
--- .. code-block:: lua
---
---     gui.button("This widget has a tooltip.")
---     if gui.begin_tooltip() then
---         gui.text_bullet("Here is a custom widget in the tooltip.")
---         gui.end_tooltip()
---     end
---
---@return boolean
function gui.begin_tooltip() end

--- Ends a tooltip.
function gui.end_tooltip() end

--- Sets the previous widget's help marker. This creates a "(?)" element that appears in a darker colour on the same
--- line as the previous widget.
---
--- .. code-block:: lua
---
---     gui.button("This widget has a help marker.")
---     gui.set_help_marker("This will appear when hovering the previous button.")
---
---@param text string
function gui.set_help_marker(text) end

--- Starts a previous widget's help marker. Use this to create complex layouts or non-text
--- widgets. Must call ``gui.end_help_marker`` if this returns true.
---
--- .. code-block:: lua
---
---     gui.button("This widget has a help marker.")
---     if gui.begin_help_marker() then
---         gui.text_bullet("Here is a custom widget in the help marker.")
---         gui.end_help_marker()
---     end
---
---@return boolean
function gui.begin_help_marker() end

--- Ends a help marker.
function gui.end_help_marker() end

--- Starts a tab bar.
---
--- .. code-block:: lua
---
---     if gui.begin_tab_bar("my_tab_bar") then
---         -- Add tab items here with gui.begin_tab_item.
---         gui.end_tab_bar()
---     end
---
---@param id string Unique identifier for the tab bar. This identifier is not visible.
---@return boolean
function gui.begin_tab_bar(id) end

--- Ends a tab bar.
function gui.end_tab_bar() end

--- Starts a tab item within a tab bar..
---
--- .. code-block:: lua
---
---     if gui.begin_tab_bar("my_tab_bar") then
---         if gui.begin_tab_item("First tab") then
---             gui.text("First tab text.")
---             gui.end_tab_item()
---         end
---         if gui.begin_tab_item("Second tab") then
---             gui.text("Second tab text.")
---             gui.end_tab_item()
---         end
---         gui.end_tab_bar()
---     end
---
---@param label string
---@return boolean
function gui.begin_tab_item(label) end

--- Ends a tab item.
function gui.end_tab_item() end

--- Creates a text input widget.
---
--- .. code-block:: lua
---
---     local custom_text = ""
---     local function draw_window()
---         local new_value, changed = gui.input_text("Name", custom_text)
---         if changed then
---             custom_text = new_value
---         end
---     end
---
---@param label string
---@param text  string
---@return string new_value
---@return boolean changed
function gui.input_text(label, text) end

--- Creates an integer input widget.
---
--- .. code-block:: lua
---
---     local custom_number = 0
---     local function draw_window()
---         local new_value, changed = gui.input_int("Custom number", custom_number)
---         if changed then
---             custom_number = new_value
---         end
---     end
---
---@param label string
---@param value integer
---@return integer new_value
---@return boolean changed
function gui.input_int(label, value) end

--- Creates an floating-point input widget.
---
--- .. code-block:: lua
---
---     local custom_number = 0.0
---     local function draw_window()
---         local new_value, changed = gui.input_float("Custom number", custom_number)
---         if changed then
---             custom_number = new_value
---         end
---     end
---
---@param label string
---@param value number
---@return number new_value
---@return boolean changed
function gui.input_float(label, value) end
