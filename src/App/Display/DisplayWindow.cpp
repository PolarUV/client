#include "DisplayWindow.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <GL/glew.h>
#include <stb_image.h>

#include <stdexcept>

ImTextureID LoadTextureFromFile(const char* filename) {
    // Load from file
    int imageWidth = 0;
    int imageHeight = 0;
    unsigned char* image_data = stbi_load(filename, &imageWidth, &imageHeight, nullptr, 4);
    if (image_data == nullptr) {
        throw std::runtime_error("Error loading texture from file");
    }

    // Create a OpenGL texture identifier
    GLuint imageTexture;
    glGenTextures(1, &imageTexture);
    glBindTexture(GL_TEXTURE_2D, imageTexture);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                    GL_CLAMP_TO_EDGE);  // This is required on WebGL for non power-of-two textures
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);  // Same

    // Upload pixels into texture
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    stbi_image_free(image_data);

    const auto image_texture_aligned = static_cast<intptr_t>(imageTexture);
    return reinterpret_cast<void*>(image_texture_aligned);
}

DisplayWindow::DisplayWindow()
    : IWindow("Обзор", true, ImGuiWindowFlags_NoCollapse, ImVec2(320, 240)),
      background_texture_(LoadTextureFromFile("Icons/Background.png")) {}

void DisplayWindow::Draw() {
    if (ImGui::GetContentRegionAvail().x / ImGui::GetContentRegionAvail().y <= imageAspectRatio_) {
        imageWidth_ = ImGui::GetContentRegionAvail().x;
        imageHeight_ = imageWidth_ / imageAspectRatio_;
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + (ImGui::GetContentRegionAvail().y - imageHeight_) / 2);
    } else {
        imageHeight_ = ImGui::GetContentRegionAvail().y;
        imageWidth_ = imageHeight_ * imageAspectRatio_;
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + (ImGui::GetContentRegionAvail().x - imageWidth_) / 2);
    }
    ImGui::Image(background_texture_, ImVec2(imageWidth_, imageHeight_));

    if constexpr (SENSORS_EMULATION) { //NOLINT
        ImGui::Begin("Имитация датчиков");
        ImGui::SliderFloat("Угол крена", &sensorsData_.Roll, 0.0F, 360.0F);
        ImGui::SliderFloat("Угол дифферента", &sensorsData_.Pitch, 0.0F, 360.0F);
        ImGui::SliderFloat("Угол курса", &sensorsData_.Yaw, 0.0F, 360.0F);
        ImGui::SliderFloat("Макс. глубина", &maxDepth_, 5.0F, 30.0F, "%.0F");
        ImGui::SliderFloat("Глубина", &sensorsData_.Depth, 0.0F, 5.0F);
        ImGui::Spacing();
        ImGui::Checkbox("Стабилизация", &stabilization_);
        if (stabilization_) {
            ImGui::Spacing();
            ImGui::SliderFloat("Уставка крена", &targetRoll_, 0.0F, 360.0F);
            ImGui::SliderFloat("Уставка дифферента", &targetPitch_, 0.0F, 360.0F);
            ImGui::SliderFloat("Уставка глубины", &targetDepth_, 0.0F, 5.0F);
        }
        ImGui::End();
    }

    // Расчет масштабного коэффициента
    const float widthScale = imageWidth_ / 1920;
    const float heightScale = imageHeight_ / 1080;
    const float scalingFactor = std::min(widthScale, heightScale);

    PaintRollIndicator(scalingFactor, sensorsData_.Roll, targetRoll_, stabilization_);
    PaintPitchIndicator(scalingFactor, sensorsData_.Pitch, stabilization_, targetPitch_);
    PaintYawIndicator(scalingFactor, sensorsData_.Yaw);
    PaintDepthIndicator(scalingFactor, sensorsData_.Depth, stabilization_, targetDepth_, maxDepth_);
}
