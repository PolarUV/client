#ifndef CLIENT_SETTINGSWINDOW_HPP
#define CLIENT_SETTINGSWINDOW_HPP

#include "App/Settings/Camera/CameraSettingsWidget.hpp"
#include "App/Settings/Control/ControlSettingsWidget.hpp"
#include "App/Settings/Movement/MovementSettingsWidget.hpp"

#include "Renderer/API/IWindow.hpp"

#include <imgui.h>

#include <memory>

namespace App {

enum SettingsSection : uint8_t { Control, Movement, Camera, Sensors, System, Appearance };

class SettingsWindow final : public IWindow {
   public:
    SettingsWindow();
    ~SettingsWindow() final = default;

    void Draw() final;

   private:
    App::ControlSettingsWidget controlSettingsWidget_;
    App::MovementSettingsWidget movementSettingsWidget_;
    float sectionSelectorWidth_;
    SettingsSection currentSection_;
};

}  // namespace App

#endif  // CLIENT_SETTINGSWINDOW_HPP
