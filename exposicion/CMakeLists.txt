# ---------------------------------------------------------------------------
# Ejemplos de la exposicion: paso de argumentos y arreglos
#
# Cada archivo de exposicion/src/ se compila como un ejecutable independiente
# con el prefijo exp_. Hereda de proyecto_opciones los avisos (-Wall -Wextra
# -Wpedantic -Wshadow) y, en Debug, AddressSanitizer y UndefinedBehaviorSanitizer.
#
#   cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
#   cmake --build build
#   ./build/bin/exp_01_marco_de_pila
# ---------------------------------------------------------------------------

file(GLOB EXPO_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

foreach(src IN LISTS EXPO_SOURCES)
    get_filename_component(name ${src} NAME_WE)
    add_executable(exp_${name} ${src})
    target_link_libraries(exp_${name} PRIVATE proyecto_opciones)
endforeach()

list(LENGTH EXPO_SOURCES expo_count)
message(STATUS "Exposicion: ${expo_count} ejemplos compilados como exp_*")
