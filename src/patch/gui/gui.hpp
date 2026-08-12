#pragma once

#include "common/mods.hpp"

#include <imgui.h>
#include <memory>
#include <plog/Log.h>
#include <sol/sol.hpp>

namespace gui {

class panel {
  public:
    std::string title;
    bool open = false;
    ImGuiWindowFlags flags;
    ImVec2 default_size;

    ~panel() = default;
    panel(const std::string& title, ImGuiWindowFlags flags = 0, ImVec2 default_size = {400, 300})
        : title(title), flags(flags), default_size(default_size) {};

    virtual void draw() {}
};

class mod_panel : public panel {
  private:
    sol::protected_function draw_function;

  public:
    const mods::mod_info mod_info;

    mod_panel(const std::string& title, const mods::mod_info mod_info,
              sol::protected_function& draw_function, ImGuiWindowFlags flags,
              ImVec2 default_size = {400, 300})
        : panel(title, flags, default_size), mod_info(mod_info), draw_function(draw_function) {
        this->title = title + "##" + mod_info.id;
    }

    void draw() override;
};

class manager {
  public:
    static manager& get() {
        static manager instance;
        return instance;
    }

    bool g_show_windows = false;

    void initialize();
    void draw();

    void register_core_window(std::shared_ptr<panel> window);
    void register_core_overlay(std::shared_ptr<panel> overlay);
    void register_mod_window(std::shared_ptr<mod_panel> window);
    void register_mod_overlay(std::shared_ptr<mod_panel> overlay);
    void clear_mod_panels();

  private:
    bool m_showing_demo_window = false;

    void draw_main_menu_bar();
    void draw_dockspace();
};
} // namespace gui
