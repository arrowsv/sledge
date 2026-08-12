===================
key_down
===================

This event is triggered a key is pressed.

.. code-block:: lua

  local function key_down_callback(data)
  end

  mod:register_event(defines.event.key_down, key_down_callback)

Event data
----------

* ``key`` (:lua:enum:`defines.key`)
* ``shift_down`` (boolean)
* ``control_down`` (boolean)
* ``alt_down`` (boolean)

Examples
----------

.. code-block:: lua
  
  local function key_down_callback(data)
      if data.key == defines.key.f5 then
          mod:log("The user pressed F5.")

          if data.shift_down then
              mod:log("The user was pressing F5 and shift.")
          end
      end
  end

  mod:register_event(defines.event.key_down, key_down_callback)