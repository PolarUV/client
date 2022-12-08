#include "ControlSettingsWidget.hpp"

#include "Gamepad/API/Gamepad.hpp"
#include "Network/API/Protocol.hpp"

#include <windows.h>
#include <winuser.h>

template<size_t size>
using StringArray = std::array<const char *, size>;

inline constexpr StringArray<7> AnalogControlKeys = {"Нет",
                                                     "Левый джойстик (ось X)",
                                                     "Левый джойстик (ось Y)",
                                                     "Правый джойстик (ось X)",
                                                     "Правый джойстик (ось Y)",
                                                     "Кнопки L1 и L2",
                                                     "Кнопки R1 и R2"};

inline constexpr StringArray<15> DiscreteControlKeys = {"Нет",
                                                        "Кнопка 'Вверх'",
                                                        "Кнопка 'Вниз'",
                                                        "Кнопка 'Влево'",
                                                        "Кнопка 'Вправо'",
                                                        "Кнопка 'Квадрат'",
                                                        "Кнопка 'Треугольник'",
                                                        "Кнопка 'Крест'",
                                                        "Кнопка 'Круг'",
                                                        "Кнопка 'Поделиться'",
                                                        "Кнопка 'Параметры'",
                                                        "Кнопка L1",
                                                        "Кнопка R1",
                                                        "Левый джойстик (нажатие)",
                                                        "Правый джойстик (нажатие)"};

static void GetInput(HWND a, UINT b, UINT_PTR c, DWORD d) {
    const auto &settings = Gamepad::Settings::get();
    [[maybe_unused]] const auto commands = Gamepad::GetCommands(settings.GamepadId, settings);

    Protocol().SendWriteRequest({reinterpret_cast<const char*>(&commands), sizeof(commands)}, 3);
}

