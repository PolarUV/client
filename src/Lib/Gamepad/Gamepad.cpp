#include "API/Gamepad.hpp"

#include "Logger/Logger.hpp"

#include <GLFW/glfw3.h>

#include <boost/container/flat_set.hpp>

#include <algorithm>
#include <string_view>

namespace {

inline double GasFunction(double X) {
    if (X > 0) {
        return 0.398522 * X - 0.22634 * X * X + 0.819158 * X * X * X;
    }

    return 0.398522 * X + 0.22634 * X * X + 0.819158 * X * X * X;
}

}  // namespace

enum AxisMap { LX = 0, LY, RX, L2, R2, RY };
enum ButtonsMap {};

std::vector<int> &Gamepad::ActiveIds() {
    static std::vector<int> ids;
    return ids;
}

bool Gamepad::DoesGamepadAllowed(int gamepadId) {
    // you can find gamepads GUIDs and input map in
    // https://github.com/glfw/glfw/blob/master/src/mappings.h
    static const boost::container::flat_set<std::string_view> allowedGamepads{
        "030000004c050000e60c000000000000",  // Windows PS5 (DualSense)
        "030000004c050000cc09000000000000",  // Windows PS4 (DualShock 4)
        "030000004c050000c405000000000000",  // Windows PS4 (DualShock 4)
        "030000004c050000a00b000000000000"   // Windows PS4 (DualShock 4)
    };

    const std::string_view gamepadUuid = glfwGetJoystickGUID(gamepadId);

    const bool result = allowedGamepads.contains(gamepadUuid);

    if (!result) {
        PolarProfile << "This gamepad isn't allowed, gamepad GUID: " << gamepadUuid;
    }

    return result;
}

void Gamepad::AddGamepadCallback(int gamepadId, int event) {
    if (event == GLFW_CONNECTED) {
        if (!DoesGamepadAllowed(gamepadId)) {
            return;
        }

        ActiveIds().push_back(gamepadId);

        int buttonsCount;
        glfwGetJoystickButtons(gamepadId, &buttonsCount);

        int hatsCount;
        glfwGetJoystickHats(gamepadId, &hatsCount);

        PolarProfile << "Gamepad connected: " << gamepadId << ", buttons count: " << buttonsCount << ", hats count"
                     << hatsCount;

    } else if (event == GLFW_DISCONNECTED) {
        auto &activeIds = ActiveIds();
        const auto newActiveIdsBegin = std::remove(activeIds.begin(), activeIds.end(), gamepadId);
        if (newActiveIdsBegin == activeIds.end()) {
            return;
        }

        activeIds.erase(newActiveIdsBegin, activeIds.end());
        PolarProfile << "Gamepad disconnected: " << gamepadId;
    }
}

std::string Gamepad::GetActiveGamepads() {
    std::string gamepadsStr;
    for (auto activeId : ActiveIds()) {
        gamepadsStr += glfwGetJoystickName(activeId);
        gamepadsStr += ": ";
        gamepadsStr += std::to_string(activeId);
        gamepadsStr += '\0';
    }
    gamepadsStr.resize(gamepadsStr.size());

    return gamepadsStr;
}

void Gamepad::InitGamepads() {
    auto &activeIds = ActiveIds();

    for (int id = 0; id <= GLFW_JOYSTICK_LAST; ++id) {
        if (glfwJoystickPresent(id) == 0) {
            continue;
        }

        if (DoesGamepadAllowed(id)) {
            activeIds.push_back(id);
        }
    }
}
Gamepad::Gamepad(int gamepadId) : axes_(), buttons_() {
    if (glfwJoystickPresent(gamepadId) == 0) {
        return;
    }

    int axesCount;
    const auto *axes = glfwGetJoystickAxes(gamepadId, &axesCount);
    std::copy_n(axes, axesCount, axes_.begin());
    if (axesCount > buttons_.size()) {
        throw std::runtime_error("Read axes more then axes array");
    }

    int buttonsCount;
    const auto *buttons = glfwGetJoystickButtons(gamepadId, &buttonsCount);

    if (buttonsCount > buttons_.size()) {
        throw std::runtime_error("Read buttons more then buttons array");
    }

    std::copy_n(buttons, buttonsCount, buttons_.begin());

    // int hatsCount;
    // const auto *hats = glfwGetJoystickHats(gamepadId, &hatsCount);
}
