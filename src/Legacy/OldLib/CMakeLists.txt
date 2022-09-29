Project(Lib)

add_subdirectory(Exceptions)
add_subdirectory(Network)
add_subdirectory(Logger)
add_subdirectory(VideoStream)
add_subdirectory(Screenshotter)

add_library(Lib Lib.hpp Lib.cpp)

target_link_libraries(Lib Exceptions)
target_link_libraries(Lib Network)
target_link_libraries(Lib Logger)
target_link_libraries(Lib VideoStream)
target_link_libraries(Lib Screenshotter)
