project(MoveSettings)

#do some cmake-protobug magic
find_package(Protobuf REQUIRED)

#compile .proto to c++ code
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS MoveSettingsMessage.proto)

include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_library(MoveSettings ${PROTO_SRCS} ${PROTO_HDRS} MoveSettingsWidget.hpp MoveSettingsWidget.cpp MoveSettingsWidgetActions.cpp)

target_link_libraries(MoveSettings ${REQUIRED_LIBS_QUALIFIED})