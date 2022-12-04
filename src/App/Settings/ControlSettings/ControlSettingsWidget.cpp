#include "ControlSettingsWidget.hpp"

#include "Gamepad/API/Gamepad.hpp"

constexpr std::array<const char *, 7> analogControlKeys = {"Нет",
                                                           "Левый джойстик (ось X)",
                                                           "Левый джойстик (ось Y)",
                                                           "Правый джойстик (ось X)",
                                                           "Правый джойстик (ось Y)",
                                                           "Кнопки L1 и L2",
                                                           "Кнопки R1 и R2"};

constexpr std::array<const char *, 15> discreteControlKeys = {"Нет",
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

ControlSettingsWidget::ControlSettingsWidget()
    : gamepadID_(0),

      xAxisMovementKeyID_(0),
      yAxisMovementKeyID_(0),
      zAxisMovementKeyID_(0),
      xAxisRotationKeyID_(0),
      yAxisRotationKeyID_(0),
      zAxisRotationKeyID_(0),

      xAxisMovementInverted_(false),
      yAxisMovementInverted_(false),
      zAxisMovementInverted_(false),
      xAxisRotationInverted_(false),
      yAxisRotationInverted_(false),
      zAxisRotationInverted_(false),

      openGripperKeyID_(0),
      closeGripperKeyID_(0),
      turnCameraUpKeyID_(0),
      turnCameraDownKeyID_(0),
      resetCameraRotationKeyID_(0),
      increaseLightBrightnessKeyID_(0),
      decreaseLightBrightnessKeyID_(0),
      switchStabilizationKeyID_(0) {}

void ControlSettingsWidget::Draw() {
    const float itemSpacingX = ImGui::GetStyle().ItemSpacing.x;
    const float availableSpace = ImGui::GetContentRegionAvail().x;
    const float firstColumnWidth = (availableSpace <= 500) ? ((availableSpace - itemSpacingX) * 0.5F) : 250.0F;

    ImGui::TextDisabled("Настройки устройства ввода");

    if (ImGui::BeginTable("Gamepad ID table", 2)) {
        ImGui::TableSetupColumn("Label", ImGuiTableColumnFlags_WidthFixed, firstColumnWidth);
        ImGui::TableSetupColumn("Input");

        ImGui::TableNextColumn();
        ImGui::Text("ID геймпада");
        ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
        const auto activeGamepads = Gamepad::GetActiveGamepads();
        ImGui::Combo("##1", &gamepadID_, activeGamepads.data());
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

        ImGui::TableNextColumn();
        ImGui::Text("Движение по оси X");
        ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
        ImGui::Combo("##Vx-key", &xAxisMovementKeyID_, analogControlKeys.cbegin(), analogControlKeys.size());
        ImGui::TableNextColumn();
        ImGui::Checkbox("##Vx-inverted", &xAxisMovementInverted_);

        ImGui::TableNextColumn();
        ImGui::Text("Движение по оси Y");
        ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
        ImGui::Combo("##Vy-key", &yAxisMovementKeyID_, analogControlKeys.cbegin(), analogControlKeys.size());
        ImGui::TableNextColumn();
        ImGui::Checkbox("##Vy-inverted", &yAxisMovementInverted_);

        ImGui::TableNextColumn();
        ImGui::Text("Движение по оси Z");
        ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
        ImGui::Combo("##Vz-key", &zAxisMovementKeyID_, analogControlKeys.cbegin(), analogControlKeys.size());
        ImGui::TableNextColumn();
        ImGui::Checkbox("##Vz-inverted", &zAxisMovementInverted_);

        ImGui::TableNextColumn();
        ImGui::Text("Вращение вокруг оси X");
        ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
        ImGui::Combo("##Wx-key", &xAxisRotationKeyID_, analogControlKeys.cbegin(), analogControlKeys.size());
        ImGui::TableNextColumn();
        ImGui::Checkbox("##Wx-inverted", &xAxisRotationInverted_);

        ImGui::TableNextColumn();
        ImGui::Text("Вращение вокруг оси Y");
        ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
        ImGui::Combo("##Wy-key", &yAxisRotationKeyID_, analogControlKeys.cbegin(), analogControlKeys.size());
        ImGui::TableNextColumn();
        ImGui::Checkbox("##Wy-inverted", &yAxisRotationInverted_);

        ImGui::TableNextColumn();
        ImGui::Text("Вращение вокруг оси Z");
        ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
        ImGui::Combo("##Wz-key", &zAxisRotationKeyID_, analogControlKeys.cbegin(), analogControlKeys.size());
        ImGui::TableNextColumn();
        ImGui::Checkbox("##Wz-inverted", &zAxisRotationInverted_);

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
        ImGui::Combo("##Gripper+", &openGripperKeyID_, discreteControlKeys.cbegin(), discreteControlKeys.size());

        ImGui::TableNextColumn();
        ImGui::Text("Закрыть манипулятор");
        ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
        ImGui::Combo("##Gripper-", &closeGripperKeyID_, discreteControlKeys.cbegin(), discreteControlKeys.size());

        ImGui::TableNextColumn();
        ImGui::Text("Повернуть камеру вверх");
        ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
        ImGui::Combo("##Camera+", &turnCameraUpKeyID_, discreteControlKeys.cbegin(), discreteControlKeys.size());

        ImGui::TableNextColumn();
        ImGui::Text("Повернуть камеру вниз");
        ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
        ImGui::Combo("##Camera-", &turnCameraDownKeyID_, discreteControlKeys.cbegin(), discreteControlKeys.size());

        ImGui::TableNextColumn();
        ImGui::Text("Сбросить вращение камеры");
        ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
        ImGui::Combo("##Camera~", &resetCameraRotationKeyID_, discreteControlKeys.cbegin(), discreteControlKeys.size());

        ImGui::TableNextColumn();
        ImGui::Text("Увеличить яркость фонаря");
        ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
        ImGui::Combo("##Light+", &increaseLightBrightnessKeyID_, discreteControlKeys.cbegin(),
                     discreteControlKeys.size());

        ImGui::TableNextColumn();
        ImGui::Text("Уменьшить яркость фонаря");
        ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
        ImGui::Combo("##Light-", &decreaseLightBrightnessKeyID_, discreteControlKeys.cbegin(),
                     discreteControlKeys.size());

        ImGui::TableNextColumn();
        ImGui::Text("Переключить стабилизацию");
        ImGui::TableNextColumn();
        ImGui::SetNextItemWidth(ImGui::GetColumnWidth());
        ImGui::Combo("##Stabilization~", &switchStabilizationKeyID_, discreteControlKeys.cbegin(),
                     discreteControlKeys.size());

        ImGui::EndTable();
    }
}
