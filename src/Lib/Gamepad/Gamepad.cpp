#include "API/Gamepad.hpp"

#include "Logger/Logger.hpp"

#include <GLFW/glfw3.h>

#include <boost/container/flat_set.hpp>

#include <algorithm>
#include <string_view>

namespace {
    // [ToDo] use array and polymorphic vector
    std::vector<int> &ActiveIds() {
        static std::vector<int> ids;
        return ids;
    }

    bool DoesGamepadAllowed(int gamepadId) {
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

    float GasFunction(double val, const std::vector<double> &coefficients) {
        double out = 0.0;

        if (val > 0) {
            for (size_t i = 0; i < coefficients.size(); ++i) {
                const auto coefficient = i % 2 == 1 ? coefficients[i] : -coefficients[i];
                out += coefficient * std::pow(val, i + 1);
            }
            return static_cast<float>(out);
        }

        for (size_t i = 0; i < coefficients.size(); ++i) {
            out += coefficients[i] * std::pow(val, i + 1);
        }
        return static_cast<float>(out);
    }

    template<typename T, size_t Size, typename Func>
    auto GetData(Func func, int id) {
        int count;
        const auto *axes = func(id, &count);

        std::array<T, Size> array{};

        if (count > array.size()) [[unlikely]] {
            throw std::runtime_error("Read count more then array");
        }

        std::copy_n(axes, count, array.begin());

        return array;
    }
} // namespace

const std::vector<int> &Gamepad::GetActiveIds() {
    return ActiveIds();
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
    for (auto activeId: ActiveIds()) {
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

enum AxisMap : size_t {
    LX = 0, LY, RX, L2, R2, RY, Max
};

enum ButtonsMap {
};

Gamepad::Commands Gamepad::GetCommands(int gamepadId, [[maybe_unused]] const Gamepad::Settings &settings) {
    using MoveEnum = Gamepad::Commands::MoveEnum;
    using GripperEnum = Gamepad::Commands::GripperEnum;

    static const std::vector<double> coefficients{0.398522, 0.22634, 0.819158};

    Gamepad::Commands commands{};

    if (glfwJoystickPresent(gamepadId) == 0) {
        return commands;
    }

    const auto axes = GetData<float, AxisMap::Max>(glfwGetJoystickAxes, gamepadId);

    [[maybe_unused]] const auto Buttons = GetData<bool, 19>(glfwGetJoystickButtons, gamepadId);

    const auto Hats = GetData<char, 1>(glfwGetJoystickHats, gamepadId);

    commands.Move[MoveEnum::Fx] = GasFunction(axes[AxisMap::RY], coefficients);
    commands.Move[MoveEnum::Fy] = GasFunction(axes[AxisMap::LX], coefficients);
    commands.Move[MoveEnum::Fz] = GasFunction(axes[AxisMap::LY], coefficients);
    commands.Move[MoveEnum::Mx] = GasFunction(axes[AxisMap::L2], coefficients);
    commands.Move[MoveEnum::My] = GasFunction(axes[AxisMap::R2], coefficients);
    commands.Move[MoveEnum::Mz] = GasFunction(axes[AxisMap::RX], coefficients);

    //ToDo do it clearly
    if (Hats[0] & GLFW_HAT_UP) {
        commands.Gripper[GripperEnum::Gripper1] = 1;
    } else if (Hats[0] & GLFW_HAT_DOWN) {
        commands.Gripper[GripperEnum::Gripper1] = -1;
    }

    if (Hats[0] & GLFW_HAT_LEFT) {
        commands.Gripper[GripperEnum::Gripper2] = 1;
    } else if (Hats[0] & GLFW_HAT_RIGHT) {
        commands.Gripper[GripperEnum::Gripper2] = -1;
    }


    return commands;
}

