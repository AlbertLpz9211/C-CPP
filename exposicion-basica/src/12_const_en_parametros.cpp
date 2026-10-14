// ===========================================================================
// 12 - const: permitir leer, prohibir modificar
// Bloque 5 (30 min) - Paso de argumentos por referencia
//
// OBJETIVO
//   Mostrar que const en un parametro convierte una intencion ("esta funcion
//   no cambia el dato") en una garantia que revisa el compilador.
//
// REGLA
//   const T& : la funcion recibe la variable original, pero solo puede leerla.
//
// PARA LA EXPOSICION
//   Descomentar la linea marcada y compilar: "cannot assign to variable with
//   const-qualified type".
// ===========================================================================

#include <iostream>

// Sin const: la funcion PUEDE modificar la variable del llamador.
void sube_nota(double& nota) {
    nota = nota + 1.0;
}

// Con const: recibe la variable original, pero el compilador impide tocarla.
void imprime_nota(const double& nota) {
    //nota = 10.0;   // <-- descomentar: error de compilacion
    std::cout << "  nota = " << nota << '\n';
}

// En un arreglo, const es aun mas util: sin el, la funcion podria
// modificar los elementos del llamador sin avisar.
int suma(const int datos[], int n) {
    int total = 0;
    for (int i = 0; i < n; ++i) {
        total = total + datos[i];
        // datos[i] = 0;   // <-- descomentar: error de compilacion
    }
    return total;
}

int main() {
    double nota = 7.5;

    std::cout << "Antes: ";
    imprime_nota(nota);

    sube_nota(nota);
    std::cout << "Despues de sube_nota(nota): ";
    imprime_nota(nota);

    int calificaciones[5] = {8, 9, 10, 7, 6};
    std::cout << "\nsuma de las 5 calificaciones = " << suma(calificaciones, 5) << '\n';

    std::cout << "\nCONCLUSION: al leer una firma de funcion,\n"
              << "  double  n   -> recibe una copia, no cambia nada mio\n"
              << "  double& n   -> puede cambiar mi variable\n"
              << "  const double& n -> ve mi variable, pero no la cambia\n";
    return 0;
}
