#ifndef CLIENT_BASEWINDOW_H
#define CLIENT_BASEWINDOW_H

#include "Renderer/API/imgui_impl_glfw.hpp"
#include "Renderer/API/imgui_impl_opengl3.hpp"

#include <GLFW/glfw3.h>

#include <array>
#include <stdexcept>

void glfw_error_callback(int error, const char *description);
void SetupImGui();
void SetupFont(float fontSize, const std::array<ImWchar, 5> &ranges);
void SetupTheme();
GLFWwindow *InitOpenGL();

template <class T>
class BaseWindow {
   private:
    GLFWwindow *window_;

    T &Derrived() { return *static_cast<T *>(this); }

    static constexpr std::array<ImWchar, 5> ranges_ = {
        0x0020, 0x00FF,  // Basic Latin + Latin Supplement
        0x0400, 0x044F,  // Cyrillic
        0,
    };

    static constexpr auto fontSize_ = 24.0F;

   protected:
    BaseWindow();

   public:
    void Run();
};

template <class T>
BaseWindow<T>::BaseWindow() {
    SetupImGui();
    SetupFont(fontSize_, ranges_);
    SetupTheme();

    window_ = InitOpenGL();
    if (window_ == nullptr) {
        throw std::runtime_error("OpenGL window isn't initialized");
    }
}

template <class T>
void BaseWindow<T>::Run() {
    // Main loop
    while (glfwWindowShouldClose(window_) == 0) {
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        Derrived().DrawFrameImpl();

        // Rendering
        int display_w;
        int display_h;
        glfwGetFramebufferSize(window_, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        constexpr ImVec4 clear_color = ImVec4(0.45F, 0.55f, 0.60f, 1.00f);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w,
                     clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window_);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window_);
    glfwTerminate();
}

#endif  // CLIENT_BASEWINDOW_H
