#ifndef CLIENT_NETWORKWINDOW_HPP
#define CLIENT_NETWORKWINDOW_HPP

#include "Renderer/API/IWidget.hpp"
#include "Network/API/Protocol.hpp"

#include <imgui.h>

#include <regex>
#include <array>

class NetworkSettingsWidget final : public IWidget<NetworkSettingsWidget> {
public:
    NetworkSettingsWidget();

    void DrawImpl();

   private:
    static constexpr size_t ipSize_ = 16;
    std::regex ipMask_;
    std::array<char, ipSize_> robotIP_;
    Protocol protocol_;
};

#endif  // CLIENT_NETWORKWINDOW_HPP
