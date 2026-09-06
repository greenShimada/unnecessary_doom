cmake_minimum_required(VERSION 3.10)
project(doom_game CXX C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra)
include_directories(include)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

set(SRC
    src/main.cpp
    src/gl.c
)

add_executable(doom_game ${SRC})

target_link_libraries(doom_game PRIVATE glfw OpenGL::GL dl m)
