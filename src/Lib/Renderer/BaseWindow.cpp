#include "Lib/Renderer/API/BaseWindow.hpp"

#include <cstdio>
#include <string_view>

void glfw_error_callback(int error, const char *description) {
    assert(fprintf(stderr, "Glfw Error %d: %s\n", error, description) != -1);
}

GLFWwindow *InitOpenGL() {
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (glfwInit() == 0) {
        return nullptr;
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
        return window;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);  // Enable vsync

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version.data());

    return window;
}

void SetupImGui() {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &imGuiIo = ImGui::GetIO();
    imGuiIo.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    imGuiIo.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    imGuiIo.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
}

void SetupFont(float fontSize, const std::array<ImWchar, 5> &ranges) {
    ImGui::GetIO().Fonts->AddFontFromFileTTF("Fonts/SegoeUI.ttf", fontSize, nullptr, ranges.cbegin());
}

void SetupTheme() {
    auto &style = ImGui::GetStyle();
    // NOLINTBEGIN
    style.WindowRounding = 3.0F;
    style.ChildRounding = 3.0F;
    style.FrameRounding = 3.0F;
    style.TabRounding = 3.0F;
    style.PopupRounding = 3.0F;
    style.GrabRounding = 3.0F;
    style.ScrollbarRounding = 3.0F;
    style.ScrollbarSize = 10.0F;
    style.FrameBorderSize = 1.0F;
    style.WindowBorderSize = 1.0F;
    style.PopupBorderSize = 1.0F;
    auto &colors = style.Colors;
    colors[ImGuiCol_Text] = ImVec4(0.95F, 0.95F, 0.95F, 1.00F);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.50F, 0.50F, 0.50F, 1.00F);
    colors[ImGuiCol_WindowBg] = ImVec4(0.12F, 0.12F, 0.12F, 1.00F);
    // colors[ImGuiCol_ChildBg] = ImVec4(0.04F, 0.04F, 0.04F, 0.50F);
    colors[ImGuiCol_ChildBg] = ImVec4(0.12F, 0.12F, 0.12F, 1.00F);
    colors[ImGuiCol_PopupBg] = ImVec4(0.12F, 0.12F, 0.12F, 0.94F);
    colors[ImGuiCol_Border] = ImVec4(0.25F, 0.25F, 0.27F, 0.50F);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00F, 0.00F, 0.00F, 0.00F);
    colors[ImGuiCol_FrameBg] = ImVec4(0.20F, 0.20F, 0.22F, 0.50F);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.25F, 0.25F, 0.27F, 0.75F);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.30F, 0.30F, 0.33F, 1.00F);
    // colors[ImGuiCol_TitleBg] = ImVec4(0.04F, 0.04F, 0.04F, 1.00F);
    colors[ImGuiCol_TitleBg] = ImVec4(0.18F, 0.18F, 0.19F, 1.00F);
    // colors[ImGuiCol_TitleBgActive] = ImVec4(0.04F, 0.04F, 0.04F, 1.00F);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.23F, 0.23F, 0.23F, 1.00F);
    // colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.04F, 0.04F, 0.04F, 0.75F);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.18F, 0.18F, 0.19F, 1.00F);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.18f, 0.18f, 0.19f, 1.00f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.24F, 0.24F, 0.26F, 0.75F);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.41F, 0.41F, 0.41F, 0.75F);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.62F, 0.62F, 0.62F, 0.75F);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.94F, 0.92F, 0.94F, 0.75F);
    colors[ImGuiCol_CheckMark] = ImVec4(0.60F, 0.60F, 0.60F, 1.00F);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.41F, 0.41F, 0.41F, 0.75F);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.62F, 0.62F, 0.62F, 0.75F);
    colors[ImGuiCol_Button] = ImVec4(0.20F, 0.20F, 0.22F, 1.00F);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.25F, 0.25F, 0.27F, 1.00F);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.41F, 0.41F, 0.41F, 1.00F);
    colors[ImGuiCol_Header] = ImVec4(0.18F, 0.18F, 0.19F, 1.00F);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.25F, 0.25F, 0.27F, 1.00F);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.41F, 0.41F, 0.41F, 1.00F);
    colors[ImGuiCol_Separator] = ImVec4(0.25F, 0.25F, 0.27F, 1.00F);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.41F, 0.41F, 0.41F, 1.00F);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.62F, 0.62F, 0.62F, 1.00F);
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.30F, 0.30F, 0.33F, 0.75F);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.41F, 0.41F, 0.41F, 0.75F);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.62F, 0.62F, 0.62F, 0.75F);
    colors[ImGuiCol_Tab] = ImVec4(0.21F, 0.21F, 0.22F, 1.00F);
    colors[ImGuiCol_TabHovered] = ImVec4(0.37F, 0.37F, 0.39F, 1.00F);
    colors[ImGuiCol_TabActive] = ImVec4(0.30F, 0.30F, 0.33F, 1.00F);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.12F, 0.12F, 0.12F, 0.97F);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.18F, 0.18F, 0.19F, 1.00F);
    colors[ImGuiCol_DockingPreview] = ImVec4(0.26F, 0.59F, 0.98F, 0.50F);
    colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.20F, 0.20F, 0.20F, 1.00F);
    colors[ImGuiCol_PlotLines] = ImVec4(0.61F, 0.61F, 0.61F, 1.00F);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00F, 0.43F, 0.35F, 1.00F);
    colors[ImGuiCol_PlotHistogram] = ImVec4(0.90F, 0.70F, 0.00F, 1.00F);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00F, 0.60F, 0.00F, 1.00F);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26F, 0.59F, 0.98F, 0.50F);
    colors[ImGuiCol_DragDropTarget] = ImVec4(1.00F, 1.00F, 0.00F, 0.90F);
    colors[ImGuiCol_NavHighlight] = ImVec4(0.26F, 0.59F, 0.98F, 1.00F);
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00F, 1.00F, 1.00F, 0.70F);
    colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80F, 0.80F, 0.80F, 0.20F);
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80F, 0.80F, 0.80F, 0.35F);
    // NOLINTEND
}
