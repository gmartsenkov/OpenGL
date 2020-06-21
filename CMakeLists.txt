cmake_minimum_required(VERSION 3.16)
project(OpenGL)

set(CMAKE_CXX_STANDARD 20)

add_compile_definitions(GLEW_STATIC)
include_directories(dependencies/GLFW/include)
include_directories(dependencies/glew-2.1.0/include)
link_directories(dependencies/GLFW/lib-vc2019)
link_directories(dependencies/glew-2.1.0/lib/Release/Win32/)

add_executable(OpenGL src/main.cpp src/Renderer.h src/Renderer.cpp)
target_link_libraries(OpenGL glew32s.lib glfw3.dll opengl32.lib)