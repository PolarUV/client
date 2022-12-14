#ifndef CLIENT_NETWORKWINDOW_HPP
#define CLIENT_NETWORKWINDOW_HPP

#include "Renderer/API/IWidget.hpp"

#include <imgui.h>

#include <string>

class NetworkSettingsWidget final : public IWidget<NetworkSettingsWidget> {
public:
    NetworkSettingsWidget();

    void DrawImpl();

private:
    std::string robotIP_;
};

#endif  // CLIENT_NETWORKWINDOW_HPP
