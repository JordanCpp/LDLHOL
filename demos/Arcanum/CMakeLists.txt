
file(GLOB ARCANUM_FILES "*.cpp")
add_executable(Arcanum ${ARCANUM_FILES})
target_link_libraries(Arcanum ${libs})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
