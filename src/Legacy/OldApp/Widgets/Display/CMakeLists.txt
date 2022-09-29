project (Display)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_library(Display DisplayWidget.hpp DisplayWidget.cpp DisplayWidgetActions.cpp
        PaintYawIndicator.cpp PaintCentralIndicator.cpp PaintDepthIndicator.cpp PaintTextInfo.cpp)

target_link_libraries(Display ${REQUIRED_LIBS_QUALIFIED})