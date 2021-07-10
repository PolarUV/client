project(Input)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_library(Input GamepadSettingsWidget.hpp GamepadSettingsWidget.cpp Gamepad.cpp)

target_link_libraries(Input ${REQUIRED_LIBS_QUALIFIED})
target_link_libraries(Input XInput DSound)