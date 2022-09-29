Project(Network)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_library(Network Network.cpp Network.hpp)

target_link_libraries(Network ${CONAN_LIBS})
target_link_libraries(Network ${REQUIRED_LIBS_QUALIFIED})

if(MINGW)
    target_link_libraries(Network ws2_32)
endif()