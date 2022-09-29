#ifndef CLIENT_GSTREAMER_HPP
#define CLIENT_GSTREAMER_HPP

#include <gst/gstelement.h>
#include <gst/gstpad.h>

#include <QImage>
#include <mutex>
#include <chrono>

class Gstreamer {
private:
    GstElement *src;
    GstElement *gdpdepay;
    GstElement *rtp;
    GstElement *h264parse;
    GstElement *decode;
    GstElement *videoconvert;
    GstElement *sink;
    GstElement *group;
    std::chrono::steady_clock::time_point time{};

    std::mutex qImageMutex_;

    QImage frame;

public:
    Gstreamer();

    ~Gstreamer();

    void Setup();

    operator bool();

    QImage GetFrame();

    bool SetStatePlaying();
};

extern "C" {
void InitGstreamer();
}

#endif
