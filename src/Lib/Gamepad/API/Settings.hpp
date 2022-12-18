#ifndef CLIENT_SETTINGS_HPP
#define CLIENT_SETTINGS_HPP

namespace Gamepad {
    enum Axis : size_t {
        Fx = 0,
        Fy,
        Fz,
        Mx,
        My,
        Mz,
        Max
    };

    struct Settings {
        int GamepadId;

        std::array<int, Axis::Max> AxisKeys;
        std::array<bool, Axis::Max> AxisInverted;

        int OpenGripperKeyID;
        int CloseGripperKeyID;
        int TurnCameraUpKeyID;
        int TurnCameraDownKeyID;
        int ResetCameraRotationKeyID;
        int IncreaseLightBrightnessKeyID;
        int DecreaseLightBrightnessKeyID;
        int SwitchStabilizationKeyID;

        static Settings &get() {
            static Settings settings;
            return settings;
        }

    private:
        Settings() = default;
    };
} // Gamepad

#endif //CLIENT_SETTINGS_HPP
