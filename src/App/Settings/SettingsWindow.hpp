#ifndef CLIENT_SETTINGSWINDOW_HPP
#define CLIENT_SETTINGSWINDOW_HPP

#include "App/Settings/Camera/CameraSettingsWidget.hpp"
#include "App/Settings/Control/ControlSettingsWidget.hpp"
#include "App/Settings/Movement/MovementSettingsWidget.hpp"

#include "Renderer/API/IWindow.hpp"

#include <imgui.h>

#include <memory>

namespace App {

enum SettingsSection { Control, Movement, Camera, Sensors, System, Appearance };

class SettingsWindow final : public IWindow {
   public:
    SettingsWindow();
    ~SettingsWindow() final;

    void Draw(bool* opened) final;

   private:
    float sectionSelectorWidth_;
    SettingsSection currentSection_;

    std::unique_ptr<App::ControlSettingsWidget> controlSettingsWidget_;
    std::unique_ptr<App::MovementSettingsWidget> movementSettingsWidget_;
};

}  // namespace App

#endif  // CLIENT_SETTINGSWINDOW_HPP
