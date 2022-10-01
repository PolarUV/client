#include "SettingsWindow.hpp"

SettingsWindow::SettingsWindow()
    : IWindow("Настройки", true, ImGuiWindowFlags_NoCollapse),
      controlSettingsWidget_(),
      movementSettingsWidget_(),
      sectionSelectorWidth_(250.0F),
      currentSection_(SettingsSection::Control) {}

void SettingsWindow::Draw() {
    ImGui::BeginGroup();

    ImGui::BeginChild("Settings section selector", ImVec2(sectionSelectorWidth_, -ImGui::GetFrameHeightWithSpacing()),
                      true);
    {
        ImGui::TextDisabled("Подводный аппарат");

        ImGui::Indent();
        if (ImGui::Selectable("Управление", currentSection_ == SettingsSection::Control)) {
            currentSection_ = SettingsSection::Control;
        }
        if (ImGui::Selectable("Движение", currentSection_ == SettingsSection::Movement)) {
            currentSection_ = SettingsSection::Movement;
        }
        if (ImGui::Selectable("Камера", currentSection_ == SettingsSection::Camera)) {
            currentSection_ = SettingsSection::Camera;
        }
        if (ImGui::Selectable("Датчики", currentSection_ == SettingsSection::Sensors)) {
            currentSection_ = SettingsSection::Sensors;
        }
        ImGui::Unindent();

        ImGui::TextDisabled("Программа");

        ImGui::Indent();
        if (ImGui::Selectable("Система", currentSection_ == SettingsSection::System)) {
            currentSection_ = SettingsSection::System;
        }
        if (ImGui::Selectable("Внешний вид", currentSection_ == SettingsSection::Appearance)) {
            currentSection_ = SettingsSection::Appearance;
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
        default: {
        }
    }

    ImGui::EndChild();
}
