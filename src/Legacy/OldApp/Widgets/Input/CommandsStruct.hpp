#ifndef CLIENT_COMMANDSSTRUCT_HPP
#define CLIENT_COMMANDSSTRUCT_HPP

#include <DataStructs/StaticMap.hpp>

struct CommandsStruct {
    enum class MoveEnum : size_t {
        Fx = 0,
        Fy = 1,
        Fz = 2,
        Mx = 3,
        My = 4,
        Mz = 5
    };

    enum class HandEnum : size_t {
        Hand1,
        Hand2,
        Hand3,
        Hand4,
        Hand5,
        Hand6,
    };

//    enum StabilizationType : int8_t {
//        None = 0,
//        Rotation = 1,
//        Absolute = 2
//    };

    using MoveArray_t = lib::StaticMap<MoveEnum, float, 6>;
    using HandArray_t = lib::StaticMap<HandEnum, float, 6>;

    MoveArray_t Move{};
    HandArray_t Hand{};
    std::array<float, 4> LowPWM{};

    /// Стабилизация
    //StabilizationType Stabilization = None;
    bool Stabilization = false;
    std::array<float, 4> StabilizationTarget{};

    friend std::ostream &operator<<(std::ostream &out, const CommandsStruct &commands) {
        out << "[COMMANDS STRUCT]\n"
            << "Move: "
            << commands.Move[MoveEnum::Fx] << ", "
            << commands.Move[MoveEnum::Fy] << ", "
            << commands.Move[MoveEnum::Fz] << ", "
            << commands.Move[MoveEnum::Mx] << ", "
            << commands.Move[MoveEnum::My] << ", "
            << commands.Move[MoveEnum::Mz] << '\n'

            << "Hand: "
            << commands.Hand[HandEnum::Hand1] << ", "
            << commands.Hand[HandEnum::Hand2] << ", "
            << commands.Hand[HandEnum::Hand3] << ", "
            << commands.Hand[HandEnum::Hand4] << ", "
            << commands.Hand[HandEnum::Hand5] << ", "
            << commands.Hand[HandEnum::Hand6] << '\n'

            << "LowPWM: "
            << commands.LowPWM[0] << ", "
            << commands.LowPWM[1] << ", "
            << commands.LowPWM[2] << ", "
            << commands.LowPWM[3];

        return out;
    }

};

#endif
