// ===========================================================================
// 16 - Decaimiento: por que un arreglo "pierde" su tamaño al pasarlo
// Bloque 8 (20 min) - Arreglos como parametros
//
// OBJETIVO
//   Este es EL punto que une los dos temas de la exposicion. Un arreglo no se
//   pasa por valor ni por referencia: se convierte en un puntero a su primer
//   elemento. A eso se le llama decaimiento (array-to-pointer decay).
//
// LAS DOS REGLAS DE LA NORMA
//   [conv.array]/1  "Una expresion E de tipo 'arreglo de N T' puede
//                    convertirse a un prvalue de tipo 'puntero a T'".
//   [dcl.fct]/5     "Despues de determinar el tipo de cada parametro, todo
//                    parametro de tipo 'arreglo de T' se ajusta a 'puntero a T'".
//
// CONSECUENCIA PRACTICA
//   Estas TRES declaraciones son exactamente la misma funcion:
//       void f(int v[10]);
//       void f(int v[]);
//       void f(int* v);
//   El 10 se ignora por completo. Dentro de f, sizeof(v) es el tamaño de un
//   puntero, no el del arreglo. Por eso hay que pasar el tamaño aparte.
//
// EFECTO SECUNDARIO UTIL
//   Como se copia solo la direccion, pasar un arreglo es barato SIEMPRE, y
//   la funcion puede modificar los elementos del llamador aunque "parezca"
//   que se paso por valor. Un arreglo nunca se copia al pasarlo.
// ===========================================================================

#include <iostream>
#include <iterator>

// El '10' es decorativo: el compilador lo descarta. La firma real es int*.
//
// Al escribir sizeof(v) aqui dentro, clang avisa por su cuenta:
//   warning: sizeof on array function parameter will return size of 'int *'
//            instead of 'int[10]' [-Wsizeof-array-argument]
// Es la confirmacion del compilador de lo que explica este archivo. El pragma
// solo silencia ese aviso para que el proyecto compile limpio; comentalo en
// clase para mostrar el diagnostico real.
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wsizeof-array-argument"
#endif
void recibe_como_arreglo(int v[10]) {
    std::cout << "  dentro de recibe_como_arreglo(int v[10])\n"
              << "    sizeof(v) = " << sizeof(v) << " bytes  <-- tamaño de un PUNTERO\n"
              << "    v[0] = " << v[0] << '\n';
    v[0] = 777;  // modifica el arreglo del llamador: no hubo copia
}
#if defined(__clang__)
#pragma clang diagnostic pop
#endif

void recibe_como_puntero(int* v, std::size_t n) {
    std::cout << "  dentro de recibe_como_puntero(int* v, n)\n"
              << "    sizeof(v) = " << sizeof(v) << " bytes\n"
              << "    n recibido = " << n << "  <-- el tamaño hay que pasarlo aparte\n";
}

// Sobrecargas para demostrar que los tres perfiles son el mismo tipo:
// si se descomenta cualquiera de estas dos, el compilador dice
// "redefinition of 'recibe_como_arreglo'".
//   void recibe_como_arreglo(int v[]) {}
//   void recibe_como_arreglo(int* v) {}

int main() {
    int datos[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    std::cout << "En main, donde el arreglo conserva su tipo int[10]\n"
              << "  sizeof(datos)    = " << sizeof(datos) << " bytes\n"
              << "  std::size(datos) = " << std::size(datos) << " elementos\n\n";

    recibe_como_arreglo(datos);
    std::cout << "  tras la llamada, datos[0] = " << datos[0]
              << "  <-- cambio: nunca hubo copia\n\n";

    recibe_como_puntero(datos, std::size(datos));

    // El decaimiento tambien ocurre fuera de las llamadas a funcion.
    int* p = datos;  // sin '&' ni [0]: el nombre del arreglo decae solo
    std::cout << "\nDecaimiento fuera de una llamada\n"
              << "  int* p = datos;   -> p apunta a " << p << " y datos esta en " << datos << '\n'
              << "  *p = " << *p << ", p[3] = " << p[3] << "  (la sintaxis [] funciona igual)\n"
              << "  sizeof(p) = " << sizeof(p) << " vs sizeof(datos) = " << sizeof(datos) << "\n\n";

    std::cout << "ERROR CLASICO\n"
              << "  Calcular sizeof(v)/sizeof(v[0]) DENTRO de una funcion que recibio\n"
              << "  el arreglo como parametro. Ahi siempre da " << sizeof(int*) / sizeof(int)
              << " en este equipo, sin importar\n"
              << "  cuantos elementos tenga el arreglo real.\n\n"
              << "SOLUCIONES (en orden de preferencia moderna)\n"
              << "  1. std::span<int>            -> 18_span.cpp\n"
              << "  2. referencia a arreglo      -> 17_arreglo_por_referencia.cpp\n"
              << "  3. puntero + tamaño          -> lo clasico, hay que ser disciplinado\n"
              << "  4. std::array / std::vector  -> 24_alternativas_modernas.cpp\n";
    return 0;
}
