// ===========================================================================
// 06 - Paso por valor: la funcion trabaja sobre una copia
// Bloque 3 (25 min) - Paso de argumentos por valor
//
// OBJETIVO
//   Demostrar con direcciones de memoria que el parametro por valor es una
//   variable DISTINTA del argumento: se crea copiando su valor y a partir de
//   ahi las dos no tienen ninguna relacion.
//
// REGLA
//   Al llamar f(x) con parametro por valor, el parametro se inicializa con
//   una copia de x. Modificar el parametro NO modifica x.
//
// PARA LA EXPOSICION
//   Preguntar al grupo que imprimira ANTES de ejecutarlo. El error clasico es
//   esperar que 'original' cambie a 999.
// ===========================================================================

#include <iostream>

void intenta_modificar(int copia) {
    std::cout << "  [dentro]  recibi     = " << copia
              << " en la direccion " << &copia << '\n';
    copia = 999;  // modifica SOLO la variable local de esta funcion
    std::cout << "  [dentro]  ahora vale = " << copia << " (pero es mi copia)\n";
}

void duplica_mal(double n) {
    n = n * 2;  // se pierde al terminar la funcion
}



double duplica_bien_resta(double n, double resta) {
    return (n * 2) - resta;  // el resultado viaja de vuelta con return
}

int main() {
    int original = 42;
    std::cout << "Paso por valor de un int\n";
    std::cout << "  [antes]   original   = " << original
              << " en la direccion " << &original << '\n';

    intenta_modificar(original);

    std::cout << "  [despues] original   = " << original << "  <-- NO cambio\n\n";

    double precio = 21.5;
    double resta = 5.0;
    duplica_mal(precio);
    std::cout << "despues de duplica_mal(precio):  precio = " << precio
              << "  <-- NO cambio\n";

    precio = duplica_bien_resta(precio, resta);
    std::cout << "despues de precio = duplica_bien(precio): precio = " << precio
              << "  <-- SI cambio\n\n";

    std::cout << "CONCLUSION: las direcciones de dentro y de fuera son distintas.\n"
              << "Son dos variables diferentes; solo se copio el valor inicial.\n"
              << "Para que el cambio salga de la funcion, hay que DEVOLVERLO.\n";
    return 0;
}
