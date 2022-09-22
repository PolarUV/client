#ifndef CLIENT_MOVEMENTSETTINGSWIDGET_HPP
#define CLIENT_MOVEMENTSETTINGSWIDGET_HPP

#include "Renderer/API/IWidget.hpp"

#include <imgui.h>

#include <array>
#include <string>

namespace App {

class MovementSettingsWidget final : public IWidget {
   public:
    MovementSettingsWidget();
    ~MovementSettingsWidget() final;

    void Draw() final;

   private:
    int motorsNumber_;
    int maximumSpeed_;
    int gripperFreedom_;
    std::array<std::array<float, 6>, 12> motorCoefficients_{};
};

}  // namespace App

#endif  // CLIENT_MOVEMENTSETTINGSWIDGET_HPP
