============
save_loaded
============

This event is triggered when a save has loaded.

.. code-block:: lua

  local function save_loaded_callback()
  end

  mod:register_event(defines.event.save_loaded, save_loaded_callback)