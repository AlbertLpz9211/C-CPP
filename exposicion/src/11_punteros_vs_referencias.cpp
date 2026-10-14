// ===========================================================================
// 11 - Punteros y referencias: cuando usar cada uno
// Bloque 5 (20 min) - const, punteros vs referencias
//
// OBJETIVO
//   Las dos herramientas permiten que una funcion acceda al objeto del
//   llamador. No son intercambiables: se diferencian en lo que PERMITEN.
//
//                          T&                    T*
//   Puede ser nulo         no                    si (nullptr)
//   Se puede reapuntar     no                    si
//   Requiere inicializar   si                    no
//   Sintaxis en la llamada f(x)                  f(&x)
//   Sintaxis de uso        x                     *p  /  p->
//   Aritmetica             no                    si (p + 1)
//
// CRITERIO (Core Guidelines F.60)
//   "Prefer T* over T& when 'no argument' is a valid option".
//   Es decir: usa referencia por omision; usa puntero cuando la ausencia de
//   dato es un caso legitimo que la funcion debe manejar.
// ===========================================================================

#include <iostream>
#include <string>

// El argumento es obligatorio: referencia.
void duplica(int& n) {
    n *= 2;
}

// El argumento es opcional: puntero, y la funcion debe comprobar el nulo.
void registra_si_hay_destino(std::string* bitacora, const std::string& mensaje) {
    if (bitacora == nullptr) {  // ausencia de destino: caso valido, no un error
        return;
    }
    *bitacora += mensaje + '\n';
}

// Un puntero se puede reapuntar; se usa para recorrer.
void muestra_recorrido(const int* inicio, std::size_t cantidad) {
    for (const int* p = inicio; p != inicio + cantidad; ++p) {  // aritmetica de punteros
        std::cout << *p << ' ';
    }
    std::cout << '\n';
}

int main() {
    int n = 21;
    duplica(n);
    std::cout << "1) Referencia: argumento obligatorio\n"
              << "   duplica(n) -> n = " << n << "\n\n";

    std::string bitacora;
    registra_si_hay_destino(&bitacora, "primer evento");
    registra_si_hay_destino(nullptr, "este evento se descarta");
    registra_si_hay_destino(&bitacora, "segundo evento");
    std::cout << "2) Puntero: argumento opcional\n"
              << "   contenido de la bitacora:\n";
    std::cout << bitacora << '\n';

    int numeros[5] = {2, 4, 6, 8, 10};
    std::cout << "3) Puntero: se reapunta y admite aritmetica\n   ";
    muestra_recorrido(numeros, 5);
    std::cout << '\n';

    // 4) Un detalle que confunde: un puntero tambien se pasa POR VALOR.
    //    La funcion recibe una copia de la direccion. Puede modificar el
    //    objeto apuntado (*p = ...), pero reasignar p dentro no afecta al
    //    puntero del llamador. Para eso haria falta int*& o int**.
    std::cout << "4) El puntero tambien viaja por valor\n"
              << "   'int* p' copia la DIRECCION. Modificar *p afecta al llamador;\n"
              << "   modificar p (la direccion) no. Para eso se usa 'int*&'.\n\n";

    std::cout << "REGLA DE DECISION\n"
              << "  Necesito acceder al objeto del llamador -> referencia.\n"
              << "  Ademas 'sin objeto' es un caso valido   -> puntero (o std::optional).\n";
    return 0;
}
