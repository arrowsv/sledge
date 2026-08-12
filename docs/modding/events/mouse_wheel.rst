===================
mouse_wheel
===================

This event is triggered when the mouse is scrolled.

.. code-block:: lua

  local function mouse_wheel_callback(data)
  end

  mod:register_event(defines.event.mouse_wheel, mouse_wheel_callback)

Event data
----------

* ``delta`` (integer)
* ``shift_down`` (boolean)
* ``control_down`` (boolean)
* ``alt_down`` (boolean)
