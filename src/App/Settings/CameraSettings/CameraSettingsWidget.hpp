#ifndef CLIENT_CAMERASETTINGSWIDGET_HPP
#define CLIENT_CAMERASETTINGSWIDGET_HPP

#include "Renderer/API/IWidget.hpp"

#include <imgui.h>

#include <string>
#include <vector>

class CameraSettingsWidget final : public IWidget {
   public:
    CameraSettingsWidget();

    ~CameraSettingsWidget() final = default;

    void Draw() final;

   private:
    std::string clientAddress_;
    std::string deviceName_;

    int clientAddressID_;
    std::vector<const char *> clientAddresses_;

    int deviceNameID_;
    std::vector<const char *> deviceNames_;
};

#endif  // CLIENT_CAMERASETTINGSWIDGET_HPP
