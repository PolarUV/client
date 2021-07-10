project(screenshotter)

add_library(Screenshotter Screenshotter.hpp Screenshotter.cpp)

target_link_libraries(Screenshotter ${REQUIRED_LIBS_QUALIFIED})