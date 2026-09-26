# Changelog

## 0.1.0-beta.3 (2026-09-26)

### Added
* Overlay menu bar options to anchor widgets to a corner of the screen.
* Icon for launcher window.
* Icon font for launcher and overlay.
* Show the default value of each mod option in a tooltip in the launcher.
* `authors` field and `tooltip` field for options in mod metadata.
* `keep_launcher_open`, `debug_logs_enabled`, and `imgui_demo_window` config options.
* `sledge.register_file`, `sledge.register_packfile` and `sledge.register_xml_edit` functions.
* `gui.property_table` and `gui.property_row` functions.
* `types.mod_info.options`, `types.xml_node.name`, and `types.xml_node.value` fields.

### Changed
* Rename overlays to widgets.
* Disable the game loading `table.vpp_pc`.
* Calculate the multiplayer hash using the hash of `misc.vpp_pc`, the current Sledge version and the number of mods enabled.
* Use TOML instead of JSON as the format for the config and mod metadata files.
* Show the operating system's cursor when the overlay is enabled instead of drawing a fake cursor.
* Rename the `open_key` config option to `overlay_key`.
* Make the `Position` widget show `0` for each coordinate when the player isn't valid instead of drawing nothing.
* Move the `types.mod_info:register_event`, `types.mod_info:register_widget`, `types.mod_info:register_window`, `types.mod_info:log`, `types.mod_info:log_warn`, and `types.mod_info:log_error` functions to the `sledge` namespace.
* Functions in the `gui` namespace now use callback function parameters instead of returning multiple values.

### Removed
* `fps_limit` config option.
* `author` field in mod metadata.
* `Sledge` -> `Demo window` item in the overlay menu bar.
* `defines.event.parse_xml` event.
* `types.xml_node:value`, and `types.xml_node:set` functions.
* `gui.separator_text`, `gui.begin_tooltip`, `gui.end_tooltip`, `gui.begin_help_marker`, `gui.end_help_marker`, `gui.begin_tab_bar`, `gui.end_tab_bar`, `gui.begin_tab_item`, `gui.end_tab_item`, `gui.input_text_hint`, `gui.input_int_1/2/3/4`, `gui.input_float_1/2/3/4`, `gui.drag_int`, and `gui.drag_float` functions.
* `types.mod_info:get_option` function and `types.mod_info.version`, `types.mod_info.description`, `types.mod_info.author`, and `types.mod_info.path` fields.

### Fixed
* `game.get_alert_level` function referencing the wrong offset for Steam.
* Mouse input passing through the overlay.
* Key events being triggered while the overlay is enabled.

## 0.1.0-beta.2 (2026-08-18)

### Added
* Support for the latest Steam version.
* Proxy dinput8.dll file to replace the launcher executable.

### Changed
* Start the Sledge launcher window automatically when running the game.
* Allow players to join others in multiplayer if they have the same Sledge version, the same number of mods enabled, and unmodified data files.

### Removed
* `game_directory` and `keep_launcher_open` config options.
* Launcher executable.

## 0.1.0-beta.1 (2026-08-12)

* First release.