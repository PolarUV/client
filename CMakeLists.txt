cmake_minimum_required(VERSION 3.23)
project(Client)

# setup standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set flags
set(CMAKE_CXX_FLAGS_RELEASE "")
set(CMAKE_CXX_FLAGS_DEBUG "")

if (MSVC)
    include(platform/msvc.cmake)
else ()
    message(FATAL_ERROR "Unsupported platform")
endif ()

# Get compilation time
set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")
set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK "${CMAKE_COMMAND} -E time")

# Setup conan
file(COPY ./conan/conanfile.txt DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ./conan/conan.cmake DESTINATION ${CMAKE_BINARY_DIR})

include(${CMAKE_BINARY_DIR}/conan.cmake)
conan_cmake_autodetect(settings)
conan_cmake_install(PATH_OR_REFERENCE .
        BUILD outdated
        REMOTE conancenter
        SETTINGS ${settings})

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

#[ToDo: Client-12] remove includes when GStreamer migrate to conan
# find GStreamer
include_directories(C:/gstreamer/1.0/mingw_x86_64/include/glib-2.0)
include_directories(C:/gstreamer/1.0/mingw_x86_64/lib/glib-2.0/include)
include_directories(C:/gstreamer/1.0/mingw_x86_64/include/gstreamer-1.0)

option(POLARUV_SENSORS_EMULATION "Использовать эмуляцию данных с датчиков")
if (POLARUV_SENSORS_EMULATION)
    add_compile_definitions(SENSORS_EMULATION=true)
else ()
    add_compile_definitions(SENSORS_EMULATION=false)
endif ()

add_subdirectory(src)
add_subdirectory(resources)
target_link_libraries(Client ${CONAN_LIBS})
