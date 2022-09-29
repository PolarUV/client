add_executable(Client Startup.cpp)

include_directories(Client PUBLIC ./)

add_subdirectory(Renderer)
add_subdirectory(Resources)
add_subdirectory(App)

target_link_libraries(Client App)

target_link_libraries(Client Renderer)
