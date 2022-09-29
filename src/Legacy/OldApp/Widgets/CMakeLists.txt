project (Widgets)

add_subdirectory(Authorization)
add_subdirectory(MoveSettings)
add_subdirectory(Input)
add_subdirectory(PythonEnvironment)
add_subdirectory(Display)
add_subdirectory(Sensors)
add_subdirectory(SensorsSettings)
add_subdirectory(CameraSettings)

add_library(Widgets Widgets.hpp Widgets.cpp)

target_link_libraries(Widgets Authorization)
target_link_libraries(Widgets MoveSettings)
target_link_libraries(Widgets Input)
target_link_libraries(Widgets PythonEnvironment)
target_link_libraries(Widgets Display)
target_link_libraries(Widgets Sensors)
target_link_libraries(Widgets SensorsSettings)
target_link_libraries(Widgets CameraSettings)

target_link_libraries(Widgets ${REQUIRED_LIBS_QUALIFIED})