#ifndef CLIENT_LIB_HPP
#define CLIENT_LIB_HPP

#include "./Network/Network.hpp"
#include "./Exceptions/Exceptions.hpp"
#include "./Coroutines/All.hpp"
#include "./Singleton.hpp"
#include "./Logger/Logger.hpp"
#include "./VideoStream/VideoStream.hpp"
#include "./DataStructs/DataStructs.hpp"
#include "./Drawer/Drawer.hpp"
#include "./Screenshotter/Screenshotter.hpp"

namespace lib {
    void Setup();
}

#endif