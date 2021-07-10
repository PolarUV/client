cmake_minimum_required(VERSION 3.16)

#set C++23
set(CMAKE_CXX_STANDARD 20)
#link C/C++ libraries statically
set(CMAKE_EXE_LINKER_FLAGS)
set(CMAKE_CXX_FLAGS "-fcoroutines -march=x86-64-v2")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra -Wpedantic -Wnon-virtual-dtor -Wduplicated-branches -Wduplicated-cond -Wfloat-equal -Wshadow=compatible-local -Wcast-qual")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -static")

set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")
set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK "${CMAKE_COMMAND} -E time")

if (CMAKE_BUILD_TYPE MATCHES "Debug")
    add_definitions(-DDEBUG)
endif ()

if (WIN32)
    add_definitions(-DWIN32)
endif (WIN32)

project(Client)

# Подключение библиотек python
find_package(Python3 COMPONENTS Interpreter Development)
include_directories(${Python_INCLUDE_DIRS})
include_directories(${Python3_INCLUDE_DIRS})

#Путь до Qt
set(QT_CMAKE_PREFIX_PATH "C:/Qt/5.15.2/mingw81_64/lib/cmake")
set(CMAKE_PREFIX_PATH ${QT_CMAKE_PREFIX_PATH})

set(QT_VERSION 5)

set(REQUIRED_LIBS Core Gui Widgets Test Gamepad Network)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Opengl32 Qt5::Widgets Qt5::Test Qt5::Network) # Для -l библиотек

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)

#conan
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_subdirectory(src)

target_link_libraries(${PROJECT_NAME} ${PROTOBUF_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
target_link_libraries(${PROJECT_NAME} ${Python3_LIBRARIES})