===================
parse_xml
===================

This event is triggered before an XML file is parsed by the game. This can be used to retrieve and edit XML values.

See the :doc:`../xml` page for an in-depth explanation.

.. note::
  This event can be filtered based on the ``name`` event data.

.. code-block:: lua

  local function parse_xml_callback(data)
  end

  mod:register_event(defines.event.parse_xml, parse_xml_callback, { filter = "" })

Event data
----------

* ``name`` (string) - Name of the file (e.g. ``character.xtbl``).
* ``document`` (:lua:class:`types.xml_document`)

Examples
---------

.. code-block:: lua

  -- Retrieves the "Height" node of each
  -- character and sets them to `0.5`.
  mod:register_event(defines.event.parse_xml, function(data)
      local table = data.document:get("root"):get("Table")
      
      local heights = table:get_multiple_from_path("//Height")
      for _, height in ipairs(heights) do
          height:set("0.5")
      end
  end, { filter = "character.xtbl" })