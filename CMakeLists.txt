cmake_minimum_required(VERSION 3.16)
project(Client)

option(CMAKE_CXX_ASAN "ADDRESS SANITIZER" OFF)
option(CMAKE_CXX_UBSAN "UNDEFINED BEHAVIOR SANITIZER" OFF)
option(CMAKE_CXX_TSAN "THREAD SANITIZER" OFF)
option(CMAKE_CXX_LSAN "LEAK SANITIZER" OFF)

set(ASAN_FLAGS "")
if(CMAKE_CXX_ASAN)
    set(ASAN_FLAGS "-fsanitize=address")
endif()

set(TSAN_FLAGS "")
if(CMAKE_CXX_TSAN)
    set(TSAN_FLAGS "-fsanitize=thread")
endif()

set(UBSAN_FLAGS "")
if(CMAKE_CXX_UBSAN)
    set(UBSAN_FLAGS "-fsanitize=undefined")
endif()

set(LSAN_FLAGS "")
if(CMAKE_CXX_LSAN)
    set(LSAN_FLAGS "-fsanitize=leak")
endif()

# set of standard
set(CMAKE_CXX_STANDARD 20)

# set flags of all types
set(CMAKE_CXX_FLAGS "-march=x86-64-v2 -static")

# Set Debug configuration
set(SAN_FLAGS "${ASAN_FLAGS} ${TSAN_FLAGS} ${UBSAN_FLAGS} ${LSAN_FLAGS}")
set(BASE_WARNINGS "-Wall -Wextra -Wpedantic")
set(BASE_DEBUG_FLAGS "-g -fno-omit-frame-pointer -fno-strict-aliasing")
set(CMAKE_CXX_FLAGS_DEBUG "${BASE_DEBUG_FLAGS} ${BASE_WARNINGS} ${SAN_FLAGS}")

# Set Release configuration
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(CMAKE_CXX_CLANG_TIDY clang-tidy)

set(CMAKE_EXE_LINKER_FLAGS "")
if (CMAKE_BUILD_TYPE MATCHES "Debug")
    add_definitions(-DDEBUG)
    set(CMAKE_EXE_LINKER_FLAGS ${ASAN_FLAGS} ${TSAN_FLAGS} ${UBSAN_FLAGS} ${LSAN_FLAGS})
endif ()

set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")
set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK "${CMAKE_COMMAND} -E time")

if (WIN32)
    add_definitions(-DWIN32)
endif (WIN32)

# Conan
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# find GStreamer
include_directories(C:/gstreamer/1.0/mingw_x86_64/include/glib-2.0)
include_directories(C:/gstreamer/1.0/mingw_x86_64/lib/glib-2.0/include)
include_directories(C:/gstreamer/1.0/mingw_x86_64/include/gstreamer-1.0)

add_subdirectory(src)
target_link_libraries(Client ${CONAN_LIBS})
