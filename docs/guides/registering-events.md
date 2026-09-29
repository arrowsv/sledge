# Registering events

Events allow for mods to run functions in response to specific in-game events being triggered.

Register an event with [`sledge.register_event`](/lua/api/sledge.md#register_event) by passing a [`defines.event`](/lua/api/defines/event.md) and callback function. As an example, we will register to the [`defines.event.save_loaded`](/lua/events/save_loaded.md) event and log a message:

```lua
local function save_loaded_callback()
    sledge.log("A save has loaded.")
end

sledge.register_event(defines.event.save_loaded, save_loaded_callback)
```

Some events will pass a table to the callback function, this is referred to as the event's data. 

[`defines.event.key_down`](/lua/events/key_down.md) is a commonly used event that triggers when a key is pressed. The pressed key and the state of other modifier keys are passed to the callback function as event data, allowing the script to check which key has been pressed:

```lua
local function key_down_callback(data)
    if data.key == defines.key.f5 then
        if data.shift_down then
            sledge.log("Shift + F5 was pressed.")
        else
            sledge.log("F5 was pressed.")
        end
    end
end

sledge.register_event(defines.event.key_down, key_down_callback)
```