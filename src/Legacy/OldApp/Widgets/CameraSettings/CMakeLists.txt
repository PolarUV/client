project (CameraSettings)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

#compile .proto to c++ code
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS VideoDevicesMessage.proto)

include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_library(CameraSettings ${PROTO_SRCS} ${PROTO_HDRS} CameraSettingsWidget.hpp CameraSettingsWidget.cpp)

target_link_libraries(CameraSettings ${REQUIRED_LIBS_QUALIFIED})