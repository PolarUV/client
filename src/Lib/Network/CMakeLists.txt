Project(NetworkLib)

file(GLOB NetworkSrc *.cpp)

add_library(NetworkLib ${NetworkSrc})

target_link_libraries(NetworkLib ${CONAN_LIBS})

if(MINGW)
    target_link_libraries(NetworkLib ws2_32)
endif()
