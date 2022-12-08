project(Lib)

add_library(Lib Lib.cpp)

add_subdirectory(Renderer)
add_subdirectory(Gamepad)
add_subdirectory(Network)

target_link_libraries(Lib Renderer)
target_link_libraries(Lib Gamepad)
target_link_libraries(Lib NetworkLib)
