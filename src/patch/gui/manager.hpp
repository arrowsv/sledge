#pragma once

#include "common/mods.hpp"

#include <imgui.h>
#include <memory>
#include <sol/sol.hpp>

namespace gui {

    enum class panel_anchor { top_left, top_right, bottom_left, bottom_right };

    class panel {
      public:
        std::string title;
        bool open = false;
        ImGuiWindowFlags flags;
        ImVec2 default_size;

        std::optional<mods::mod_info> mod_info;
        std::optional<sol::protected_function> draw_function;

        panel_anchor anchor = panel_anchor::top_right;
        const float padding = 10.0f;

        ~panel() = default;

        panel(const std::string& title, ImGuiWindowFlags flags = 0,
              ImVec2 default_size = {400, 300})
            : title(title), flags(flags), default_size(default_size) {};

        panel(const std::string& title, sol::protected_function draw_function,
              ImGuiWindowFlags flags = 0, ImVec2 default_size = {400, 300})
            : title(title), flags(flags), default_size(default_size),
              draw_function(std::move(draw_function)) {}

        panel(const std::string& title, mods::mod_info mod_info,
              sol::protected_function draw_function, ImGuiWindowFlags flags = 0,
              ImVec2 default_size = {400, 300})
            : title(title + "##" + mod_info.id), flags(flags), default_size(default_size),
              mod_info(std::move(mod_info)), draw_function(std::move(draw_function)) {}

        virtual void draw();
    };

    class manager {
      public:
        static manager& get() {
            static manager instance;
            return instance;
        }

        bool g_show_overlay = false;

        void initialize();
        void draw();

        void register_window(std::shared_ptr<panel> window);
        void register_widget(std::shared_ptr<panel> widget);
        void clear_mod_panels();

        bool wants_mouse() const;
        bool wants_keyboard() const;
        bool is_input_required() const;

      private:
        std::vector<std::shared_ptr<panel>> windows{};
        std::vector<std::shared_ptr<panel>> widgets{};

        bool m_showing_demo_window = false;

        void draw_main_menu_bar();
        void draw_widgets();
        void draw_windows();
    };
}
