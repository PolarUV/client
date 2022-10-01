project(App)

add_library(App App.cpp App.hpp)

include_directories(Settings)

add_subdirectory(Settings)

target_link_libraries(App Settings)
