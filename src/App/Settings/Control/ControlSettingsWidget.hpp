#ifndef CLIENT_CONTROLSETTINGSWIDGET_HPP
#define CLIENT_CONTROLSETTINGSWIDGET_HPP

#include "Renderer/API/IWidget.hpp"

#include <imgui.h>

#include <array>

namespace App {

class ControlSettingsWidget final : public IWidget {
   public:
    ControlSettingsWidget();
    ~ControlSettingsWidget() final = default;

    void Draw() final;

   private:
    int xAxisMovementKeyID_;
    int yAxisMovementKeyID_;
    int zAxisMovementKeyID_;
    int xAxisRotationKeyID_;
    int yAxisRotationKeyID_;
    int zAxisRotationKeyID_;

    bool xAxisMovementInverted_;
    bool yAxisMovementInverted_;
    bool zAxisMovementInverted_;
    bool xAxisRotationInverted_;
    bool yAxisRotationInverted_;
    bool zAxisRotationInverted_;

    int openGripperKeyID_;
    int closeGripperKeyID_;
    int turnCameraUpKeyID_;
    int turnCameraDownKeyID_;
    int resetCameraRotationKeyID_;
    int increaseLightBrightnessKeyID_;
    int decreaseLightBrightnessKeyID_;
    int switchStabilizationKeyID_;
};

}  // namespace App

#endif  // CLIENT_CONTROLSETTINGSWIDGET_HPP
