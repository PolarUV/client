#ifndef CLIENT_CAMERASETTINGSWIDGET_HPP
#define CLIENT_CAMERASETTINGSWIDGET_HPP

#include "Renderer/API/IWidget.hpp"

#include <imgui.h>

namespace App {

class CameraSettingsWidget final : public IWidget {
   public:
    CameraSettingsWidget();
    ~CameraSettingsWidget() final;

    void Draw() final;
};

}  // namespace App

#endif  // CLIENT_CAMERASETTINGSWIDGET_HPP
