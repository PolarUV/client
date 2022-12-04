#include "NetworkSettingsWidget.hpp"

NetworkSettingsWidget::NetworkSettingsWidget() : robotIP_("XXX.XXX.XXX.XXX") {}

void NetworkSettingsWidget::Draw() {
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
