#ifndef CLIENT_GAMEPAD_HPP
#define CLIENT_GAMEPAD_HPP

#include "Commands.hpp"
#include "Settings.hpp"

#include <array>
#include <iomanip>
#include <string>
#include <vector>

namespace Gamepad {
    const std::vector<int> &GetActiveIds();

    std::string GetActiveGamepads();

    void InitGamepads();

    void AddGamepadCallback(int gamepadId, int event);

    Commands GetCommands(int gamepadId, const Gamepad::Settings& settings);

} // Gamepad
#endif  // CLIENT_GAMEPAD_HPP
