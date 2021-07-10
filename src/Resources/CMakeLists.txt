project(Resources)

file(COPY Icons DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY Pipelines DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin/Media)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin/Media/Video)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/bin/Media/Image)