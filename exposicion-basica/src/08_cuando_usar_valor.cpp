// ===========================================================================
// 08 - Cuando el paso por valor es la opcion correcta
// Bloque 3 (25 min) - Paso de argumentos por valor
//
// OBJETIVO
//   Evitar que el grupo se lleve la idea de que "por valor es malo".
//   Es la forma normal de pasar numeros y de proteger los datos del llamador.
//
// REGLA
//   Si la funcion solo necesita LEER un dato pequeno (int, double, char,
//   bool), se pasa por valor.
//
// PARA LA EXPOSICION
//   Recalcar la ventaja: dentro de la funcion se puede modificar el parametro
//   sin miedo, porque es una copia de trabajo.
// ===========================================================================

#include <iostream>

// 1. Calculo con numeros: por valor.
double area_circulo(double radio) {
    return 3.14159265 * radio * radio;
}

// 2. La funcion necesita su propia copia para trabajar: por valor.
//    Aqui el parametro se va modificando dentro sin danar el original.
int cuenta_digitos(int n) {
    if (n == 0) {
        return 1;
    }
    if (n < 0) {
        n = -n;
    }

    int digitos = 0;
    while (n > 0) {
        n = n / 10;  // modifica la copia, no el argumento
        ++digitos;
    }
    return digitos;
}

// 3. Proteger al llamador: esta funcion NO PUEDE estropear nada.
void imprime_tabla(int numero, int hasta) {
    for (int i = 1; i <= hasta; ++i) {
        std::cout << "  " << numero << " x " << i << " = " << numero * i << '\n';
    }
}

int main() {
    std::cout << "area_circulo(2.0)  = " << area_circulo(2.0) << "\n\n";

    int valor = 40325;
    std::cout << "cuenta_digitos(" << valor << ") = " << cuenta_digitos(valor) << '\n';
    std::cout << "valor sigue siendo " << valor << "  <-- intacto\n\n";

    std::cout << "Tabla del 7 hasta 5:\n";
    imprime_tabla(7, 5);

    std::cout << "\nCONCLUSION: por valor es lo normal para numeros.\n"
              << "Es rapido, es seguro y deja usar el parametro como borrador.\n";
    return 0;
}
