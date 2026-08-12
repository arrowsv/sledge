===================
key_up
===================

This event is triggered a key is released.

.. code-block:: lua

  local function key_up_callback(data)
  end

  mod:register_event(defines.event.key_up, key_up_callback)

Event data
----------

* ``key`` (:lua:enum:`defines.key`)
* ``shift_down`` (boolean)
* ``control_down`` (boolean)
* ``alt_down`` (boolean)

Examples
----------

.. code-block:: lua
  
  local function key_up_callback(data)
      if data.key == defines.key.f5 then
          mod:log("The user released F5.")
      end
  end

  mod:register_event(defines.event.key_up, key_up_callback)