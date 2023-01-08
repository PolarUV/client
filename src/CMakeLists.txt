add_executable(Client Startup.cpp)

include_directories(Client PUBLIC ./)
include_directories(Client PUBLIC ./Lib)

add_subdirectory(Lib)
add_subdirectory(App)

target_link_libraries(Client App)
target_link_libraries(Client Lib)
