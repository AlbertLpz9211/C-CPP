// ===========================================================================
// 09 - Referencias colgantes: el precio de no copiar
// Bloque 5 (20 min) - const, punteros vs referencias
//
// ATENCION: ESTE PROGRAMA ESTA ESCRITO PARA FALLAR.
//   Ejecutalo asi para que AddressSanitizer detecte el error de la ultima
//   seccion y detenga el programa (esa parada es el resultado esperado):
//
//     ASAN_OPTIONS=detect_stack_use_after_return=1 ./build/bin/exp_09_referencias_colgantes
//
//   Informe esperado:
//     ERROR: AddressSanitizer: stack-use-after-return on address 0x...
//     SUMMARY: AddressSanitizer: stack-use-after-return en 09_referencias_colgantes.cpp
//
//   Sin esa variable de entorno el programa NO se detiene: imprime un valor
//   basura y termina normalmente. Ese es justamente el peligro del
//   comportamiento indefinido, y merece la pena enseñar las dos ejecuciones.
//
// OBJETIVO
//   Una referencia no es dueña del objeto al que apunta. Si el objeto muere
//   antes que la referencia, queda una referencia COLGANTE (dangling) y
//   usarla es comportamiento indefinido: puede imprimir basura, funcionar por
//   casualidad o abortar el programa.
//
// LAS DOS CAUSAS MAS COMUNES
//   A. Devolver una referencia a una variable local.
//   B. Guardar una referencia (o puntero, o iterador) a un elemento de un
//      contenedor que despues crece y reubica su memoria.
// ===========================================================================

#include <iostream>
#include <vector>

// --- Causa A ---------------------------------------------------------------
// El compilador AVISA de este error. El pragma silencia el aviso solo para
// poder ejecutar la demostracion; comentalo en clase para ver el diagnostico:
//   warning: reference to stack memory associated with local variable 'local' returned
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreturn-stack-address"
#endif
int& referencia_colgante() {
    int local = 1234;  // muere al terminar la funcion
    return local;      // devolvemos un alias de algo que ya no existira
}
#if defined(__clang__)
#pragma clang diagnostic pop
#endif

int main() {
    std::cout << "CASO B: referencia invalidada al crecer un vector\n";

    std::vector<int> datos{10, 20, 30};
    std::cout << "  capacidad inicial : " << datos.capacity() << '\n';

    int& primero = datos[0];  // alias del primer elemento
    std::cout << "  primero = " << primero << " en " << &primero << '\n';

    // Al superar la capacidad, el vector pide un bloque nuevo, copia los
    // elementos y libera el anterior. 'primero' queda apuntando al bloque viejo.
    for (int i = 0; i < 1000; ++i) {
        datos.push_back(i);
    }
    std::cout << "  capacidad final   : " << datos.capacity()
              << "  (hubo realojamiento: los elementos se movieron)\n"
              << "  datos[0] ahora vive en " << &datos[0]
              << " y 'primero' sigue apuntando a " << static_cast<const void*>(&primero) << '\n'
              << "  Leer 'primero' ahora seria comportamiento indefinido.\n\n";

    std::cout << "COMO SE EVITA\n"
              << "  - No devuelvas referencias a locales; devuelve por valor.\n"
              << "  - No guardes referencias, punteros ni iteradores a elementos de un\n"
              << "    contenedor si el contenedor puede crecer. Guarda el INDICE.\n"
              << "  - Reserva capacidad (datos.reserve(n)) si necesitas estabilidad.\n\n";

    std::cout << "CASO A: a continuacion se usa una referencia a una variable local ya\n"
              << "destruida. Con ASAN_OPTIONS=detect_stack_use_after_return=1 el\n"
              << "programa se detiene AQUI con el informe 'stack-use-after-return'.\n"
              << "-------------------------------------------------------------------\n";
    std::cout.flush();

    int& colgante = referencia_colgante();
    std::cout << "  valor leido: " << colgante << "  <-- si ves esta linea, tuviste suerte\n";

    return 0;
}
