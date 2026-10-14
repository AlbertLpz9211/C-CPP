// ===========================================================================
// 01 - El marco de pila: donde viven los parametros
// Bloque 1 (15 min) - Modelo de memoria y mecanica de la llamada
//
// OBJETIVO
//   Mostrar que cada llamada a funcion crea un marco de pila (stack frame)
//   nuevo y que los parametros son variables locales de ese marco. Sin esta
//   idea, "por valor" y "por referencia" se memorizan pero no se entienden.
//
// QUE OBSERVAR AL EJECUTAR
//   1. Las direcciones de las variables locales de cada nivel son distintas.
//   2. En arm64/x86-64 la pila crece hacia direcciones MENORES: cada llamada
//      anidada imprime una direccion mas pequena que la anterior.
//   3. Al volver de la funcion, ese marco deja de existir: la memoria se
//      reutiliza en la siguiente llamada.
//
// NOTA
//   Las direcciones exactas cambian en cada ejecucion (ASLR) y al activar
//   AddressSanitizer. Lo importante es la RELACION entre ellas, no el valor.
// ===========================================================================
#include <iostream>
/*


// Imprime la direccion de una variable local para ver donde quedo el marco.
void nivel_3(int profundidad) {
    int local = 30;
    std::cout << "  nivel_3 | profundidad=" << profundidad << " | &local = " << &local
              << " | &profundidad = " << &profundidad << '\n';
}

void nivel_2(int profundidad) {
    int local = 20;
    std::cout << "  nivel_2 | profundidad=" << profundidad << " | &local = " << &local
              << " | &profundidad = " << &profundidad << '\n';
    nivel_3(profundidad + 1);
}

void nivel_1(int profundidad) {
    int local = 10;
    std::cout << "  nivel_1 | profundidad=" << profundidad << " | &local = " << &local
              << " | &profundidad = " << &profundidad << '\n';
    nivel_2(profundidad + 1);
}

int main() {
    int local_main = 0;
    std::cout << "Cada llamada abre un marco de pila nuevo.\n";
    std::cout << "  main    | &local_main = " << &local_main << "\n\n";

    std::cout << "Primera cadena de llamadas:\n";
    nivel_1(1);

    std::cout << "\nSegunda cadena de llamadas (la pila se reutiliza):\n";
    nivel_1(1);

    std::cout << "\nTamanos en bytes de este equipo:\n"
              << "  sizeof(int)      = " << sizeof(int) << '\n'
              << "  sizeof(double)   = " << sizeof(double) << '\n'
              << "  sizeof(void*)    = " << sizeof(void*) << '\n';

    std::cout << "\nCONCLUSION: un parametro es una variable local mas del marco.\n"
              << "La pregunta 'por valor o por referencia' es la pregunta de QUE\n"
              << "se guarda en esa variable local: una copia del dato, o su direccion.\n";
    return 0;
}
*/

int suma(float a, float b){
    return a + b;
}
//funciones que retornan float

float suma(int a, int b){
    return a + b;
}

int edad(){
    int anos=20;
    return 33;
}


int main(){
    int x=1, y=2;
    float a=1.5, b=2.5;
    std::cout << "Funciones basicas de C++20" << std::endl;
    //std::cout << "Suma de enteros: " << suma(x, y) << std::endl;
    //std::cout << "Suma de floats: " << suma(a, b) << std::endl;
    std::cout <<"Suma fallida " << suma(a , b) << std::endl; // falla de compilacion
    std::cout << "Hola, tengo " << edad() << " años" << std::endl;
    return 0;
}
