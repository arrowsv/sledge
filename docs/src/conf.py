# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

project = 'Sledge'
copyright = '2026, arrows'
author = 'arrows'
release = '0.1.0'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = [
    "sphinx_lua_ls",
    "sphinx_design"
]
exclude_patterns = ['build', 'Thumbs.db', '.DS_Store']

# -- Options for LuaLS extension ---------------------------------------------

lua_ls_project_root = "../../src/patch/lua/annotations"
lua_ls_backend = "emmylua"
lua_ls_default_options = {
   # Document members without description.
   "undoc-members": "",
   # Document protected members.
   "protected-members": "",
   # Document module's global variables.
   "globals": "",
   # Override default ordering.
   "member-order": "groupwise",
   "module-member-order": "groupwise",
   # Add table with inherited members for classes.
   "inherited-members-table": "",
}

# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = "shibuya"
html_title = project + " " + release
html_theme_options = {
  "accent_color": "bronze",
}