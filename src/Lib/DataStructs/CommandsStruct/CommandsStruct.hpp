#ifndef ROBOT_COMMANDSSTRUCT_HPP
#define ROBOT_COMMANDSSTRUCT_HPP

#include <iostream>

namespace lib {
    enum MoveVector : uint8_t {
        Fx = 0,
        Fy = 1,
        Fz = 2,
        Mx = 3,
        My = 4,
        Mz = 5
    };

    struct CommandsStruct {
        ///Array prototype
        ///{Fx, Fy, Fz, Mx, My, Mz}
        float MoveVector[6] = {};
        float TheHand[6] = {};
        float LowPWM[4] = {};
        bool MotorsLock = true;
        bool Stabilization = false;
    };
    
    constexpr size_t CommandsStructLen = sizeof(CommandsStruct);

    std::ostream &operator<<(std::ostream &ostream, const CommandsStruct &commandsStruct);

}

#endif
