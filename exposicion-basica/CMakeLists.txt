# ---------------------------------------------------------------------------
# Exposicion basica: funciones, paso de argumentos y arreglos
#
# Este directorio es autonomo: se puede configurar por si solo, sin depender
# del CMakeLists.txt de la raiz del repositorio.
#
#   cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
#   cmake --build build
#   ./build/bin/bas_01_funcion_basica
#
# Cada archivo de src/ produce un ejecutable con el prefijo bas_.
# ---------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.20)
project(exposicion_basica LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Tipo de build" FORCE)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

option(ENABLE_SANITIZERS "Activar AddressSanitizer y UBSan en builds Debug" ON)

add_library(opciones_basicas INTERFACE)
target_compile_options(opciones_basicas INTERFACE -Wall -Wextra -Wpedantic -Wshadow)

if(ENABLE_SANITIZERS)
    target_compile_options(opciones_basicas INTERFACE
        $<$<CONFIG:Debug>:-fsanitize=address,undefined -fno-omit-frame-pointer>)
    target_link_options(opciones_basicas INTERFACE
        $<$<CONFIG:Debug>:-fsanitize=address,undefined>)
endif()

file(GLOB FUENTES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

foreach(src IN LISTS FUENTES)
    get_filename_component(name ${src} NAME_WE)
    add_executable(bas_${name} ${src})
    target_link_libraries(bas_${name} PRIVATE opciones_basicas)
endforeach()

list(LENGTH FUENTES total)
message(STATUS "Exposicion basica: ${total} ejemplos compilados como bas_*")
