#include "Startup.hpp"

#include "Renderer/API/imgui_impl_glfw.hpp"
#include "Renderer/API/imgui_impl_opengl3.hpp"

#include <GLFW/glfw3.h>  // Will drag system OpenGL headers
#include <imgui.h>

#include <cstdio>
#include <ranges>

enum SettingsSection { Control, Movement, Camera, Sensors, System, Appearance };

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

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &imGuiIo = ImGui::GetIO();
    (void)imGuiIo;
    imGuiIo.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    imGuiIo.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    imGuiIo.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version.data());

    // Load font
    constexpr auto fontSize = 24.0F;
    imGuiIo.Fonts->AddFontFromFileTTF("Fonts/SegoeUI.ttf", fontSize);

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45F, 0.55f, 0.60f, 1.00f);

    // Main loop
    while (glfwWindowShouldClose(window) == 0) {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to
        // tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data
        // to your main application, or clear/overwrite your copy of the mouse
        // data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input
        // data to your main application, or clear/overwrite your copy of the
        // keyboard data. Generally you may always pass all inputs to dear
        // imgui, and hide them from your application based on those two flags.
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 1. Show the big demo window (Most of the sample code is in
        // ImGui::ShowDemoWindow()! You can browse its code to learn more about
        // Dear ImGui!).
        if (show_demo_window) {
            ImGui::ShowDemoWindow(&show_demo_window);
        }

        // 2. Show a simple window that we create ourselves. We use a Begin/End
        // pair to create a named window.
        {
            static float flt = 0.0F;
            static int counter = 0;

            // Create a window called "Hello, world!" and append into it.
            ImGui::Begin("Hello, world!");

            // Display some text (you can use a format strings too)
            ImGui::TextUnformatted("This is some useful text.");

            // Edit bools storing our window open/close state
            ImGui::Checkbox("Demo Window", &show_demo_window);

            ImGui::Checkbox("Another Window", &show_another_window);

            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::SliderFloat("float", &flt, 0.0F, 1.0F);

            // Edit 3 floats representing a color
            ImGui::ColorEdit4("clear color", reinterpret_cast<float *>(&clear_color));

            if (ImGui::Button("Button")) {
                // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            }

            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            auto toFrameTime = [](auto framerate) { return 1000.0F / framerate; };
            const auto framerate = ImGui::GetIO().Framerate;
            ImGui::TextColored(clear_color, "Application average %.3f ms/frame (%.1f FPS)", toFrameTime(framerate),
                               framerate);
            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_another_window) {
            // Pass a pointer to our bool variable
            // (the window will have a closing button that will clear the bool when clicked)
            ImGui::Begin("Another Window", &show_another_window);
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me")) {
                show_another_window = false;
            }
            ImGui::End();
        }

        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("Menu")) {
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("View", false)) {
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Help", false)) {
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }

        ImGui::Begin("Settings");
        {
            static auto currentSection = SettingsSection::Control;

            constexpr auto sectionSelectorWidth = 200;

            ImGui::BeginChild("Section Selector", ImVec2(sectionSelectorWidth, 0), true);
            {
                ImGui::Text("Underwater Vehicle");
                ImGui::Spacing();
                ImGui::Indent();
                if (ImGui::Selectable("Control", currentSection == SettingsSection::Control)) {
                    currentSection = SettingsSection::Control;
                }
                if (ImGui::Selectable("Movement", currentSection == SettingsSection::Movement)) {
                    currentSection = SettingsSection::Movement;
                }
                if (ImGui::Selectable("Camera", currentSection == SettingsSection::Camera)) {
                    currentSection = SettingsSection::Camera;
                }
                if (ImGui::Selectable("Sensors", currentSection == SettingsSection::Sensors)) {
                    currentSection = SettingsSection::Sensors;
                }
                ImGui::Unindent();
                ImGui::Spacing();

                ImGui::Text("Client");
                ImGui::Spacing();
                ImGui::Indent();
                if (ImGui::Selectable("System", currentSection == SettingsSection::System)) {
                    currentSection = SettingsSection::System;
                }

                if (ImGui::Selectable("Appearance", currentSection == SettingsSection::Appearance)) {
                    currentSection = SettingsSection::Appearance;
                }
                ImGui::Unindent();
                ImGui::Spacing();
            }
            ImGui::EndChild();

            ImGui::SameLine();

            ImGui::BeginChild("Settings selector", ImVec2(0, 0), true);
            {
                if (currentSection == SettingsSection::Movement) {
                    ImGui::Text("Motors settings");
                    ImGui::Spacing();
                    static int motorsNumber = 8;
                    ImGui::InputInt("Quantity", &motorsNumber);
                    ImGui::Spacing();
                    static int maximumSpeed = 100;
                    ImGui::SliderInt("Maximum speed", &maximumSpeed, 0, 100);
                    ImGui::Spacing();
                    ImGui::Text("Speed coefficients");
                    ImGui::Spacing();
                    if (ImGui::BeginTable("Motor coefficients table", 7, ImGuiTableFlags_Borders)) {
                        ImGui::TableSetupColumn("No.");
                        ImGui::TableSetupColumn("Fx");
                        ImGui::TableSetupColumn("Fy");
                        ImGui::TableSetupColumn("Fz");
                        ImGui::TableSetupColumn("Mx");
                        ImGui::TableSetupColumn("My");
                        ImGui::TableSetupColumn("Mz");
                        ImGui::TableHeadersRow();
                        for (int row = 0; row < motorsNumber; row++) {
                            ImGui::TableNextRow();
                            for (int column = 0; column < 7; column++) {
                                ImGui::TableSetColumnIndex(column);
                                if (column == 0) {
                                    ImGui::Text("%d", row + 1);
                                } else {
                                    ImGui::Text("0.0");
                                }
                            }
                        }
                        ImGui::EndTable();
                    }
                }
            }
            ImGui::EndChild();
        }
        ImGui::End();

        // Rendering
        ImGui::Render();
        int display_w;
        int display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
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
