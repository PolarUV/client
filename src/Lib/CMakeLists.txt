project(Lib)

add_library(Lib Lib.cpp)

add_subdirectory(Renderer)

target_link_libraries(Lib Renderer)
