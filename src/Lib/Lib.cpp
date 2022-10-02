#include "Gamepad/API/Gamepad.hpp"

#include <GLFW/glfw3.h>

int Lib() {
    glfwInit();

    glfwSetJoystickCallback(Gamepad::AddGamepadCallback);
    Gamepad::InitGamepads();

    return 0;
}
