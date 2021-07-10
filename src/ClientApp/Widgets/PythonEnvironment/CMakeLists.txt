project (PythonEnvironment)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_library(PythonEnvironment PythonEnvironmentWidget.hpp PythonEnvironmentWidget.cpp)

target_link_libraries(PythonEnvironment ${REQUIRED_LIBS_QUALIFIED})