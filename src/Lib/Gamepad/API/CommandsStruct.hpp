#ifndef LIB_COMMANDSSTRUCT_HPP
#define LIB_COMMANDSSTRUCT_HPP

#include <array>
#include <iostream>

struct CommandsStruct {
    enum MoveEnum : size_t { Fx = 0, Fy = 1, Fz = 2, Mx = 3, My = 4, Mz = 5 };

    enum GripperEnum : size_t {
        Gripper1,
        Gripper2,
        Gripper3,
        Gripper4,
        Gripper5,
        Gripper6,
    };

    //    enum StabilizationType : int8_t {
    //        None = 0,
    //        Rotation = 1,
    //        Absolute = 2
    //    };

    std::array<float, 6> Move{};
    std::array<float, 6> Gripper{};
    std::array<float, 4> LowPWM{};

    /// Стабилизация
    // StabilizationType Stabilization = None;
    bool Stabilization = false;
    std::array<float, 4> StabilizationTarget{};

    friend std::ostream &operator<<(std::ostream &out, const CommandsStruct &commands) {
        out << "[COMMANDS STRUCT]\n"
            << "Move: " << commands.Move[MoveEnum::Fx] << ", " << commands.Move[MoveEnum::Fy] << ", "
            << commands.Move[MoveEnum::Fz] << ", " << commands.Move[MoveEnum::Mx] << ", " << commands.Move[MoveEnum::My]
            << ", " << commands.Move[MoveEnum::Mz] << '\n'

            << "Gripper1: " << commands.Gripper[GripperEnum::Gripper1] << ", "
            << commands.Gripper[GripperEnum::Gripper2] << ", " << commands.Gripper[GripperEnum::Gripper3] << ", "
            << commands.Gripper[GripperEnum::Gripper4] << ", " << commands.Gripper[GripperEnum::Gripper5] << ", "
            << commands.Gripper[GripperEnum::Gripper6] << '\n'

            << "LowPWM: " << commands.LowPWM[0] << ", " << commands.LowPWM[1] << ", " << commands.LowPWM[2] << ", "
            << commands.LowPWM[3];

        return out;
    }
};

#endif
