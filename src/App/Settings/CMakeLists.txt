project(Settings)

add_subdirectory(Control)
add_subdirectory(Movement)
add_subdirectory(Camera)

add_library(Settings SettingsWindow.hpp SettingsWindow.cpp)

target_link_libraries(Settings Control)
target_link_libraries(Settings Movement)
target_link_libraries(Settings Camera)
