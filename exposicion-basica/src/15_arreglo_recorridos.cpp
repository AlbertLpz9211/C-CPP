// ===========================================================================
// 15 - Algoritmos basicos sobre un arreglo
// Bloque 8 (25 min) - Arreglos unidimensionales
//
// OBJETIVO
//   Practicar el esqueleto de recorrido con los cuatro ejercicios clasicos:
//   suma y media, maximo, busqueda y ordenamiento.
//
// REGLA
//   Casi todo lo que se hace con un arreglo es un bucle for de 0 a n-1.
//
// PARA LA EXPOSICION
//   Escribir el de la media en vivo y dejar que el grupo dicte el del maximo.
// ===========================================================================

#include <iostream>

const int N = 8;

double media(const int v[], int n) {
    int total = 0;
    for (int i = 0; i < n; ++i) {
        total = total + v[i];
    }
    return static_cast<double>(total) / n;
}

int maximo(const int v[], int n) {
    int mayor = v[0];  // se empieza suponiendo que el primero es el mayor
    for (int i = 1; i < n; ++i) {
        if (v[i] > mayor) {
            mayor = v[i];
        }
    }
    return mayor;
}

// Devuelve la posicion del valor buscado, o -1 si no esta.
int busca(const int v[], int n, int buscado) {
    for (int i = 0; i < n; ++i) {
        if (v[i] == buscado) {
            return i;
        }
    }
    return -1;
}

// Ordenamiento de burbuja: el arreglo se modifica (sin const).
void ordena(int v[], int n) {
    for (int pasada = 0; pasada < n - 1; ++pasada) {
        for (int i = 0; i < n - 1 - pasada; ++i) {
            if (v[i] > v[i + 1]) {
                int temporal = v[i];
                v[i] = v[i + 1];
                v[i + 1] = temporal;
            }
        }
    }
}

void imprime(const int v[], int n) {
    for (int i = 0; i < n; ++i) {
        std::cout << v[i] << ' ';
    }
    std::cout << '\n';
}

int main() {
    int datos[N] = {23, 5, 78, 12, 99, 4, 56, 31};
    int m;
    std::cout<<"dame el numero de alumnos: ";
    std::cin>>m;

    int edades[m];

    std::cout<<"ingresa las edades de los alumnos: ";
    for(int i=0; i<m; i++){
        std::cin>>edades[i];
    }
    std::cout<<"las edades de los alumnos son: ";
    for(int i=0; i<m; i++){
        std::cout<<edades[i]<<" ";
    }

    std::cout << "datos : ";
    imprime(datos, N);

    std::cout << "media : " << media(datos, N) << '\n';
    std::cout << "maximo: " << maximo(datos, N) << '\n';

    std::cout << "busca(99) -> posicion " << busca(datos, N, 99) << '\n';
    std::cout << "busca(77) -> posicion " << busca(datos, N, 77)
              << "  (-1 significa que no esta)\n\n";

    ordena(datos, N);
    std::cout << "ordenados: ";
    imprime(datos, N);

    std::cout << "\nCONCLUSION: 'ordena' modifico el arreglo de main.\n"
              << "Los arreglos NUNCA se copian al pasarlos a una funcion.\n"
              << "Ese es el tema del siguiente bloque.\n";
    return 0;
}
