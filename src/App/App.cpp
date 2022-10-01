#include "App.hpp"

void App::DrawFrameImpl() {
    ImGui::NewFrame();

    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("Меню", false)) {
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Окна", false)) {
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Справка", false)) {
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    drawer_();

    ImGui::Render();
}
