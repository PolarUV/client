project (SensorsSettings)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_library(SensorsSettings SensorsSettingsWidget.hpp SensorsSettingsWidget.cpp)

target_link_libraries(SensorsSettings ${REQUIRED_LIBS_QUALIFIED})