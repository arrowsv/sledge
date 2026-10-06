Mods can change the game by adding, replacing, or editing its files. Sledge offers three ways to do this. Choose based on the kind of file you want to change:
 
[Editing XML files](editing-xml-files)
:   For `.xtbl`, `.dtodx`, and `.gtodx` files. Use `sledge.register_xml_edit` to change individual values and entries. Multiple mods can edit the same file without overwriting each other, so this is the best choice for most mods.
 
---

[Overriding files](overriding-files)
:   For any other file, such as a `.scriptx` file. Use `sledge.register_file` to add a new file or fully replace an existing one.

---

[Overriding files (packfiles)](overriding-files#registering-a-packfile)
:   For files stored in a `.vpp_pc` packfile. Use `sledge.register_packfile` to add or replace every file inside it.

!!! info
 
    Replacing a whole `.xtbl` file with `sledge.register_file` will conflict with any other mod that changes the same file, and one mod's changes will overwrite the other's. Use `sledge.register_xml_edit` instead.
 
If you have an existing mod made in the legacy `modinfo.xml` format, see how to [convert legacy mods](legacy-mods).