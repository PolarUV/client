#ifndef CLIENT_NETWORKWINDOW_HPP
#define CLIENT_NETWORKWINDOW_HPP

#include "Renderer/API/IWindow.hpp"

class NetworkWindow final : public IWindow {
   public:
    NetworkWindow();
    ~NetworkWindow() final = default;
    void Draw() final;

   private:
    std::string robotIP_;
};

#endif  // CLIENT_NETWORKWINDOW_HPP
