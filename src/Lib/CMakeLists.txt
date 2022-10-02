project(Lib)

add_library(Lib Lib.cpp)

add_subdirectory(Renderer)
add_subdirectory(Gamepad)

target_link_libraries(Lib Renderer)
target_link_libraries(Lib Gamepad)
