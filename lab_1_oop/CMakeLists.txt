cmake_minimum_required(VERSION 3.16)

project(cipipi LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(main_programm
    src/main.cpp
    src/array_ops.cpp
)
target_include_directories(main_programm PRIVATE include)

enable_testing()
add_subdirectory(tests)
