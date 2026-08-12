======
Events
======

Events allow for scripts to run functions when specific things in the game happen. 

Registering an event
---------------------
The :lua:meth:`types.mod_info.register_event` function is used to register a callback function that will run when the game triggers that event.

For example, here is the code to subscribe to the :doc:`events/save_loaded` event:

.. code-block:: lua

  mod:register_event(defines.event.save_loaded, function()
      mod:log("The save has loaded.")
  end)

Retrieving event data
----------------------

Events can pass data to the callback function as a table. The table's fields depend on the event and are listed on their individual pages.

An event's data table is passed as the first argument to the callback function. To demonstrate, the :doc:`events/alert_level_changed` event passes a table with two fields:

.. code-block:: lua

  mod:register_event(defines.event.alert_level_changed, function(data)
      local previous_alert_level = data.previous_alert_level
      local new_alert_level = data.new_alert_level
  end)

The name of the parameter does not matter, but ``data`` is recommended so that it's clear that the event's data is being accessed.

Filtering an event
-------------------

Events can be filtered to only run the callback function if a certain condition is met. Always opt to use a filter if it supports your use case.

For example, the :doc:`events/parse_xml` event supports filtering based on the name of the XML file being parsed. This is a shortcut for comparing the ``name`` field in the event data to the given filter. To demonstrate, these do the same thing:

.. code-block:: lua

  -- Registering with a filter.
  mod:register_event(defines.event.parse_xml, function(data)
      mod:log("We are now editing the character.xtbl file.")
  end, { filter = "character.xtbl" })

  -- Registering without a filter.
  mod:register_event(defines.event.parse_xml, function(data)
      if data.name ~= "character.xtbl" then
          return
      end
      mod:log("We are now editing the character.xtbl file without a filter.")
  end)

In the above example where no filter is provided, the game must run the callback function for every XML file being parsed, despite us only wanting to edit ``character.xtbl``. This should be avoided because the filter lets us achieve the same outcome without needing the game to run the callback function unnecessarily.

List of events
---------------

.. toctree::
  :maxdepth: 1
  :glob:

  events/*