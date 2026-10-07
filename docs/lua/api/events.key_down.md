# key_down

This event is triggered a key is pressed.

```lua
local function key_down_callback(data)
end

sledge.register_event(defines.event.key_down, key_down_callback)
```

## Event data

* `key` (<code>[defines.key](defines.key.md)</code>)
* `shift_down` (<code>boolean</code>)
* `control_down` (<code>boolean</code>)
* `alt_down` (<code>boolean</code>)
