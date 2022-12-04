#include "CameraSettingsWidget.hpp"

CameraSettingsWidget::CameraSettingsWidget()
    : clientAddress_("XXX.XXX.XXX.XXX"), deviceName_("/dev/videoXX"), clientAddressID_(0), deviceNameID_(0) {}

void CameraSettingsWidget::Draw() {
    const float itemSpacingX = ImGui::GetStyle().ItemSpacing.x;
    const float availableSpace = ImGui::GetContentRegionAvail().x;
    const float firstColumnWidth = (availableSpace <= 400) ? ((availableSpace - itemSpacingX) * 0.5F) : 200.0F;

    if (ImGui::BeginTable("Camera settings table", 2)) {
        ImGui::TableSetupColumn("Label", ImGuiTableColumnFlags_WidthFixed, firstColumnWidth);
        ImGui::TableSetupColumn("Input");

        ImGui::TableNextColumn();
        ImGui::Text("IP-адрес компьютера");
        ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
        ImGui::Combo("##1", &clientAddressID_, clientAddresses_.data(), (int)clientAddresses_.size());

        ImGui::TableNextRow();

        ImGui::TableNextColumn();
        ImGui::Text("Имя устройства");
        ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
        ImGui::Combo("##2", &deviceNameID_, deviceNames_.data(), (int)deviceNames_.size());

        ImGui::EndTable();
    }
}
