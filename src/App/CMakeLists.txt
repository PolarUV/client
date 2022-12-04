project(App)

add_library(App App.cpp App.hpp)

add_subdirectory(Settings)
add_subdirectory(Console)
add_subdirectory(Network)

target_link_libraries(App Settings)
target_link_libraries(App Console)
target_link_libraries(App Network)
