#include "common/logging.hpp"
#include "common/utils/imgui.hpp"
#include "common/config.hpp"
#include "common/mods.hpp"

#include "gui.hpp"

#include <spdlog/spdlog.h>
#include <windows.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#undef GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace {
    unsigned char icon_data[] = {
#include "icon.png.h"
    };

    void set_window_icon(GLFWwindow* window) {
        GLFWimage image;
        int channels;

        image.pixels = stbi_load_from_memory(icon_data, ARRAYSIZE(icon_data), &image.width,
                                             &image.height, &channels, 4);

        if (image.pixels) {
            glfwSetWindowIcon(window, 1, &image);
            stbi_image_free(image.pixels);
        }
    }
}

int main() {
    auto sledge_dir = utils::os::get_module_directory(nullptr);

    logging::initialize(sledge_dir, "launcher");
    config::get().initialize(sledge_dir);
    mods::manager::get().initialize(sledge_dir / "mods");
    config::get().save();

    if (!glfwInit()) {
        spdlog::error("Failed to initialize GLFW.");
        return 1;
    }

    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    int width = 704;
    int height = 396;

    GLFWwindow* window = glfwCreateWindow(width, height, "Sledge", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return 1;
    }

    set_window_icon(window);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* videoMode = glfwGetVideoMode(primaryMonitor);

    int monitorX, monitorY;
    glfwGetMonitorPos(primaryMonitor, &monitorX, &monitorY);

    int centerX = monitorX + (videoMode->width - width) / 2;
    int centerY = monitorY + (videoMode->height - height) / 2;

    glfwSetWindowPos(window, centerX, centerY);

    utils::imgui::initialize();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    gui::load_background_textures();

    while (!glfwWindowShouldClose(window)) {
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

    return 0;
}