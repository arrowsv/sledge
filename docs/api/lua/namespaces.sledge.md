# sledge

## Functions

### <small><code>log</code></small> { #log data-toc-label="log" }

:   
    ```lua
    sledge.log(message)
    ```

    **Parameters**

    * `message` (<code>string</code>)

---

### <small><code>log_error</code></small> { #log_error data-toc-label="log_error" }

:   
    ```lua
    sledge.log_error(message)
    ```

    **Parameters**

    * `message` (<code>string</code>)

---

### <small><code>log_warn</code></small> { #log_warn data-toc-label="log_warn" }

:   
    ```lua
    sledge.log_warn(message)
    ```

    **Parameters**

    * `message` (<code>string</code>)

---

### <small><code>register_event</code></small> { #register_event data-toc-label="register_event" }

:   
    ```lua
    sledge.register_event(event, callback)
    ```

    **Parameters**

    * `event` (<code>[enums.event](enums.event.md)</code>)
    * `callback` (<code>function</code>)

---

### <small><code>register_file</code></small> { #register_file data-toc-label="register_file" }

:   
    ```lua
    sledge.register_file(path)
    ```

    **Parameters**

    * `path` (<code>string</code>)

---

### <small><code>register_packfile</code></small> { #register_packfile data-toc-label="register_packfile" }

:   
    ```lua
    sledge.register_packfile(path)
    ```

    **Parameters**

    * `path` (<code>string</code>)

---

### <small><code>register_widget</code></small> { #register_widget data-toc-label="register_widget" }

:   
    ```lua
    sledge.register_widget(title, callback, options?)
    ```

    **Parameters**

    * `title` (<code>string</code>)
    * `callback` (<code>function</code>)
    * `options` (<code>table</code>) <small>optional</small>
        * `requires_gameplay` (<code>boolean</code>) <small>optional</small> - If `true`, the widget will only draw its contents if the user is in gameplay. Recommended for panels that access objects only valid in gameplay, such as [`types.player`](types.player.md).

---

### <small><code>register_window</code></small> { #register_window data-toc-label="register_window" }

:   
    ```lua
    sledge.register_window(title, callback, options?)
    ```

    **Parameters**

    * `title` (<code>string</code>)
    * `callback` (<code>function</code>)
    * `options` (<code>table</code>) <small>optional</small>
        * `width` (<code>number</code>) <small>optional</small>
        * `height` (<code>number</code>) <small>optional</small>
        * `auto_resize` (<code>boolean</code>) <small>optional</small> - If `true`, the window will automatically resize to its contents, ignore any provided width or height, and remove the ability for users to manually resize it.
        * `no_resize` (<code>boolean</code>) <small>optional</small> - If `true`, the window will remove the ability for users to manually resize it.
        * `requires_gameplay` (<code>boolean</code>) <small>optional</small> - If `true`, the window will only draw its contents if the user is in gameplay. Recommended for panels that access objects only valid in gameplay, such as [`types.player`](types.player.md).

---

### <small><code>register_xml_edit</code></small> { #register_xml_edit data-toc-label="register_xml_edit" }

:   
    ```lua
    sledge.register_xml_edit(name, callback)
    ```

    **Parameters**

    * `name` (<code>string</code>)
    * `callback` (<code>function</code>)
