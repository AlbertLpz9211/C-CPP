// ===========================================================================
// 14 - Fuera de rango: el error mas caro de C++
// Bloque 7 (25 min) - Arreglos unidimensionales
//
// ATENCION: ESTE PROGRAMA ESTA ESCRITO PARA FALLAR AL FINAL.
//   Ejecucion normal: UndefinedBehaviorSanitizer imprime
//     runtime error: index 6 out of bounds for type 'int[5]'
//   y el programa CONTINUA (UBSan avisa pero no aborta por omision).
//
//   Ejecucion que ademas detiene el programa:
//     ASAN_OPTIONS=detect_stack_use_after_return=1 ./build/bin/exp_14_fuera_de_rango
//   Informe esperado:
//     ERROR: AddressSanitizer: stack-buffer-overflow on address 0x...
//     SUMMARY: AddressSanitizer: stack-buffer-overflow en 14_fuera_de_rango.cpp, funcion main
//
// OBJETIVO
//   Un arreglo no comprueba sus limites. v[10] en un arreglo de 5 elementos
//   compila, se ejecuta y lee o escribe memoria que no le pertenece. El
//   estandar lo llama comportamiento indefinido: el programa puede imprimir
//   basura, corromper otra variable, funcionar hoy y fallar manana.
//
// MENSAJE PARA LA AUDIENCIA
//   Este es el origen historico de una parte enorme de las vulnerabilidades
//   de seguridad (desbordamiento de bufer). No es un detalle academico.
//
// HERRAMIENTAS QUE SI AVISAN
//   1. std::array<T,N>::at(i) y std::vector<T>::at(i) lanzan std::out_of_range.
//   2. AddressSanitizer: -fsanitize=address (ya activo en Debug aqui).
//   3. Bibliotecas estandar con modo depuracion (_LIBCPP_HARDENING_MODE).
// ===========================================================================

#include <array>
#include <iostream>
#include <stdexcept>

int main(int argc, char** argv) {
    (void)argv;
    std::cout << "1) El arreglo crudo no comprueba nada\n";

    int centinela_anterior = 111;
    int v[5] = {0, 1, 2, 3, 4};
    int centinela_posterior = 222;

    std::cout << "   v = [0 1 2 3 4], centinelas: " << centinela_anterior << " y "
              << centinela_posterior << '\n'
              << "   v[4] (ultimo valido) = " << v[4] << '\n';

    // 2) La version segura: at() comprueba y lanza excepcion.
    std::cout << "\n2) std::array::at() si comprueba\n";
    std::array<int, 5> seguro{0, 1, 2, 3, 4};
    try {
        std::cout << "   seguro.at(4) = " << seguro.at(4) << '\n';
        std::cout << "   seguro.at(10) = " << seguro.at(10) << '\n';  // lanza
    } catch (const std::out_of_range& e) {
        std::cout << "   excepcion atrapada: " << e.what() << '\n';
    }
    std::cout << "   (seguro[10] SIN at() no comprobaria nada, igual que el arreglo crudo)\n";

    // 3) El bucle mal escrito: el clasico error "off by one".
    std::cout << "\n3) El error de un elemento (off by one)\n"
              << "   for (i = 0; i <= 5; ++i)  <-- 'menor o igual' recorre 6 posiciones\n"
              << "   El indice valido maximo es N-1 = 4. La condicion correcta es i < 5.\n";

    // 4) Demostracion del comportamiento indefinido. Va al final a proposito.
    std::cout << "\n4) Acceso fuera de rango. UBSan avisa aqui; con\n"
              << "   ASAN_OPTIONS=detect_stack_use_after_return=1 el programa ademas se detiene.\n"
              << "   ----------------------------------------------------------------\n";
    std::cout.flush();

    // El indice se calcula a partir de argc (vale 1 al ejecutar sin argumentos)
    // para que el compilador no pueda conocerlo. Escrito como constante literal,
    //     v[7] = 999;
    // clang si avisa: "array index 7 is past the end of the array [-Warray-bounds]".
    // Ese es justo el limite del compilador: solo detecta lo que puede calcular.
    const std::size_t indice_invalido = 5 + static_cast<std::size_t>(argc);
    v[indice_invalido] = 999;  // comportamiento indefinido

    std::cout << "   Si el programa llego hasta aqui (sin sanitizers), observa los\n"
              << "   centinelas: " << centinela_anterior << " y " << centinela_posterior
              << ". Alguno pudo quedar corrompido.\n";
    return 0;
}
