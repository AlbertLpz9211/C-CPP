cmake_minimum_required(VERSION 3.20)
project(C-CPP LANGUAGES C CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-Wall -Wextra -Wpedantic)

add_executable(hola_c   src/hola.c)
add_executable(hola_cpp src/hola.cpp)

foreach(t hola_c hola_cpp)
    target_include_directories(${t} PRIVATE ${CMAKE_SOURCE_DIR}/include)
endforeach()
