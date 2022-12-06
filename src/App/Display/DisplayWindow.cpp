#include "DisplayWindow.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <GL/glew.h>

#include "stb_image.h"

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
      background_texture_(LoadTextureFromFile("Icons/Background.png")) {
}

void DisplayWindow::Draw() { ImGui::Image(background_texture_, ImGui::GetContentRegionAvail()); }
