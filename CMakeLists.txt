
if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_definitions(-D_CRT_NONSTDC_NO_DEPRECATE)
endif()

if (UNIX AND NOT APPLE)
    find_package(X11 REQUIRED)
    link_libraries(${X11_LIBRARIES})
    include_directories(${X11_INCLUDE_DIR})
endif()

if (WIN32)
    set(libs gdi32 user32 winmm opengl32)
elseif (UNIX AND NOT APPLE)
    set(libs X11 GL dl)
endif()

add_executable(tests "tests.cpp")
target_link_libraries(tests ${libs})

include_directories("include")

add_subdirectory("demos")
add_subdirectory("examples")
