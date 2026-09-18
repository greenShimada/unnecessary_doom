cmake_minimum_required(VERSION 3.10)
project(doom_game CXX C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra)
include_directories(include)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(SRC
    src/main.cpp
    src/shader.cpp
    src/texture.cpp
    src/game.cpp
    src/resource_manager.cpp
    src/sprite_renderer.cpp
    src/gl.c
    src/stb_image.cpp
)

add_executable(doom_game ${SRC})

target_compile_definitions(doom_game PRIVATE ROOT_DIR="${CMAKE_SOURCE_DIR}")

target_link_libraries(doom_game PRIVATE glfw OpenGL::GL dl m)
