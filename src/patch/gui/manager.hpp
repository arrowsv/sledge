#pragma once

#include "common/mods.hpp"

#include <imgui.h>
#include <memory>
#include <sol/sol.hpp>

namespace gui {

    enum class panel_anchor { top_left, top_right, bottom_left, bottom_right };

    struct panel_options {
        ImGuiWindowFlags flags = ImGuiWindowFlags_None;
        ImVec2 default_size = {500, 300};
        bool open = false;
        bool requires_gameplay = false;
        panel_anchor anchor = panel_anchor::top_right;
        std::optional<sol::protected_function> draw_function = std::nullopt;
    };

    class panel {
      public:
        std::string title;
        std::optional<mods::mod_info> mod_info;

        panel_options options;

        ~panel() = default;
        panel(std::string title, panel_options opts = {})
            : title(std::move(title)), options(std::move(opts)) {}
        panel(const std::string& title, mods::mod_info info, panel_options opts = {})
            : title(title + "##" + info.id), mod_info(std::move(info)), options(std::move(opts)) {}

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
