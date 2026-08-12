============
Introduction
============

This page explains how to create a basic mod for the game with Sledge.

Mods are only recognised if they are placed inside a folder named ``mods`` within the same directory as ``sledge.exe`` and ``sledge.dll``.

Mod structure
-------------

A mod requires its own folder within the ``mods`` directory that contains two files:

* ``mod.json`` - The mod's metadata which is read by Sledge.
* ``mod.lua`` - The mod's main script which is executed only once by Sledge immediately after it's initialized.

The folder structure should be as follows:

.. code-block::

  Sledge/
  ├── mods/
  │   └── Example Mod/
  │       ├── mod.json
  │       └── mod.lua
  ├── sledge.exe
  └── sledge.dll

Creating a metadata file
------------------------

This file must have the name ``mod.json``. It can contain the following fields:

* ``id`` - Unique identifier of the mod. For consistency sake, use the ``author`` and ``name`` separated by a ``.`` symbol (e.g. ``arrows.safehouse_vehicle_selector``). Ensure that it is written in all lowercase with no special symbols and replace all spaces with underscores.
* ``name`` - Display name of the mod.
* ``author`` - Author of the mod.
* ``description`` - Description of the mod.
* ``version`` - Version of the mod.
* ``options`` - Optional list of options that allows the user to make choices accessible to the mod.
    
  * ``option`` - Display name of the option.

    * ``type`` - The type of the option. The following are available: ``multiple``, ``custom``, ``key``, ``checkbox``.

      * ``multiple`` - Allows the user to select one out of multiple choices in a listbox. Maps to a ``string`` in Lua.
      * ``custom`` - Allows the user to write a custom value. Maps to a ``string`` in Lua.
      * ``key`` - Allows the user to select a key. Maps to a :lua:enum:`defines.key` in Lua.
      * ``checkbox`` - Allows the user to select true or false. Maps to a ``boolean`` in Lua.

    * ``default`` - Default value for the option. This can be used with all types.
    * ``choices`` - This is used for options with the ``multiple`` type. This field requires an array of strings (``"choices": ["", ""]``). If desired, an option can reuse the same choices as another option (must be of type ``multiple`` and defined after the option that will be reused) by writing the name of the option instead of an array: ``"choices": "CHOICE_NAME"``.

.. code-block:: json

    {
        "id": "",
        "name": "",
        "author": "",
        "description": "",
        "version": "0.1.0",
        "options": {
            "My option": {
                "type": "multiple",
                "choices": ["One", "Two"]
            }
        }
    }

Creating a script file
----------------------

This file must have the name ``mod.lua``. In this file, the following can be defined: 

* Local variables
* Local functions
* Event, window, and overlay registrations

Code that modifies the game should not be directly written into the file without first being placed into a callback function and checking that the classes being accessed are valid.

The global :lua:obj:`mod` variable is used to access mod-specific information and register events, windows, and overlays. See :lua:class:`types.mod_info` for the properties and methods available for the variable.

Retrieving option values
^^^^^^^^^^^^^^^^^^^^^^^^^

If a mod has options defined in its ``mod.json`` file, ``mod.lua`` can retrieve and store the choice chosen by the user with :lua:meth:`types.mod_info.get_option`.

.. tab-set::

    .. tab-item:: mod.json

        .. code-block:: json

            "options": {
                "Enabled": {
                    "type": "checkbox",
                    "default": "false"
                },
                "Multiple choices": {
                    "type": "multiple",
                    "default": "Choice 2",
                    "choices": ["Choice 1", "Choice 2"]
                },
                "Toggle key": {
                    "type": "key",
                    "default": "f1"
                }
            }
    
    .. tab-item:: mod.lua

        .. code-block:: lua

            -- This is a boolean.
            local option_enabled = mod:get_option("Enabled")

            -- This is a string.
            local option_multiple_choices = mod:get_option("Multiple choices")

            -- This is a defines.key.
            local option_toggle_key = mod:get_option("Toggle key")

            -- This is nil because it doesn't exist.
            local option_missing = mod:get_option("Missing")

Registering an event
^^^^^^^^^^^^^^^^^^^^^

As an example, to create a script that will change the player's salvage once a save has loaded, use :lua:meth:`types.mod_info.register_event` to register to the :lua:data:`defines.event.save_loaded` event.

.. code-block:: lua

  -- The function that will be called by the event.
  local function save_loaded()
      local player = game.get_player()

      -- Check if the player exists before continuing.
      -- Even though the player should never be nil within the save_loaded event, 
      -- it's always good practice to check.
      if not player then
          return
      end

      player.salvage = 50000
  end

  -- Register the function to the save_loaded event.
  mod:register_event(defines.event.save_loaded, save_loaded)