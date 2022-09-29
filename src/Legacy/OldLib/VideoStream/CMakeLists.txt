project(VideoStream)

set(GSTREAMER_LIB_PATH C:/gstreamer/1.0/mingw_x86_64/lib)
file(GLOB GSTREAMER_LIBRARIES
        ${GSTREAMER_LIB_PATH}/*.dll.a
        ${GSTREAMER_LIB_PATH}/gstreamer-1.0/*.dll
        )

set(VIDEO_LIBRARIES d3d11 dxguid dxgi Ole32 Oleaut32 Imm32 Winmm Version)

# Do some cmake-protobuf magic
find_package(Protobuf REQUIRED)

# Compile .proto files to C++ code
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS VideoStreamMessage.proto)

include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_library(VideoStream ${PROTO_SRCS} ${PROTO_HDRS} VideoStream.hpp VideoStream.cpp Gstreamer.hpp Gstreamer.cpp)

target_link_libraries(VideoStream ${CONAN_LIBS})
target_link_libraries(VideoStream ${VIDEO_LIBRARIES})
target_link_libraries(VideoStream ${REQUIRED_LIBS_QUALIFIED})
target_link_libraries(VideoStream ${GSTREAMER_LIBRARIES})