void ControlSettingsWidget::DrawImpl() {
    using namespace Gamepad;

    const float itemSpacingX = ImGui::GetStyle().ItemSpacing.x;
    const float availableSpace = ImGui::GetContentRegionAvail().x;
    const float firstColumnWidth = (availableSpace <= 500) ? ((availableSpace - itemSpacingX) * 0.5F) : 250.0F;

    auto &settings = Settings::get();

    ImGui::TextDisabled("Настройки устройства ввода");

    if (ImGui::BeginTable("Gamepad ID table", 2)) {
        ImGui::TableSetupColumn("Label", ImGuiTableColumnFlags_WidthFixed, firstColumnWidth);
        ImGui::TableSetupColumn("Input");

        ImGui::TableNextColumn();
        ImGui::Text("ID геймпада");
        ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
        const auto activeGamepads = Gamepad::GetActiveGamepads();
        ImGui::Combo("##1", &settings.GamepadId, activeGamepads.data());
        ImGui::EndTable();
    }

    if (ImGui::BeginTable("Analog control table", 3)) {
        ImGui::TableSetupColumn("Action", ImGuiTableColumnFlags_WidthFixed, firstColumnWidth);
        ImGui::TableSetupColumn("Assigned key");
        ImGui::TableSetupColumn("Inverted", ImGuiTableColumnFlags_WidthFixed);

        ImGui::TableNextColumn();
        ImGui::TextDisabled("Действие");
        ImGui::TableNextColumn();
        ImGui::TextDisabled("Назначенная клавиша");
        ImGui::TableNextColumn();
        ImGui::Indent(5.0F);
        ImGui::TextDisabled("(?)");
        ImGui::Unindent(5.0F);

        //TODO: рефакторинг, повторения убрать в цикл
        ImGui::TableNextColumn();
        ImGui::Text("Движение по оси X");
        ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
        ImGui::Combo("##Vx-key", &settings.AxisKeys[Axis::Fx], AnalogControlKeys.data(), AnalogControlKeys.size());
        ImGui::TableNextColumn();
        ImGui::Checkbox("##Vx-inverted", &settings.AxisInverted[Axis::Fx]);

        ImGui::TableNextColumn();
        ImGui::Text("Движение по оси Y");
        ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
        ImGui::Combo("##Vy-key", &settings.AxisKeys[Axis::Fy], AnalogControlKeys.data(), AnalogControlKeys.size());
        ImGui::TableNextColumn();
        ImGui::Checkbox("##Vy-inverted", &settings.AxisInverted[Axis::Fy]);

        ImGui::TableNextColumn();
        ImGui::Text("Движение по оси Z");
        ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
        ImGui::Combo("##Vz-key", &settings.AxisKeys[Axis::Fz], AnalogControlKeys.data(), AnalogControlKeys.size());
        ImGui::TableNextColumn();
        ImGui::Checkbox("##Vz-inverted", &settings.AxisInverted[Axis::Fy]);

        ImGui::TableNextColumn();
        ImGui::Text("Вращение вокруг оси X");
        ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
        ImGui::Combo("##Wx-key", &settings.AxisKeys[Axis::Mx], AnalogControlKeys.data(), AnalogControlKeys.size());
        ImGui::TableNextColumn();
        ImGui::Checkbox("##Wx-inverted", &settings.AxisInverted[Axis::Mx]);

        ImGui::TableNextColumn();
        ImGui::Text("Вращение вокруг оси Y");
        ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
        ImGui::Combo("##Wy-key", &settings.AxisKeys[Axis::My], AnalogControlKeys.data(), AnalogControlKeys.size());
        ImGui::TableNextColumn();
        ImGui::Checkbox("##Wy-inverted", &settings.AxisInverted[Axis::My]);

        ImGui::TableNextColumn();
        ImGui::Text("Вращение вокруг оси Z");
        ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
        ImGui::Combo("##Wz-key", &settings.AxisKeys[Axis::Mz], AnalogControlKeys.data(), AnalogControlKeys.size());
        ImGui::TableNextColumn();
        ImGui::Checkbox("##Wz-inverted", &settings.AxisInverted[Axis::Mz]);

        ImGui::EndTable();
    }

    ImGui::Spacing();

    if (ImGui::BeginTable("Discrete control table", 2)) {
        ImGui::TableSetupColumn("Action", ImGuiTableColumnFlags_WidthFixed, firstColumnWidth);
        ImGui::TableSetupColumn("Assigned key");

        ImGui::TableNextColumn();
        ImGui::TextDisabled("Действие");
        ImGui::TableNextColumn();
        ImGui::TextDisabled("Назначенная клавиша");

        ImGui::TableNextColumn();
        ImGui::Text("Открыть манипулятор");
        ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
        ImGui::Combo("##Gripper+", &settings.OpenGripperKeyID, DiscreteControlKeys.data(), DiscreteControlKeys.size());

        ImGui::TableNextColumn();
        ImGui::Text("Закрыть манипулятор");
        ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
        ImGui::Combo("##Gripper-", &settings.CloseGripperKeyID, DiscreteControlKeys.data(),
                     DiscreteControlKeys.size());

        ImGui::TableNextColumn();
        ImGui::Text("Повернуть камеру вверх");
        ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
        ImGui::Combo("##Camera+", &settings.TurnCameraUpKeyID, DiscreteControlKeys.data(), DiscreteControlKeys.size());

        ImGui::TableNextColumn();
        ImGui::Text("Повернуть камеру вниз");
        ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
        ImGui::Combo("##Camera-", &settings.TurnCameraDownKeyID, DiscreteControlKeys.data(),
                     DiscreteControlKeys.size());

        ImGui::TableNextColumn();
        ImGui::Text("Сбросить вращение камеры");
        ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
        ImGui::Combo("##Camera~", &settings.ResetCameraRotationKeyID, DiscreteControlKeys.data(),
                     DiscreteControlKeys.size());

        ImGui::TableNextColumn();
        ImGui::Text("Увеличить яркость фонаря");
        ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
        ImGui::Combo("##Light+", &settings.IncreaseLightBrightnessKeyID, DiscreteControlKeys.data(),
                     DiscreteControlKeys.size());

        ImGui::TableNextColumn();
        ImGui::Text("Уменьшить яркость фонаря");
        ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
        ImGui::Combo("##Light-", &settings.DecreaseLightBrightnessKeyID, DiscreteControlKeys.data(),
                     DiscreteControlKeys.size());

        ImGui::TableNextColumn();
        ImGui::Text("Переключить стабилизацию");
        ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
        ImGui::Combo("##Stabilization~", &settings.SwitchStabilizationKeyID, DiscreteControlKeys.data(),
                     DiscreteControlKeys.size());

        ImGui::EndTable();
    }
}


//ToDo: use asio
ControlSettingsWidget::ControlSettingsWidget() {
    SetTimer(nullptr, 0, 10, GetInput);
}

ControlSettingsWidget::~ControlSettingsWidget() {
    KillTimer(0, 0);
}

