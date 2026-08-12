===================
alert_level_changed
===================

This event is triggered when the alert level has changed.

.. code-block:: lua

  local function alert_level_changed_callback(data)
  end

  mod:register_event(defines.event.alert_level_changed, alert_level_changed_callback)

Event data
----------

* ``previous_alert_level`` (:lua:enum:`defines.alert_level`)
* ``new_alert_level`` (:lua:enum:`defines.alert_level`)