# Changelog

## 0.2.0 (2026-10-08)

### Added
- `sledge_version` field in mod metadata, which specifies the version range of Sledge a mod is compatible with. This field is required by all mods.
- Warning icon in the launcher's `Mods` window for incompatible mods.
- `Sledge version` row in the launcher's `Mods` window.
- `types.xml_node:add` method overload, which allows copying a node.

### Fixed
- `Documentation` button in the launcher opening the wrong page.

### Changed
- Move the documentation from MkDocs to Zensical.
- Move `FactionFiles mods` button to the launcher's `Mods` window and rename it to `FactionFiles`.

### Removed
- Bundled mods. They are now available on FactionFiles.

## 0.1.0 (2026-10-03)

### Added
- Icon for the launcher executable.
- `xml_warnings_enabled` config option, which logs warnings when an XML node or path doesn't exist.
- `requires_gameplay` option for panels, which prevents drawing elements when player isn't in gameplay.
- Semantic Versioning validation for the `version` field in mod metadata.

### Changed
- Display mods alphabetically.
- Redesign the launcher UI.

### Removed
- `types.mod_info:import` method.

## 0.1.0-beta.3 (2026-09-26)

### Added
- Overlay menu bar options to anchor widgets to a corner of the screen.
- Icon for the launcher window.
- Icon font for the launcher and overlay.
- Tooltip in the launcher showing the default value of each mod option.
- `tooltip` field for options in mod metadata.
- `keep_launcher_open`, `debug_logs_enabled`, and `imgui_demo_window` config options.
- `sledge.register_file`, `sledge.register_packfile` and `sledge.register_xml_edit` functions.
- `gui.property_table` and `gui.property_row` functions.
- `types.xml_node.name`, and `types.xml_node.value` field.

### Fixed
- `game.get_alert_level` function referencing the wrong offset for Steam.
- Mouse input passing through the overlay.
- Key events being triggered while the overlay is enabled.

### Changed
- Rename overlays to widgets.
- Disable the game loading `table.vpp_pc`.
- Calculate the multiplayer hash using the hash of `misc.vpp_pc`, the current Sledge version, and the number of mods enabled.
- Use TOML instead of JSON as the format for the config and mod metadata files.
- Show the operating system's cursor when the overlay is enabled, instead of drawing a fake cursor.
- Rename the `open_key` config option to `overlay_key`.
- Make the `Position` widget show `0.0` for each coordinate when the player isn't valid, instead of drawing nothing.
- Move the `register_event`, `register_widget`, `register_window`, `log`, `log_warn`, and `log_error` methods from `types.mod_info` to the `sledge` namespace.
- Functions in the `gui` namespace now use callback function parameters instead of returning multiple values.
- Replace the `types.mod_info:get_option` method with the `types.mod_info.options` field.
- Replace the `types.xml_node:value` and `types.xml_node:set` methods with the `types.xml_node.value` field.
- Replace the `author` field in mod metadata with `authors`, which accepts multiple authors.
- Replace the `Demo window` item in the overlay menu with `ImGui demo`, which only shows if the `imgui_demo_window` config option is enabled.

### Removed
- `fps_limit` config option.
- `defines.event.parse_xml` event.
- `gui.separator_text`, `gui.begin_tooltip`, `gui.end_tooltip`, `gui.begin_help_marker`, `gui.end_help_marker`, `gui.begin_tab_bar`, `gui.end_tab_bar`, `gui.begin_tab_item`, `gui.end_tab_item`, `gui.input_text_hint`, `gui.input_int_1/2/3/4`, `gui.input_float_1/2/3/4`, `gui.drag_int`, and `gui.drag_float` functions.
- `types.mod_info.version`, `types.mod_info.description`, `types.mod_info.author`, and `types.mod_info.path` fields.

## 0.1.0-beta.2 (2026-08-18)

### Added
- Support for the latest Steam version.
- Proxy `dinput8.dll` file to replace the launcher executable.

### Changed
- Start the Sledge launcher window automatically when running the game.
- Allow players to join others in multiplayer if they have the same Sledge version, the same number of mods enabled, and unmodified data files.

### Removed
- Launcher executable.
- `game_directory` and `keep_launcher_open` config options.

## 0.1.0-beta.1 (2026-08-12)

- First release.