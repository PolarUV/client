#ifndef CLIENT_LIB_HPP
#define CLIENT_LIB_HPP

#include "./Coroutines/All.hpp"
#include "./Drawer/Drawer.hpp"
#include "./Screenshotter/Screenshotter.hpp"
#include "./Singleton.hpp"
#include "Legacy/OldLib/DataStructs/DataStructs.hpp"
#include "Legacy/OldLib/Exceptions/Exceptions.hpp"
#include "Legacy/OldLib/Logger/Logger.hpp"
#include "Legacy/OldLib/Network/Network.hpp"
#include "Legacy/OldLib/VideoStream/VideoStream.hpp"

namespace lib {
    void Setup();
}

#endif