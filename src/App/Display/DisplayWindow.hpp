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
    float imageAspectRatio_ = 16.0F/9.0F;
    float imageWidth_ = 0.0F;
    float imageHeight_ = 0.0F;
};

#endif  // CLIENT_DISPLAYWINDOW_HPP
