#include "CameraSettingsWidget.hpp"
#include "IPFunction.hpp"

CameraSettingsWidget::CameraSettingsWidget() :
        addressID_(0),
        cameraID_(0),
        currentAddress_(AdaptersInfo().GetIp(addressID_)),
        currentCamera_("/dev/videoXX") {}

void CameraSettingsWidget::DrawImpl() {
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

        const AdaptersInfo adaptersInfo;

        const auto ips = GetIps();
        ImGui::Combo("##1", &addressID_, adaptersInfo.data());

        currentAddress_ = adaptersInfo.GetIp(addressID_);

        ImGui::TableNextRow();

        ImGui::TableNextColumn();
        ImGui::Text("Имя устройства");
        ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
        ImGui::Combo("##2", &cameraID_, cameras_.data());

        ImGui::EndTable();
    }
}
