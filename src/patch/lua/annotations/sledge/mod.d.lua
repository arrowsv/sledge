---@meta

--- Information and functions for the running mod.
---@class types.mod_info
---@field id          string Identifier of the mod.
---@field name        string Name of the mod.
---@field version     string Version of the mod.
---@field description string Description of the mod.
---@field author      string Author of the mod.
---@field path        string Path of the mod directory.
types.mod_info = {}

--- Returns the selected choice of the mod's option. May return nil.
---
--- .. code-block: lua
---
---     -- text_choice will be a 'string' if the option is defined as 'custom' or 'multiple'.
---     local text_choice = mod:get_option("Custom vehicle name")
---
---     -- checkbox_choice will be a 'boolean' if the option is defined as 'checkbox'.
---     local checkbox_choice = mod:get_option("Checkbox choice")
---
---     -- toggle_key will be a 'defines.key' if the option is defined as 'key'.
---     local toggle_key = mod:get_option("Toggle key")
---
---@param name string Name of the option as defined in the mod's json file.
---@return string | boolean | defines.key | nil
function types.mod_info:get_option(name) end

--- Logs a message to the log file with an `INFO` tag.
---@param message string
function types.mod_info:log(message) end

--- Logs a message to the log file with a `WARN` tag.
---@param message string
function types.mod_info:log_warn(message) end

--- Logs a message to the log file with an `ERROR` tag.
---@param message string
function types.mod_info:log_error(message) end

--- Options for creating a mod window.
---@class types.register_window_options
---@field width?         number  Width of the window, in pixels. Default: `500.0`.
---@field height?        number  Height of the window, in pixels. Default: `300.0`.
---@field auto_resize?   boolean Automatically resize the window to fit its contents every frame.
---@field no_resize?     boolean Prevent the user from resizing the window.
---@field no_decoration? boolean Hide the window's title bar and borders.
---@field no_background? boolean Hide the window's background.

--- Registers a window that can be toggled through the Sledge menu.
---@param title    string                        Title shown in the window's title bar and the Sledge menu.
---@param callback function                      Called every frame while the window is open to draw its contents.
---@param options? types.register_window_options Table of options.
function types.mod_info:register_window(title, callback, test, options) end

---@class types.register_overlay_options
---@field width?         number  Width of the overlay, in pixels. Only applies if `auto_resize` is false. Default: `500.0`.
---@field height?        number  Height of the overlay, in pixels. Only applies if `auto_resize` is false. Default: `300.0`.
---@field auto_resize?   boolean Automatically resize the overlay to fit its contents every frame. Default: `true`.
---@field no_resize?     boolean Prevent the user from resizing the overlay. Default: `true`.
---@field no_decoration? boolean Hide the overlay's title bar and borders. Default: `true`.
---@field no_background? boolean Hide the overlay's background. Default: `true`.

--- Registers an overlay that can be toggled through the Sledge menu. Overlays are windows
--- that, by default, have no background or decorations.
---@param title    string                         Title shown in the Sledge menu (overlays have no visible title bar by default).
---@param callback function                       Called every frame while the overlay is open to draw its contents.
---@param options? types.register_overlay_options Table of options.
function types.mod_info:register_overlay(title, callback, options) end

---@class types.register_event_options
---@field id?     string Identifier for this event callback, usable later to remove it.
---@field filter? string Filter restricting which occurrences of the event trigger the callback.

--- Registers a function to be called when an event is triggered by the game.
---@param event    defines.event                The event type to listen for.
---@param callback function                     Called when the event is triggered. Depending on the event, a table is passed to the function which contains event-specific information.
---@param options? types.register_event_options Table of options.
function types.mod_info:register_event(event, callback, options) end

--- Imports and runs a Lua script relative to the mod's root folder.
---@param name string Name of the file without its extension.
---@return any result The return value of the imported file.
function types.mod_info:import(name) end

--- Global variable representing the script's associated mod.
---@type types.mod_info
mod = nil
