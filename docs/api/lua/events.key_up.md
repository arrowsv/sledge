# key_up

This event is triggered a key is released.

```lua
local function key_up_callback(data)
end

sledge.register_event(enums.event.key_up, key_up_callback)
```

## Event data

* `key` (<code>[enums.key](enums.key.md)</code>)
* `shift_down` (<code>boolean</code>)
* `control_down` (<code>boolean</code>)
* `alt_down` (<code>boolean</code>)
