cmake_minimum_required(VERSION 3.16)
project(OpenGL)

set(CMAKE_CXX_STANDARD 20)

add_compile_definitions(GLEW_STATIC)
include_directories(dependencies/GLFW/include)
include_directories(dependencies/glew-2.1.0/include)
include_directories(src/vendor)
link_directories(dependencies/GLFW/lib-vc2019)
link_directories(dependencies/glew-2.1.0/lib/Release/Win32/)

file(GLOB OpenGLSRC "src/*.cpp" "src/*.h" "src/vendor/**/*")
add_executable(OpenGL ${OpenGLSRC})
target_link_libraries(OpenGL glew32s.lib glfw3.dll opengl32.lib)