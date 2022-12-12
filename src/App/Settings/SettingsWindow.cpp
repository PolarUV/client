#include "SettingsWindow.hpp"

SettingsWindow::SettingsWindow()
    : IWindow("Настройки", true, ImGuiWindowFlags_NoCollapse,ImVec2(800,800)),
      sectionSelectorWidth_(250.0F),
      currentSection_(SettingsSection::Network) {}

void SettingsWindow::Draw() {
    ImGui::BeginGroup();

    ImGui::BeginChild("Settings section selector", ImVec2(sectionSelectorWidth_, -ImGui::GetFrameHeightWithSpacing()),
                      true);
    {
        ImGui::TextDisabled("Подводный аппарат");

        ImGui::Indent();
        if (ImGui::Selectable("Подключение", currentSection_ == SettingsSection::Network)) {
            currentSection_ = SettingsSection::Network;
        }
        if (ImGui::Selectable("Движители", currentSection_ == SettingsSection::Movement)) {
            currentSection_ = SettingsSection::Movement;
        }
        if (ImGui::Selectable("Камера", currentSection_ == SettingsSection::Camera)) {
            currentSection_ = SettingsSection::Camera;
        }
        ImGui::Unindent();

        ImGui::TextDisabled("Береговая станция");

        ImGui::Indent();
        if (ImGui::Selectable("Управление", currentSection_ == SettingsSection::Control)) {
            currentSection_ = SettingsSection::Control;
        }
        ImGui::Unindent();
    }
    ImGui::EndChild();

    if (ImGui::Button("Применить", ImVec2((sectionSelectorWidth_ - 8) / 2, 0))) {
    }
    ImGui::SameLine();
    if (ImGui::Button("Отменить", ImVec2((sectionSelectorWidth_ - 8) / 2, 0))) {
    }

    ImGui::EndGroup();

    ImGui::SameLine();

    ImGui::BeginChild("Settings selector", ImVec2(0, 0), true);

    switch (currentSection_) {
        case SettingsSection::Control: {
            controlSettingsWidget_.Draw();
            break;
        }
        case SettingsSection::Movement: {
            movementSettingsWidget_.Draw();
            break;
        }
        case SettingsSection::Camera: {
            cameraSettingsWidget_.Draw();
            break;
        }
        case SettingsSection::Network: {
            networkSettingsWidget_.Draw();
            break;
        }
        default: {
        }
    }

    ImGui::EndChild();
}
