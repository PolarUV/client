#ifndef CLIENT_GAMEPAD_HPP
#define CLIENT_GAMEPAD_HPP

#include "CommandsStruct.hpp"
#include "GamepadSettingsStruct.hpp"

#include <array>
#include <iomanip>
#include <string>
#include <vector>

struct Move {
    std::array<float, 6> Forces;
};

class Gamepad {
   private:
    static std::vector<int>& ActiveIds();

    static bool DoesGamepadAllowed(int gamepadId);

   public:
    static const std::vector<int>& GetActiveIds() { return ActiveIds(); }

    static std::string GetActiveGamepads();

    static void InitGamepads();

    static void AddGamepadCallback(int gamepadId, int event);

    explicit Gamepad(int gamepadId);

   private:
    std::array<float, 6> axes_;
    std::array<bool, 19> buttons_;

   public:
    friend std::ostream& operator<<(std::ostream& out, const Gamepad& gamepad);
};

inline std::ostream& operator<<(std::ostream& out, const Gamepad& gamepad) {
    out << "[GAMEPAD]\naxes: " << std::setprecision(5);

    for (auto axe : gamepad.axes_) {
        out << axe << '\t';
    }

    return out;
}

#endif  // CLIENT_GAMEPAD_HPP
