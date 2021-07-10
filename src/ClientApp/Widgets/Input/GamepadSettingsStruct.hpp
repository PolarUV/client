#ifndef CLIENT_COMMANSSETTINGSSTRUCT_HPP
#define CLIENT_COMMANSSETTINGSSTRUCT_HPP

#include <DataStructs/StaticMap.hpp>

struct GamepadSettingsStruct {
public:

    enum class AnalogAxisEnum : int {
        LeftStickX,
        LeftStickY,
        RightStickX,
        RightStickY,
        LeftTrigger,
        RightTrigger,
        DPadX,
        DPadY,
        NoButton
    };

    enum class DiscreteAxisEnum : int {
        LeftStick,
        RightStick,
        Square,
        Triangle,
        Circle,
        Cross,
        Start,
        Back,
        NoButton
    };

    enum class AnalogActionEnum : size_t {
        MoveX,
        MoveY,
        MoveZ,
        RotateX,
        RotateY,
        RotateZ,
        Hand1,
        Hand2,
        Hand3,
        Hand4,
        Hand5,
        Hand6
    };

    enum class DiscreteActionEnum : size_t {
        TurnOn,
        TurnOff
    };

    // Использовать примерно так:
    // ControlsSettings::Analog[AnalogAxisEnum::DPadX];
    // ControlsSettings::DiscreteActionEnum[DiscreteAxisEnum::DPadX];

    struct AnalogAxis{
        AnalogAxisEnum Axis;
        bool IsInverted;
    };

    using AnalogSettings_t = lib::StaticMap<AnalogActionEnum, AnalogAxis, 12>;
    using DiscreteSettings_t = lib::StaticMap<DiscreteActionEnum, DiscreteAxisEnum, 8>;

    AnalogSettings_t AnalogActionsIds{};
    DiscreteSettings_t DiscreteActionsIds{};
};

#endif
