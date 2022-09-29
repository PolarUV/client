project(Authorization)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_library(Authorization AuthorizationWidget.hpp AuthorizationWidget.cpp ../CameraSettings/IPFunction.hpp)

target_link_libraries(Authorization ${REQUIRED_LIBS_QUALIFIED})

if (WIN32)
    #do something
endif (WIN32)