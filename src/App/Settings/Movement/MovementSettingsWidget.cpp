#include "MovementSettingsWidget.hpp"

#include <charconv>
#include <limits>

namespace App {

MovementSettingsWidget::MovementSettingsWidget() {
    motorsNumber_ = 8;
    maximumSpeed_ = 100;
    gripperFreedom_ = 2;
}

MovementSettingsWidget::~MovementSettingsWidget() {}

void MovementSettingsWidget::Draw() {
    {
        ImGui::Text("Настройки движителей");
        ImGui::Spacing();

        ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x * 0.5F);

        ImGui::InputInt("Количество", &motorsNumber_);

        ImGui::SliderInt("Максимальная мощность", &maximumSpeed_, 0, 100);

        ImGui::PopItemWidth();

        ImGui::Spacing();
        ImGui::Text("Коэффициенты мощности движителей");
        ImGui::Spacing();

        if (ImGui::BeginTable("Motor coefficients table", 7, ImGuiTableFlags_Borders)) {
            ImGui::TableSetupColumn("No.");
            ImGui::TableSetupColumn("Vx");
            ImGui::TableSetupColumn("Vy");
            ImGui::TableSetupColumn("Vz");
            ImGui::TableSetupColumn("Wx");
            ImGui::TableSetupColumn("Wy");
            ImGui::TableSetupColumn("Wz");
            ImGui::TableHeadersRow();
            for (int row = 0; row < motorsNumber_; row++) {
                ImGui::TableNextRow();
                for (int column = 0; column < 7; column++) {
                    ImGui::TableSetColumnIndex(column);
                    if (column == 0) {
                        ImGui::Text("%d", row + 1);
                        continue;
                    }
                    std::array<char, 20> label = {};
                    snprintf(label.begin(), label.size(), "##InputText-%d.%d", row, column);
                    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0F);
                    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0, 0, 0, 0));
                    ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
                    ImGui::InputFloat(label.data(), &motorCoefficients_[row][column - 1], 0.0F, 0.0F, "%.2F");
                    ImGui::PopStyleColor();
                    ImGui::PopStyleVar();
                }
            }
            ImGui::EndTable();
        }

        ImGui::Spacing();
        ImGui::Text("Настройки манипулятора");
        ImGui::Spacing();

        ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x * 0.5F);

        ImGui::SliderInt("Число степеней свободы", &gripperFreedom_, 1, 6);

        ImGui::Spacing();
        ImGui::Text("Коэффициенты мощности манипулятора");
        ImGui::Spacing();

        constexpr auto maxDigits = std::numeric_limits<int>::digits10 + 2;

        if (ImGui::BeginTable("Gripper coefficients table", gripperFreedom_, ImGuiTableFlags_Borders)) {
            for (int column = 0; column < gripperFreedom_; column++) {
                assert(column < maxDigits + 1);
                char column_str[maxDigits + 1]{};
                auto [end_ptr, err] = std::to_chars(column_str, column_str + maxDigits, column);
                assert(err == std::errc());
                ImGui::TableSetupColumn(column_str);
            }
            ImGui::TableHeadersRow();
            ImGui::TableNextRow();
            for (int column = 0; column < gripperFreedom_; column++) {
                ImGui::TableSetColumnIndex(column);
                ImGui::Text("0.0");
            }
            ImGui::EndTable();
        }

        ImGui::Spacing();
        ImGui::Text("Коэффициенты стабилизации");
        ImGui::Spacing();

        if (ImGui::BeginTable("Stabilization coefficients table", 5, ImGuiTableFlags_Borders)) {
            ImGui::TableSetupColumn("Ось");
            ImGui::TableSetupColumn("П");
            ImGui::TableSetupColumn("И");
            ImGui::TableSetupColumn("Д");
            ImGui::TableSetupColumn("Включен");
            ImGui::TableHeadersRow();
            for (int row = 0; row < 4; row++) {
                ImGui::TableNextRow();
                for (int column = 0; column < 4; column++) {
                    ImGui::TableSetColumnIndex(column);
                    if (column == 0) {
                        switch (row) {
                            case 0:
                                ImGui::Text("X");
                                break;
                            case 1:
                                ImGui::Text("Y");
                                break;
                            case 2:
                                ImGui::Text("Z");
                                break;
                            case 3:
                                ImGui::Text("H");
                                break;
                            default: {
                            }
                        }
                    } else {
                        ImGui::Text("0.0");
                    }
                }
            }
            ImGui::EndTable();
        }
    }
}

}  // namespace App
