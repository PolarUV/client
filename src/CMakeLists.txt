cmake_minimum_required(VERSION 3.16)

if (CMAKE_BUILD_TYPE MATCHES "Release")
    add_executable(Client WIN32 Startup.cpp)
else ()
    add_executable(Client Startup.cpp)
endif ()

include_directories(Client PUBLIC ./)

#add_subdirectory(Lib)
add_subdirectory(Renderer)
add_subdirectory(Resources)
add_subdirectory(App)

target_link_libraries(Client App)
#target_link_libraries(Client Lib)

target_link_libraries(Client Renderer)
