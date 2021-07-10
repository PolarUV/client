#ifndef CLIENT_SCREENSHOTTER_HPP
#define CLIENT_SCREENSHOTTER_HPP

#include <thread>

#include "ScreenShotterQueue.hpp"

class ScreenShotter {

    ScreenshotsQueue queue_;
    std::thread thread_;

    void TakeScreenshot();

public:

    ScreenShotter();
    ~ScreenShotter();

    inline void AddToQueue(QImage&& frame){
        queue_.AddFrame(std::move(frame));
    }

    inline void AddToQueue(const QImage& frame){
        queue_.AddFrame(frame);
    }

};


#endif