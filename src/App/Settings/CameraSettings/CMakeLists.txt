project(CameraSettings)

add_library(CameraSettings CameraSettingsWidget.hpp CameraSettingsWidget.cpp)

target_link_libraries(CameraSettings PRIVATE iphlpapi)
