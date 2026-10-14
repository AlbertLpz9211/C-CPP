// ===========================================================================
// 02 - Paso por valor: la funcion trabaja sobre una copia
// Bloque 2 (30 min) - Paso de argumentos por valor
//
// OBJETIVO
//   Demostrar con direcciones de memoria que el parametro por valor es un
//   OBJETO DISTINTO del argumento: se inicializa copiando su valor y a partir
//   de ahi las dos variables no tienen ninguna relacion.
//
// REGLA
//   Al llamar f(x) con parametro por valor, el parametro se inicializa por
//   copia desde x. Modificar el parametro dentro de la funcion NO modifica x.
//
// PARA LA EXPOSICION
//   Preguntar a la audiencia que imprimira el programa ANTES de ejecutarlo.
//   El error clasico es esperar que 'original' cambie a 999.
// ===========================================================================

#include <iostream>

void intenta_modificar(int copia) {
    std::cout << "  [dentro]  recibi     = " << copia << " en la direccion " << &copia << '\n';
    copia = 999;  // Modifica SOLO la variable local del marco de esta funcion.
    std::cout << "  [dentro]  ahora vale = " << copia << " (pero es mi copia)\n";
}

// Tambien se copian los tipos definidos por el usuario, campo por campo.
struct Punto {
    double x;
    double y;
};

void mueve_al_origen(Punto p) {
    p.x = 0.0;
    p.y = 0.0;
    std::cout << "  [dentro]  mi copia quedo en (" << p.x << ", " << p.y << ") en " << &p << '\n';
}

int main() {
    int original = 42;
    std::cout << "Paso por valor de un int\n";
    std::cout << "  [antes]   original   = " << original << " en la direccion " << &original << '\n';

    intenta_modificar(original);

    std::cout << "  [despues] original   = " << original << "  <-- NO cambio\n\n";

    Punto p{3.5, 7.25};
    std::cout << "Paso por valor de una estructura\n";
    std::cout << "  [antes]   p = (" << p.x << ", " << p.y << ") en " << &p << '\n';
    mueve_al_origen(p);
    std::cout << "  [despues] p = (" << p.x << ", " << p.y << ")  <-- NO cambio\n\n";

    std::cout << "CONCLUSION: las direcciones impresas dentro y fuera son distintas.\n"
              << "Son dos objetos diferentes; solo se copio el valor inicial.\n";
    return 0;
}
