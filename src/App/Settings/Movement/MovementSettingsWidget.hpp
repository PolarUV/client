#ifndef CLIENT_MOVEMENTSETTINGSWIDGET_HPP
#define CLIENT_MOVEMENTSETTINGSWIDGET_HPP

#include "Renderer/API/IWidget.hpp"

#include <imgui.h>

#include <array>
#include <string>

class MovementSettingsWidget final : public IWidget {
    template <size_t row, size_t column>
    using StaticMatrix = std::array<std::array<float, column>, row>;

   public:
    MovementSettingsWidget();
    ~MovementSettingsWidget() final = default;

    void Draw() final;

   private:
    int motorsNumber_;
    int maximumSpeed_;
    int gripperFreedom_;
    StaticMatrix<12, 6> motorCoefficients_{};
};

#endif  // CLIENT_MOVEMENTSETTINGSWIDGET_HPP
