project(Sensors)

#do some cmake-protobug magic
find_package(Protobuf REQUIRED)

#compile .proto to c++ code
#protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS SensorsMessage.proto)

#include_directories(${Protobuf_INCLUDE_DIRS})
#include_directories(${CMAKE_CURRENT_BINARY_DIR})

#add_library(Sensors ${PROTO_SRCS} ${PROTO_HDRS} SensorsWidget.hpp SensorsWidget.cpp)

add_library(Sensors SensorsWidget.hpp SensorsWidget.cpp)


target_link_libraries(Sensors ${REQUIRED_LIBS_QUALIFIED})