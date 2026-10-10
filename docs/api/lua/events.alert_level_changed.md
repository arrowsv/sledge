# alert_level_changed

This event is triggered when the alert level has changed.

```lua
local function alert_level_changed_callback(data)
end

sledge.register_event(enums.event.alert_level_changed, alert_level_changed_callback)
```

## Event data

* `previous_alert_level` (<code>[enums.alert_level](enums.alert_level.md)</code>)
* `new_alert_level` (<code>[enums.alert_level](enums.alert_level.md)</code>)
