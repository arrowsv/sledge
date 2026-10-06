# sledge

## Functions

### `log`

```lua
sledge.log(message)
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

### `log_warn`

```lua
sledge.log_warn(message)
```

**Parameters**

* `message` (<code>string</code>)

---

### `register_event`

```lua
sledge.register_event(event, callback)
```

**Parameters**

* `event` (<code>[defines.event](/lua/api/defines/event)</code>)
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

### `register_widget`

```lua
sledge.register_widget(title, callback, options?)
```

**Parameters**

* `title` (<code>string</code>)
* `callback` (<code>function</code>)
* `options` (<code>table</code>) <small>optional</small> 
    * `requires_gameplay` (<code>boolean</code>) <small>optional</small>  - If `true`, the widget will only draw its contents if the user is in gameplay. Recommended for panels that access objects only valid in gameplay, such as [`types.player`](/lua/api/types/player).

---

### `register_window`

```lua
sledge.register_window(title, callback, options?)
```

**Parameters**

* `title` (<code>string</code>)
* `callback` (<code>function</code>)
* `options` (<code>table</code>) <small>optional</small> 
    * `width` (<code>number</code>) <small>optional</small> 
    * `height` (<code>number</code>) <small>optional</small> 
    * `auto_resize` (<code>boolean</code>) <small>optional</small>  - If `true`, the window will automatically resize to its contents, ignore any provided width or height, and remove the ability for users to manually resize it.
    * `no_resize` (<code>boolean</code>) <small>optional</small>  - If `true`, the window will remove the ability for users to manually resize it.
    * `requires_gameplay` (<code>boolean</code>) <small>optional</small>  - If `true`, the window will only draw its contents if the user is in gameplay. Recommended for panels that access objects only valid in gameplay, such as [`types.player`](/lua/api/types/player).

---

### `register_xml_edit`

```lua
sledge.register_xml_edit(name, callback)
```

**Parameters**

* `name` (<code>string</code>)
* `callback` (<code>function</code>)

