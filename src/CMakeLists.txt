cmake_minimum_required(VERSION 3.16)

if (CMAKE_BUILD_TYPE MATCHES "Release")
    add_executable(Client WIN32 Startup.cpp Startup.hpp)
else()
    add_executable(Client Startup.cpp Startup.hpp)
endif()

#Qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if (WIN32)

    set(QT_INSTALL_PATH "${QT_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()

    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()

    foreach (QT_LIB ${REQUIRED_LIBS})
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt${QT_VERSION}${QT_LIB}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()

include_directories(Client PUBLIC ./Lib)
include_directories(Client PUBLIC ./Renderer/.imgui/include)

add_subdirectory(Lib)
add_subdirectory(Renderer)
add_subdirectory(Resources)
add_subdirectory(ClientApp)


target_link_libraries(Client ClientApp)
target_link_libraries(Client Lib)

target_link_libraries(Client ${CONAN_LIBS})

target_link_libraries(Client Renderer)