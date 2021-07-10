#include "Lib.hpp"

namespace lib {
    void Setup() {
        SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
        lib::logger::Setup();
        InitGstreamer();
    }
}