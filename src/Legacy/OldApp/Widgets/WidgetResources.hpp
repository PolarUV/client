#ifndef CLIENT_WIDGETRESOURCES_HPP
#define CLIENT_WIDGETRESOURCES_HPP

#define WIN32_LEAN_AND_MEAN

#include <QOpenGLFramebufferObject>
#include <QImage>

#include <Network/Network.hpp>
#include <VideoStream/VideoStream.hpp>

#include <string>

struct SensorsStruct {

    enum Position {
        X = 0,
        Y = 1,
        Z = 2,
        W = 3
    };

    std::array<float, 4> Rotation{};

    std::array<float, 3> Acceleration{};

    float Depth = 0.0f;

    float Pressure = 0.0f;

    float BatteryVoltage = 0.0f;

    std::array<int8_t, 4> MotionCalibration {};

    bool Euler = true;
};

/// ToDo: что-то с этим сделать
struct SensorsSettingsStruct {
    float OrientationOffsetZ = 0.0f;
    float DepthOffset = 0.0f;
    int MaxDepth = 5;
    bool IndicatorsEnabled = true;
};


struct WidgetResources {

    SensorsStruct Sensors{};
    SensorsSettingsStruct SensorsSettings{};

    bool StabilizationState = false;
    std::array<float, 4> StabilizationTarget{};

    lib::processing::CameraSettingsStruct CameraSettings{};

    lib::network::Network Network{};
    std::string ClientIp{};
    int GamepadId{};

};




#endif