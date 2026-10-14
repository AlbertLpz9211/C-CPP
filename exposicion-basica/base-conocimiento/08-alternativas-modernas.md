# 8. Qué usar en lugar del arreglo crudo

> Bloque 10 de la exposición · 10 min · ejemplo `24`

## 8.1 Por qué seguimos enseñando arreglos crudos

Porque hay que saber **leerlos**: aparecen en C, en todo el código heredado,
en sistemas embebidos, en las APIs del sistema operativo y en los exámenes.
Pero para **escribir** código nuevo en C++ casi siempre hay una opción mejor.

## 8.2 Las tres herramientas

### `std::array<T, N>` — `<array>`

Tamaño fijo, conocido en tiempo de compilación. Es el sustituto directo del
arreglo crudo, **sin ningún sobrecosto**: `sizeof(std::array<int,4>) == 16`,
igual que `int[4]`.

Lo que gana frente al arreglo crudo:

- conoce su tamaño (`.size()`) y **no decae** al pasarlo;
- se copia, se asigna y se **devuelve** desde una función;
- se compara con `==`, se ordena, se usa con todos los algoritmos;
- tiene `.at()` con comprobación de límites.

### `std::vector<T>` — `<vector>`

Tamaño decidido en ejecución y modificable. Es la respuesta correcta cuando el
número de elementos lo decide el usuario o el archivo de entrada. Reserva la
memoria en el montón, y la libera sola.

Es la respuesta al VLA que C++ no tiene:

```cpp
int n;  std::cin >> n;
std::vector<int> v(n);      // esto sí es C++ estándar
```

Advertencia relevante para el tema anterior: al crecer, un `vector` puede
realojar su memoria e **invalidar** todas las referencias, punteros e
iteradores a sus elementos.

### `std::span<T>` — `<span>`, C++20

Una **vista**: dirección + tamaño, sin propiedad. Es para **parámetros**, no
para almacenar. Una sola firma acepta arreglo crudo, `std::array` y
`std::vector`.

## 8.3 Para matrices

| Opción | Contigua | Dimensiones | Sintaxis | Nota |
|---|---|---|---|---|
| `std::array<std::array<T,C>,F>` | sí | fijas al compilar | `m[i][j]` | equivalente moderno de `T m[F][C]` |
| `std::vector<T>` aplanado + `i*C+j` | sí | en ejecución | `m(i,j)` con una clase | lo que usan las bibliotecas numéricas |
| `std::vector<std::vector<T>>` | **no** | en ejecución | `m[i][j]` | cómodo pero lento: cada fila es un bloque suelto |
| `std::mdspan` (C++23) | sí | en ejecución | `m[i,j]` | vista multidimensional sobre un bloque lineal |

La tercera opción es la que más se ve en trabajos de clase y la que peor
rendimiento da: `N` reservas independientes, memoria dispersa y un salto de
puntero por fila. Conviene mencionarlo explícitamente.

El patrón de la segunda opción cabe en pocas líneas y es el que vale la pena
mostrar (`24_alternativas_modernas.cpp`):

```cpp
class Matriz {
public:
    Matriz(std::size_t filas, std::size_t columnas)
        : filas_(filas), columnas_(columnas), datos_(filas * columnas, 0.0) {}

    double& operator()(std::size_t i, std::size_t j)       { return datos_[i*columnas_ + j]; }
    double  operator()(std::size_t i, std::size_t j) const { return datos_[i*columnas_ + j]; }

private:
    std::size_t filas_, columnas_;
    std::vector<double> datos_;
};
```

Reúne todo lo visto en la exposición: memoria contigua, la fórmula del índice
por filas, dimensiones que viajan con el objeto, y `const` correcto en las dos
sobrecargas del operador.

## 8.4 Criterio final

| Situación | Elección |
|---|---|
| Tamaño fijo y conocido al compilar | `std::array<T,N>` |
| Tamaño decidido al ejecutar | `std::vector<T>` |
| Parámetro que recibe una secuencia | `std::span<T>` |
| Parámetro de entrada, objeto grande | `const T&` |
| Interoperar con C, o sistema embebido | arreglo crudo |

## 8.5 Fuentes

- C++ Core Guidelines, I.13, F.24.
- Stroustrup, B. *A Tour of C++*, 2.ª ed., cap. 11 "Containers".
- Josuttis, N. *The C++ Standard Library*, 2.ª ed., capítulos sobre `array`,
  `vector` y contenedores en general.
- ISO/IEC 14882, `[views.span]`.
