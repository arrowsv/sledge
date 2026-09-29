# sledge

## Functions

### `log`

```lua
sledge.log(message)
```

**Parameters**

* `message` (<code>string</code>)

---

### `log_warn`

```lua
sledge.log_warn(message)
```

**Parameters**

* `message` (<code>string</code>)

---

### `log_error`

```lua
sledge.log_error(message)
```

**Parameters**

* `message` (<code>string</code>)

---

### `register_window`

```lua
sledge.register_window(title, callback)
```

**Parameters**

* `title` (<code>string</code>)
* `callback` (<code>function</code>)

---

### `register_widget`

```lua
sledge.register_widget(title, callback)
```

**Parameters**

* `title` (<code>string</code>)
* `callback` (<code>function</code>)

---

### `register_event`

```lua
sledge.register_event(event, callback)
```

**Parameters**

* `event` (<code>[defines.event](/lua/api/defines/event.md)</code>)
* `callback` (<code>function</code>)

---

### `register_file`

```lua
sledge.register_file(path)
```

**Parameters**

* `path` (<code>string</code>)

---

### `register_packfile`

```lua
sledge.register_packfile(path)
```

**Parameters**

* `path` (<code>string</code>)

---

### `register_xml_edit`

```lua
sledge.register_xml_edit(name, callback)
```

**Parameters**

* `name` (<code>string</code>)
* `callback` (<code>function</code>)

