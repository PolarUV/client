project(MovementSettings)

#do some cmake-protobuf magic
find_package(Protobuf REQUIRED)

#compile .proto to c++ code
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS MovementSettingsMessage.proto)

include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_library(MovementSettings ${PROTO_SRCS} ${PROTO_HDRS} MovementSettingsWidget.hpp MovementSettingsWidget.cpp)
