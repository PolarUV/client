project(Exceptions)

add_library(Exceptions Exceptions.hpp ExceptionHandler.cpp)
target_link_libraries(Exceptions ${REQUIRED_LIBS_QUALIFIED})
