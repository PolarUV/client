#ifndef CLIENT_CONTROLSETTINGSWIDGET_HPP
#define CLIENT_CONTROLSETTINGSWIDGET_HPP

#include "Renderer/API/IWidget.hpp"

#include <imgui.h>

#include <array>

class ControlSettingsWidget final : public IWidget<ControlSettingsWidget> {
public:
    ControlSettingsWidget();
    ~ControlSettingsWidget();
    void DrawImpl();

private:
    int gamepadId_ = 0;
};

#endif  // CLIENT_CONTROLSETTINGSWIDGET_HPP
