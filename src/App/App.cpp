#include "App.hpp"

void App::DrawFrameImpl() {
    ImGui::NewFrame();

    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("Окна", true)) {
            drawer_.DrawWindowsState();
            ImGui::EndMenu();
        }
        ImGui::SetCursorPosX(ImGui::GetContentRegionMax().x + ImGui::GetStyle().ItemSpacing.x - 100);
        if (ImGui::Button("Закрыть", ImVec2(100, 31))) {
            glfwSetWindowShouldClose(GetBaseWindow(), GLFW_TRUE);
        }
        ImGui::EndMainMenuBar();
    }

    drawer_.DrawWindows();

    ImGui::Render();
}
