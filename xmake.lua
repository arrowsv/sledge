set_languages("c++23")

add_rules("mode.debug", "mode.release", "mode.releasedbg")
add_rules("plugin.compile_commands.autoupdate")

set_arch("x86")

if is_host("linux") then 
    set_plat("mingw") 
end

if is_mode("releasedbg") then 
    add_cxflags("-g1") 
end

-- requires: common
add_requires("magic_enum 0.9.8")
add_requires("plog 1.1.11")
add_requires("nlohmann_json 3.12.0")
add_requires("nativefiledialog-extended 1.3.0")

-- requires: launcher
add_requires("glfw 3.4")
add_requires("glad 0.1.36")

-- requires: patch
add_requires("minhook 1.3.4")
add_requires("picosha2 2022.08.08")
add_requires("sol2 3.5.0")
add_requires("pugixml 1.16")
add_requires("safetyhook 0.6.10")

-- global
add_includedirs("src")
add_includedirs("deps")
add_includedirs("deps/crashcatch")
add_includedirs("deps/imgui")
add_cxflags("-Wunused-variable", "-Wunused-function")

-- targets
target("common")
    set_kind("static")
    add_packages("plog", "nlohmann_json", "nativefiledialog-extended", "magic_enum")
    
    add_files("src/common/**.cpp")
    add_files("deps/imgui/*.cpp")
    
    add_links("comdlg32")
    
    add_defines("MAGIC_ENUM_RANGE_MIN=0")
    add_defines("MAGIC_ENUM_RANGE_MAX=256")
    
target("launcher")
    set_kind("binary")
    set_filename("sledge.exe")
    
    add_deps("common")
    add_packages("plog", "glfw", "glad", "magic_enum")
    --add_embeddirs("src/launcher/assets")
    add_includedirs("src")
    
    add_rules("utils.bin2c", {extensions = {".png"}})
    add_files("src/launcher/assets/*.png")

    add_files("src/launcher/**.cpp")
    add_files(
        "deps/imgui/backends/imgui_impl_glfw.cpp",
        "deps/imgui/backends/imgui_impl_opengl3.cpp"
    )
    
    add_defines("IMGUI_IMPL_OPENGL_LOADER_GLAD")
    add_ldflags("-mwindows", {force = true})
    add_ldflags("-static", "-static-libgcc", "-static-libstdc++")
    
target("patch")
    set_kind("shared")
    set_filename("sledge.dll")
    
    add_deps("common")
    add_packages("plog", "sol2", "minhook", "nlohmann_json", "picosha2", "pugixml", "safetyhook", "magic_enum")
    
    add_files("src/patch/**.cpp")
    add_files(
        "deps/imgui/backends/imgui_impl_win32.cpp",
        "deps/imgui/backends/imgui_impl_dx11.cpp"
    )

    add_shflags("-static", "-static-libgcc", "-static-libstdc++")
    add_syslinks("d3dcompiler", "gdi32", "dwmapi", "dbghelp")