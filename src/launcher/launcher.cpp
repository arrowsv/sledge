#include "launcher.hpp"

#include "common/logging.hpp"
#include "common/utils/imgui.hpp"
#include "common/config.hpp"
#include "common/mods.hpp"

#include "launcher/gui.hpp"

#include <plog/Log.h>
#include <windows.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#undef GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

namespace launcher {

static choice g_result = choice::quit;
static bool g_done = false;

choice run() {
    auto sledge_directory = utils::os::get_module_directory(nullptr);

    logging::initialize(sledge_directory, "sledge_launcher");
    config::get().initialize(sledge_directory);
    mods::manager::get().initialize(sledge_directory / "mods");
    config::get().save();

    if (!glfwInit()) {
        PLOG_ERROR << "Failed to initialize GLFW, continuing in vanilla mode.";
        return choice::play_vanilla;
    }

    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    GLFWwindow* window = glfwCreateWindow(576, 324, "Sledge", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return choice::play;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* videoMode = glfwGetVideoMode(primaryMonitor);

    // 3. Extract monitor position (crucial for multi-monitor setups)
    int monitorX, monitorY;
    glfwGetMonitorPos(primaryMonitor, &monitorX, &monitorY);

    // 4. Calculate center position
    int centerX = monitorX + (videoMode->width - 576) / 2;
    int centerY = monitorY + (videoMode->height - 324) / 2;

    // 5. Position and show the window
    glfwSetWindowPos(window, centerX, centerY);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_NavEnableGamepad;
    io.IniFilename = NULL;

    utils::imgui::initialize_styles();
    utils::imgui::initialize_fonts();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    launcher::gui::load_background_textures();

    while (!g_done && !glfwWindowShouldClose(window)) {
        glfwPollEvents();
        if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0) {
            ImGui_ImplGlfw_Sleep(10);
            continue;
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        gui::draw();

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return g_done ? g_result : choice::quit;
}

void select_play() {
    g_result = choice::play;
    g_done = true;
}
void select_play_vanilla() {
    g_result = choice::play_vanilla;
    g_done = true;
}

} // namespace launcher