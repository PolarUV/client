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

# Установка стандарта C++20
set(CMAKE_CXX_STANDARD 20)

# Установка флагов компилятора для всех конфигураций
set(CMAKE_CXX_FLAGS "-fcoroutines -march=x86-64-v2 -static")

# Установка флагов компилятора для конфигурации Release
set(BASE_WARNINGS "-Wall -Wextra -Wpedantic")
set(EXTRA_WARNINGS "-Wnon-virtual-dtor -Wduplicated-branches -Wduplicated-cond -Wfloat-equal -Wshadow=compatible-local -Wcast-qual")
set(CMAKE_CXX_FLAGS_DEBUG "-g ${BASE_WARNINGS} ${EXTRA_WARNINGS} ${ASAN_FLAGS} ${TSAN_FLAGS} ${UBSAN_FLAGS} ${LSAN_FLAGS}")

# Установка флагов компилятора для конфигурации Debug
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

if (CMAKE_BUILD_TYPE MATCHES "Debug")
    add_definitions(-DDEBUG)
    set(CMAKE_EXE_LINKER_FLAGS ${ASAN_FLAGS} ${TSAN_FLAGS} ${UBSAN_FLAGS} ${LSAN_FLAGS})
endif ()

set(CMAKE_EXE_LINKER_FLAGS)

set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")
set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK "${CMAKE_COMMAND} -E time")


if (WIN32)
    add_definitions(-DWIN32)
endif (WIN32)


# Conan
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# Подключение библиотек GStreamer
include_directories(C:/gstreamer/1.0/mingw_x86_64/include/glib-2.0)
include_directories(C:/gstreamer/1.0/mingw_x86_64/lib/glib-2.0/include)
include_directories(C:/gstreamer/1.0/mingw_x86_64/include/gstreamer-1.0)

# Подключение библиотек Python
find_package(Python3 COMPONENTS Interpreter Development)
include_directories(${Python_INCLUDE_DIRS})
include_directories(${Python3_INCLUDE_DIRS})

# Подключение библиотек Qt
message(STATUS "QT PATH IS: ${QT_PATH}\n")
set(CMAKE_PREFIX_PATH ${QT_PATH})
set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets Test Gamepad Network)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Opengl32 Qt5::Widgets Qt5::Test Qt5::Network) # Для -l библиотек
find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)

add_subdirectory(src)

target_link_libraries(${PROJECT_NAME} ${PROTOBUF_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
target_link_libraries(${PROJECT_NAME} ${Python3_LIBRARIES})
