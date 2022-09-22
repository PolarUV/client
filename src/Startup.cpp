#include "Startup.hpp"

#include "Renderer/API/imgui_impl_glfw.hpp"
#include "Renderer/API/imgui_impl_opengl3.hpp"

#include <GLFW/glfw3.h>  // Will drag system OpenGL headers
#include <imgui.h>

#include "App/MainWindow.hpp"

#include <cstdio>
#include <ranges>

static void glfw_error_callback(int error, const char *description) {
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

int main() {
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (glfwInit() == 0) {
        return 1;
    }

    // GL 3.0 + GLSL 130
    constexpr std::string_view glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+
    // only glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // 3.0+ only

    // Create window with graphics context
    int count = 0;
    auto *const monitors = glfwGetMonitors(&count);

    // Get first monitor
    const GLFWvidmode *mode = glfwGetVideoMode(monitors[0]);
    auto *const window =
        glfwCreateWindow(mode->width, mode->height, "New PolarUV with Dear ImGui", monitors[0], nullptr);

    if (window == nullptr) {
        return 1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);  // Enable vsync

    auto mainWindow = App::MainWindow();

    constexpr std::array<ImWchar, 5> ranges = {
        0x0020, 0x00FF,  // Basic Latin + Latin Supplement
        0x0400, 0x044F,  // Cyrillic
        0,
    };
    constexpr auto fontSize = 24.0F;
    ImGui::GetIO().Fonts->AddFontFromFileTTF("Fonts/SegoeUI.ttf", fontSize, nullptr, ranges.cbegin());

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version.data());

    // Main loop
    while (glfwWindowShouldClose(window) == 0) {
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        mainWindow.DrawFrame();

        // Rendering
        int display_w;
        int display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        constexpr ImVec4 clear_color = ImVec4(0.45F, 0.55f, 0.60f, 1.00f);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w,
                     clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
