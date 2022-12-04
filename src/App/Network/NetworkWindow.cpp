#include "NetworkWindow.hpp"

#include "Logger/Logger.hpp"

NetworkWindow::NetworkWindow()
    : IWindow("Сеть", true, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDocking,
              ImVec2(350, 120)) {}

void NetworkWindow::Draw() {
    if (ImGui::BeginTable("Network settings", 2)) {
        ImGui::TableSetupColumn("Parameter", ImGuiTableColumnFlags_WidthFixed, 150);
        ImGui::TableSetupColumn("Value");

        ImGui::TableNextColumn();
        ImGui::Text("IP-адрес аппарата");
        ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
        ImGui::InputText("##1", robotIP_.data(), 16);

        ImGui::EndTable();
    }
    if (ImGui::Button("Подключение", ImVec2(ImGui::GetContentRegionAvail().x, 32))) {
        /// ToDo: место для магии PolarStarWalker'а
    }
}
