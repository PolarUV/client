#ifndef CLIENT_CAMERASETTINGSWIDGET_HPP
#define CLIENT_CAMERASETTINGSWIDGET_HPP

#include "Renderer/API/IWidget.hpp"

#include <imgui.h>

class CameraSettingsWidget final : public IWidget {
   public:
    CameraSettingsWidget();
    ~CameraSettingsWidget() final = default;

    void Draw() final;
};

#endif  // CLIENT_CAMERASETTINGSWIDGET_HPP
