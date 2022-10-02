#ifndef LIB_COMMANSSETTINGSSTRUCT_HPP
#define LIB_COMMANSSETTINGSSTRUCT_HPP

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

    enum class DiscreteAxisEnum : int { LeftStick, RightStick, Square, Triangle, Circle, Cross, Start, Back, NoButton };

    enum class AnalogActionEnum : size_t {
        MoveX,
        MoveY,
        MoveZ,
        RotateX,
        RotateY,
        RotateZ,
        Gripper1,
        Gripper2,
        Gripper3,
        Gripper4,
        Gripper5,
        Gripper6
    };

    enum class DiscreteActionEnum : size_t { TurnOn, TurnOff };

    struct AnalogAxis {
        AnalogAxisEnum Axis;
        bool IsInverted;
    };

    std::array<AnalogAxis, 12> AnalogActionsIds{};
    std::array<DiscreteActionEnum, 8> DiscreteActionsIds{};
};

#endif
