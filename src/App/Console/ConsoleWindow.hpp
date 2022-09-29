#ifndef CLIENT_CONSOLEWINDOW_HPP
#define CLIENT_CONSOLEWINDOW_HPP

#include "Renderer/API/IWindow.hpp"

class ConsoleWindow final : public IWindow {
    bool autoScroll_ = true;

   public:
    ConsoleWindow();
    ~ConsoleWindow() final = default;
    void Draw() final;
};

#endif  // CLIENT_CONSOLEWINDOW_HPP
