#ifndef CLIENT_DISPLAYWINDOW_HPP
#define CLIENT_DISPLAYWINDOW_HPP

#include "Renderer/API/IWindow.hpp"

class DisplayWindow final : public IWindow {
   public:
    DisplayWindow();
    ~DisplayWindow() final = default;
    void Draw() final;

   private:
    const ImTextureID background_texture_;
};

#endif  // CLIENT_DISPLAYWINDOW_HPP
