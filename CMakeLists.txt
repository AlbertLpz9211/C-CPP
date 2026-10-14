cmake_minimum_required(VERSION 3.20)
project(C-CPP LANGUAGES C CXX)

# ---------------------------------------------------------------------------
# Estandares
# ---------------------------------------------------------------------------
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Necesario para que IntelliSense y clangd sepan como se compila cada archivo.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Si nadie eligio tipo de build, usamos Debug (simbolos para el depurador).
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Tipo de build" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS Debug Release RelWithDebInfo MinSizeRel)
endif()

# Todos los ejecutables en build/bin, separados de la cache de CMake.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

option(ENABLE_SANITIZERS "Activar AddressSanitizer y UBSan en builds Debug" ON)

# ---------------------------------------------------------------------------
# Opciones comunes a todos los ejecutables
# ---------------------------------------------------------------------------
add_library(proyecto_opciones INTERFACE)

target_include_directories(proyecto_opciones INTERFACE ${CMAKE_SOURCE_DIR}/include)
target_compile_options(proyecto_opciones INTERFACE -Wall -Wextra -Wpedantic -Wshadow)

if(ENABLE_SANITIZERS)
    target_compile_options(proyecto_opciones INTERFACE
        $<$<CONFIG:Debug>:-fsanitize=address,undefined -fno-omit-frame-pointer>)
    target_link_options(proyecto_opciones INTERFACE
        $<$<CONFIG:Debug>:-fsanitize=address,undefined>)
endif()

# ---------------------------------------------------------------------------
# Un ejecutable por cada archivo de src/. Al agregar un archivo nuevo basta
# con volver a configurar (CMake: Configure) para que aparezca como target.
# ---------------------------------------------------------------------------
file(GLOB C_SOURCES   CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/*.c)
file(GLOB CXX_SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/*.cpp)

foreach(src IN LISTS C_SOURCES CXX_SOURCES)
    get_filename_component(name ${src} NAME_WE)
    get_filename_component(ext  ${src} EXT)
    if(ext STREQUAL ".c")
        set(target ${name}_c)
    else()
        set(target ${name}_cpp)
    endif()
    add_executable(${target} ${src})
    target_link_libraries(${target} PRIVATE proyecto_opciones)
endforeach()

message(STATUS "Targets generados en ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

# ---------------------------------------------------------------------------
# Material de la exposicion (paso de argumentos y arreglos).
# ---------------------------------------------------------------------------
add_subdirectory(exposicion)
