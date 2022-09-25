#include "MainWindow.hpp"

namespace App {

void MainWindow::DrawFrameImpl() {
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
}  // namespace App
