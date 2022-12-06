project(Display)

add_library(Display DisplayWindow.hpp DisplayWindow.cpp)

find_package(OpenGL)
target_link_libraries(Display ${OPENGL_LIBRARIES})
