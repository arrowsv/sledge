=====================
Panels
=====================

This page explains registering windows and overlays, which are collectively known as panels.

.. _windows:

Windows
--------

Windows are toggleable through the Sledge menu and can be used to both display information and allow the user to configure the mod beyond what the metadata file options allow. 

Windows are only visible while the Sledge menu is enabled. If it's intended for a window to always be visible, use an :ref:`overlay <overlays>` instead.

Registering windows
^^^^^^^^^^^^^^^^^^^^

In a script file, use :lua:meth:`types.mod_info.register_window` to register a window. Similar to events, it requires a callback function which is called when the window is open to draw its contents. The callback function is called every frame while it's open.

.. code-block:: lua

  -- The function that will be called by the window while it's open.
  local function draw_my_window() end

  -- Register the window with the title "My Window" 
  -- and draw_my_window() as the draw function.
  mod:register_window("My Window", draw_my_window)

If this script is run as is, while in-game, the Sledge menu will show this window under the ``Windows`` menu item with the title ``My Window`` and the id of the mod next to it. The user can click on the menu item to toggle whether the window is visible. 

From here, the window needs to be populated with elements to allow the user to see information and/or interact with the mod.

Adding elements
^^^^^^^^^^^^^^^^

For a full list of available elements, see the :lua:class:`gui` class.

.. important::

  If a window is intended to be used while the user is in gameplay or the player is valid, checks must be placed before accessing or modifying any class.

  To implement these checks, use :lua:meth:`game.is_in_gameplay` and/or check for nil with :lua:meth:`game.get_player`.

  .. code-block:: lua

    mod:register_window("My Window", function()
        local player = game.get_player()

        if not game.is_in_gameplay() or not player then
            -- This text will be shown to the user 
            -- if not in gameplay or the player is nil.
            gui.text("A save must be loaded before using this menu.")

            -- Make sure to return here, otherwise the script will
            -- continue and cause errors.
            return
        end

        gui.text(player.salvage)
    end)

Text
""""""""

In this example, we will display the player's position by using the following functions and properties:

* :lua:meth:`gui.text`
* :lua:meth:`gui.same_line`
* :lua:meth:`game.get_player`
* :lua:data:`types.object.position` - The object type's property is linked here because :lua:class:`types.player` inherits :lua:class:`types.human`, which inherits :lua:class:`types.object`.

.. code-block:: lua

    mod:register_window("My Window", function()
        local player = game.get_player()
        
        if not game.is_in_gameplay() or not player then
            gui.text("A save must be loaded before using this menu.")
            return
        end
        
        gui.text("X:")

        -- This will place the next element on
        -- the same line as "X:" with a little spacing.
        gui.same_line()

        -- Even though `x` is a number, the text function
        -- will convert it to a string. Optionally,
        -- tostring(player.position.x) can be used.
        gui.text(player.position.x)
                                    
        gui.text("Y:")
        gui.same_line()
        gui.text(player.position.y)

        gui.text("Z:")
        gui.same_line()
        gui.text(player.position.z)
    end)

Buttons and number input
""""""""""""""""""""""""""

In this example, we will let the user add a custom amount of salvage to the player by using the following functions and properties:

* :lua:meth:`gui.text`
* :lua:meth:`gui.same_line`
* :lua:meth:`gui.input_int`
* :lua:meth:`gui.button`
* :lua:meth:`game.get_player`
* :lua:data:`types.player.salvage`

.. code-block:: lua

  -- A local table to store the input state. If `salvage_amount` was instead declared
  -- inside the `draw_my_window` function, it would be reset to `0`
  -- each frame, which is not what we want.
  local state = {
      salvage_amount = 0
  }

  local function draw_my_window()
      local player = game.get_player()
      
      if not game.is_in_gameplay() or not player then
          gui.text("A save must be loaded before using this menu.")
          return
      end
      
      -- Display the player's current salvage.
      gui.text("Current salvage:")
      gui.same_line()
      gui.text(player.salvage)

      -- gui.input_int() returns two values, `new_value` (an integer) 
      -- and `changed` (a boolean).
      --
      -- If `changed` is `true`, that means the user has changed its value,
      -- and `new_value` can be used.
      local new_value, changed = gui.input_int("Salvage amount", state.salvage_amount)
      if changed then
          -- Update state.salvage_amount to the value of `new_value`.
          state.salvage_amount = new_value
      end

      -- gui.button() returns a boolean value, `true` if it was
      -- pressed and `false` otherwise.
      if gui.button("Add") then
          -- The script will reach here if the button returns
          -- `true`. Now the player's salvage can be modified.
          player.salvage = player.salvage + state.salvage_amount
      end
  end

.. _overlays:

Overlays
---------

.. note::

  The following information assumes you have read all about :ref:`windows <windows>`, as they are mostly identical.

Overlays are windows that have no background, title bar, and are visible even if the Sledge menu is not enabled. They are intended for displaying information that is frequently changing and is beneficial for the user to see without requiring the Sledge menu to be enabled.

While it is still possible to accept user input, it is not obvious to the user, and a window would be more suited for this.

Registering overlays
^^^^^^^^^^^^^^^^^^^^

In a script file, use :lua:meth:`types.mod_info.register_overlay` to register an overlay.

.. code-block:: lua

  -- The function that will be called by the overlay while it's open.
  local function draw_my_overlay() end

  -- Register the overlay with the title "My Overlay"
  -- and draw_my_overlay() as the draw function.
  --
  -- Even though overlays do not have a title bar, the
  -- title will be used in the Sledge menu.
  mod:register_overlay("My Overlay", draw_my_overlay)

As an example, Sledge comes with a built-in overlay used for seeing the player's position. Here is its equivalent Lua script:

.. code-block:: lua

  local function position_overlay() 
      local player = game.get_player()

      if not player then
          return
      end

      gui.text("X:")
      gui.same_line()
      gui.text(player.position.x)
                                  
      gui.text("Y:")
      gui.same_line()
      gui.text(player.position.y)

      gui.text("Z:")
      gui.same_line()
      gui.text(player.position.z)
  end

  mod:register_overlay("Position", position_overlay)