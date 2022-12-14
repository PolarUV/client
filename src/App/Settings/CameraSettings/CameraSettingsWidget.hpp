#ifndef CLIENT_CAMERASETTINGSWIDGET_HPP
#define CLIENT_CAMERASETTINGSWIDGET_HPP

#include "Renderer/API/IWidget.hpp"

#include <imgui.h>

#include <array>
#include <string>

class CameraSettingsWidget final : public IWidget {
public:
    CameraSettingsWidget();

    ~CameraSettingsWidget() final = default;

    void Draw() final;

private:
    int addressID_;
    int cameraID_;
    std::array<char, 16> currentAddress_;
    std::string currentCamera_;
    std::string cameras_;
};

#endif  // CLIENT_CAMERASETTINGSWIDGET_HPP
