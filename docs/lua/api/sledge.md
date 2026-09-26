# sledge

## Functions

### `log`

```lua
sledge.log(message)
```

**Parameters**

* `message` (`string`)

---

### `log_warn`

```lua
sledge.log_warn(message)
```

**Parameters**

* `message` (`string`)

---

### `log_error`

```lua
sledge.log_error(message)
```

**Parameters**

* `message` (`string`)

---

### `register_window`

```lua
sledge.register_window(title, callback)
```

**Parameters**

* `title` (`string`)
* `callback` (`function`)

---

### `register_widget`

```lua
sledge.register_widget(title, callback)
```

**Parameters**

* `title` (`string`)
* `callback` (`function`)

---

### `register_event`

```lua
sledge.register_event(event, callback)
```

**Parameters**

* `event` (`defines.event`)
* `callback` (`function`)

---

### `register_file`

```lua
sledge.register_file(path)
```

**Parameters**

* `path` (`string`)

---

### `register_packfile`

```lua
sledge.register_packfile(path)
```

**Parameters**

* `path` (`string`)

---

### `register_xml_edit`

```lua
sledge.register_xml_edit(name, callback)
```

**Parameters**

* `name` (`string`)
* `callback` (`function`)

