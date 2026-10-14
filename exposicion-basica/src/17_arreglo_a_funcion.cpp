// ===========================================================================
// 17 - Que le llega a una funcion cuando le pasas un arreglo
// Bloque 9 (20 min) - Arreglos como parametros
//
// OBJETIVO
//   Responder la pregunta bisagra de la sesion: un arreglo no se pasa por
//   valor ni por referencia. Lo que viaja es la DIRECCION del primer
//   elemento. Por eso no se copia y por eso la funcion puede modificarlo.
//
// REGLA
//   void f(int v[10])  es lo mismo que  void f(int v[])  y que  void f(int* v).
//   Dentro de la funcion, el arreglo ya no conoce su tamano: hay que pasarlo
//   aparte.
//
// PARA LA EXPOSICION
//   Este es el punto contraintuitivo del dia. Decirlo con estas palabras:
//   "un arreglo NUNCA se copia al pasarlo a una funcion".
// ===========================================================================

#include <iostream>

// El aviso -Wsizeof-array-argument es justo la leccion de esta demostracion,
// asi que se silencia para que el ejemplo compile limpio.
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wsizeof-array-argument"
void dentro_de_la_funcion(int v[]) {
    std::cout << "  [dentro] v apunta a        " << v << '\n';
    std::cout << "  [dentro] sizeof(v)       = " << sizeof(*v)
              << " bytes  <-- el tamano de UNA DIRECCION\n";
    std::cout << "  [dentro] primer elemento = " << v[-10] << '\n';


    v[0] = 999;  // modifica el arreglo del llamador, sin haberlo copiado

}


// Forma correcta: el tamano viaja como segundo parametro.
void imprime(const int v[], int n) {
    for (int i = 0; i < n; ++i) {
        std::cout << v[i] << ' ';
    }
    std::cout << '\n';
}

void pon_a_cero(int v[], int n) {
    for (int i = 0; i < n; ++i) {
        v[i] = 0;
    }
}

int main() {
    int datos[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    std::cout << "[fuera]  datos empieza en " << datos << '\n';
    std::cout << "[fuera]  sizeof(datos)  = " << sizeof(datos)
              << " bytes  <-- 10 enteros de 4 bytes\n\n";

    dentro_de_la_funcion(datos);

    std::cout << "\n[fuera]  datos[0] = " << datos[0]
              << "  <-- la funcion SI lo modifico\n\n";

    std::cout << "datos: ";
    imprime(datos, 10);

    pon_a_cero(datos, 10);
    std::cout << "tras pon_a_cero: ";
    imprime(datos, 10);

    std::cout << "\nCONCLUSION: a la funcion solo le llega una direccion.\n"
              << "1. El arreglo no se copia, da igual lo grande que sea.\n"
              << "2. La funcion puede modificar los elementos del llamador.\n"
              << "3. Dentro ya no se sabe cuantos elementos hay: pasa el tamano.\n"
              << "4. Si la funcion no debe modificarlo, escribe const.\n";
    return 0;
}
