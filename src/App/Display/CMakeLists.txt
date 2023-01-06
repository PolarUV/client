project(Display)

add_subdirectory(OSD)

add_library(Display DisplayWindow.hpp DisplayWindow.cpp)

target_link_libraries(Display OSD)

find_package(OpenGL)
target_link_libraries(Display ${OPENGL_LIBRARIES})
