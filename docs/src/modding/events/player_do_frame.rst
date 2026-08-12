===================
player_do_frame
===================

This event is triggered every single frame the player is processed. This will not be triggered while the game is paused or in the main menu.

.. code-block:: lua

  local function player_do_frame_callback(data)
  end

  mod:register_event(defines.event.player_do_frame, player_do_frame_callback)

Event data
----------

* ``player`` (:lua:class:`types.player`)