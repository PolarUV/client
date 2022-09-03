cmake_minimum_required(VERSION 3.16)

if (CMAKE_BUILD_TYPE MATCHES "Release")
    add_executable(Client WIN32 Startup.cpp Startup.hpp)
else()
    add_executable(Client Startup.cpp Startup.hpp)
endif()

include_directories(Client PUBLIC ./)

#add_subdirectory(Lib)
add_subdirectory(Renderer)
add_subdirectory(Resources)
#add_subdirectory(ClientApp)

#target_link_libraries(Client ClientApp)
#target_link_libraries(Client Lib)


target_link_libraries(Client Renderer)
