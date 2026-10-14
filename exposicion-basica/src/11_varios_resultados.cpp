// ===========================================================================
// 11 - Devolver varios resultados con parametros por referencia
// Bloque 5 (30 min) - Paso de argumentos por referencia
//
// OBJETIVO
//   Mostrar el uso mas util del paso por referencia en un curso basico: una
//   funcion solo puede devolver UN valor con return; con referencias puede
//   entregar varios.
//
// REGLA
//   Un parametro T& sirve cuando la funcion debe ESCRIBIR en una variable del
//   llamador.
//
// PARA LA EXPOSICION
//   Hacer notar que las variables mn, mx y media se declaran antes de la
//   llamada, porque la funcion escribe en ellas.
// ===========================================================================

#include <iostream>

// Una sola funcion devuelve tres datos: minimo, maximo y media.
void estadisticas(int a, int b, int c, int& minimo, int& maximo, double& media) {
    minimo = a;
    if (b < minimo) {
        minimo = b;
    }
    if (c < minimo) {
        minimo = c;
    }

    maximo = a;
    if (b > maximo) {
        maximo = b;
    }
    if (c > maximo) {
        maximo = c;
    }

    media = (a + b + c) / 3.0;
}

// Entrada y salida a la vez: entra con un valor y sale modificado.
void aplica_descuento(double& precio, double porcentaje) {
    precio = precio - precio * porcentaje / 100.0;
}

// Devolver ademas si la operacion se pudo hacer.
bool divide(double a, double b, double& resultado) {
    if (b == 0.0) {
        return false;  // no se toca 'resultado'
    }
    resultado = a / b;
    return true;
}

int main() {
    int menor = 0;
    int mayor = 0;
    double media = 0.0;

    estadisticas(14, 3, 9, menor, mayor, media);
    std::cout << "estadisticas(14, 3, 9)\n";
    std::cout << "  minimo = " << menor << '\n';
    std::cout << "  maximo = " << mayor << '\n';
    std::cout << "  media  = " << media << "\n\n";

    double precio = 200.0;
    aplica_descuento(precio, 15.0);
    std::cout << "precio con 15% de descuento = " << precio << "\n\n";

    double cociente = 0.0;
    if (divide(10.0, 4.0, cociente)) {
        std::cout << "10 / 4 = " << cociente << '\n';
    }
    if (!divide(10.0, 0.0, cociente)) {
        std::cout << "10 / 0 no se pudo calcular\n";
    }

    std::cout << "\nCONCLUSION: usa T& cuando la funcion deba escribir en una\n"
              << "variable del llamador. Si solo devuelve un dato, usa return.\n";
    return 0;
}
