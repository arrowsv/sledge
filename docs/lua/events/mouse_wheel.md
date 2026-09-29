# mouse_wheel

This event is triggered when the mouse is scrolled.

```lua
local function mouse_wheel_callback(data)
end

sledge.register_event(defines.event.mouse_wheel, mouse_wheel_callback)
```

## Event data

* `delta` (<code>integer</code>)
* `shift_down` (<code>boolean</code>)
* `control_down` (<code>boolean</code>)
* `alt_down` (<code>boolean</code>)
