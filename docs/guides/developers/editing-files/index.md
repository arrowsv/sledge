Mods can change the game by adding, replacing, or editing its files using these approaches:
 
[Editing XML files](editing-xml-files.md)
:   For `.xtbl`, `.dtodx`, and `.gtodx` files. Use `sledge.register_xml_edit` to change specific entries without breaking compatibility with other mods.

---

[Overriding files](overriding-files.md)
:   For any other file format, such as a `.scriptx` file. Use `sledge.register_file` to add new files or replace existing ones entirely.

---

[Overriding files with packfiles](overriding-files.md#registering-a-packfile)
:   For files stored in a `.vpp_pc` packfile containing multiple files. Use `sledge.register_packfile`.

!!! warning "Avoid overriding XML files"
    Replacing an entire `.xtbl` file using `sledge.register_file` causes conflicts where one mod overwrites another. Always prefer `sledge.register_xml_edit` instead.

If you are transitioning from the older `modinfo.xml` format, see how to [convert legacy mods](legacy-mods.md).