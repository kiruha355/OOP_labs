cmake_minimum_required(VERSION 3.20)

project(lab_3_oop LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(main_programm
    src/main.cpp
    src/phone.cpp
)
target_include_directories(main_programm PRIVATE include)

include(CTest)
if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
