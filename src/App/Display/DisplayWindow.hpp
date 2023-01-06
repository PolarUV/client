#ifndef CLIENT_DISPLAYWINDOW_HPP
#define CLIENT_DISPLAYWINDOW_HPP

#include "Sensors/SensorsData.hpp"

#include "Renderer/API/IWindow.hpp"

class DisplayWindow final : public IWindow {
   public:
    DisplayWindow();
    ~DisplayWindow() final = default;
    void Draw() final;

   private:
    static void PaintRollIndicator(float scalingFactor, float roll, float targetRoll, bool stabilization);
    static void PaintPitchIndicator(float scalingFactor, float pitch, bool stabilization, float targetPitch);
    static void PaintYawIndicator(float scalingFactor, float yaw);
    static void PaintDepthIndicator(float scalingFactor, float depth, bool stabilization, float targetDepth,
                                    float maxDepth);

    const ImTextureID background_texture_;

    SensorsData sensorsData_;

    /// ToDo: Перенести в структуру настроек клиента
    float maxDepth_ = 5;
    bool stabilization_ = false;
    float targetRoll_ = 180;
    float targetPitch_ = 180;
    float targetDepth_ = 0;

    float imageAspectRatio_ = 16.0F / 9.0F;
    float imageWidth_ = 0.0F;
    float imageHeight_ = 0.0F;
};

#endif  // CLIENT_DISPLAYWINDOW_HPP
