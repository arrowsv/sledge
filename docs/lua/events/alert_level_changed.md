# alert_level_changed

This event is triggered when the alert level has changed.

```lua
local function alert_level_changed_callback(data)
end

sledge.register_event(defines.event.alert_level_changed, alert_level_changed_callback)
```

## Event data

* `previous_alert_level` (<code>[defines.alert_level](/lua/api/defines/alert_level)</code>)
* `new_alert_level` (<code>[defines.alert_level](/lua/api/defines/alert_level)</code>)
