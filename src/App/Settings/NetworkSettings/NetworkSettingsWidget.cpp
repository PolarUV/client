#include "NetworkSettingsWidget.hpp"
#include "Logger/Logger.hpp"

NetworkSettingsWidget::NetworkSettingsWidget() :
        ipMask_(R"([\d]{1,3}.[\d]{1,3}.[\d]{1,3}.[\d]{1,3})"),
        robotIP_(std::to_array("XXX.XXX.XXX.XXX")) {}

void NetworkSettingsWidget::DrawImpl() {
    if (ImGui::BeginTable("Network settings", 2)) {
        ImGui::TableSetupColumn("Parameter", ImGuiTableColumnFlags_WidthFixed, 150);
        ImGui::TableSetupColumn("Value");

        ImGui::TableNextColumn();
        ImGui::Text("IP-адрес аппарата");
        ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
        ImGui::InputText("##1", robotIP_.data(), robotIP_.size());

        ImGui::EndTable();
    }
    if (ImGui::Button("Подключение", ImVec2(ImGui::GetContentRegionAvail().x, 32))) {

        if (!std::regex_match(robotIP_.data(), ipMask_)) {
            PolarWarning << "Wrong ip format: " << robotIP_.data();
            robotIP_.fill('\0');
            return;
        }

        protocol_.Connect(robotIP_);
    }
}
