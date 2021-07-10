project (ClientApp)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_library(ClientApp MainWindow.cpp MainWindow.hpp Slots.cpp)
target_link_libraries(ClientApp ${REQUIRED_LIBS_QUALIFIED})

include_directories(./Widgets)

add_subdirectory(Widgets)

target_link_libraries(ClientApp Widgets)

target_link_libraries(ClientApp iphlpapi)
