#ifndef CLIENT_VIDEOSTREAM_HPP
#define CLIENT_VIDEOSTREAM_HPP

#include <thread>

#include "./Gstreamer.hpp"

namespace lib::processing {

    struct CameraSettingsStruct {
        std::string ClientIP;
        std::string DeviceName;
        int Brightness = 0;
        int Contrast = 0;
        int Hue = 0;
        int Saturation = 0;
        bool IsRotated = false;
    };

    class VideoStream {
    public:

        VideoStream();

        ~VideoStream();

        static std::string GetStartMessage(const CameraSettingsStruct &cameraSettings);

        static std::string GetStopMessage();

        QImage GetQImage() {
            std::lock_guard lock(qImageMutex_);
            return std::move(frame);
        }

        bool IsOnline() {
            return isOnline_.load();
        }

    private:
        void StartClient();

        std::thread thread_;

        std::atomic<bool> isOnline_;
        std::atomic<bool> isDone_;

        std::mutex qImageMutex_;
        QImage frame;

        Gstreamer gstreamer_;

        void SetImage(QImage&& img);
    };

}


#endif
