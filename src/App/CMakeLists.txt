project(App)

add_library(App MainWindow.cpp MainWindow.hpp)

include_directories(Settings)

add_subdirectory(Settings)

target_link_libraries(App Settings)
