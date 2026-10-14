# Práctica 3 · Arreglos y matrices

> Para llevar. Cubre los bloques 7, 8 y 9.

Solución de referencia: `soluciones/solucion-practica-3.cpp`

---

## Ejercicio 1 · Corregir el conteo

Esta función siempre devuelve 2 en un sistema de 64 bits, sin importar el
arreglo que reciba. Explica por qué y corrígela de **tres formas distintas**.

```cpp
int suma(int v[]) {
    int s = 0;
    for (std::size_t i = 0; i < sizeof(v) / sizeof(v[0]); ++i) {
        s += v[i];
    }
    return s;
}
```

## Ejercicio 2 · Índices

Dada `int m[4][6]`:

1. ¿De qué tipo es `m[2]`?
2. ¿Cuántos bytes ocupa `m` completa, con `int` de 4 bytes?
3. ¿Cuál es el índice lineal del elemento `m[2][3]`?
4. Escribe la expresión con puntero equivalente a `m[2][3]`.

## Ejercicio 3 · Recorrido

Escribe una función que reciba una matriz de `double` de 3 filas y 4 columnas
y devuelva la suma de cada fila en un arreglo de salida. Hazlo en las dos
formas: con parámetro de salida y con `std::array` de retorno.

## Ejercicio 4 · Reto

Escribe una función `transpuesta` genérica con plantillas que reciba una
matriz `const int (&)[F][C]` y escriba el resultado en `int (&)[C][F]`.
Comprueba que el compilador rechaza pasarle matrices de dimensiones
incompatibles.

## Ejercicio 5 · Medición

Escribe un programa que sume todos los elementos de una matriz de 1000×1000
`int` de las dos formas (por filas y por columnas) y mida ambas con
`<chrono>`. Compílalo con `-O2` y explica la diferencia.

---

## Soluciones

**1.** El parámetro `int v[]` es en realidad `int*`, así que `sizeof(v)` es 8 y
`sizeof(v[0])` es 4. Las tres correcciones:

```cpp
int suma(const int* v, std::size_t n);                      // puntero + tamaño
template <std::size_t N> int suma(const int (&v)[N]);       // referencia a arreglo
int suma(std::span<const int> v);                           // C++20
```

**2.**
1. `int[6]`, una fila entera.
2. 4 × 6 × 4 = 96 bytes.
3. 2 × 6 + 3 = 15.
4. `*(&m[0][0] + 15)`, o equivalentemente `*(m[2] + 3)`.

**3.** Véase `soluciones/solucion-practica-3.cpp`. La versión con `std::array`
de retorno es preferible según F.20: un arreglo crudo no se puede devolver,
pero un `std::array` sí.

**4.**
```cpp
template <std::size_t F, std::size_t C>
void transpuesta(const int (&a)[F][C], int (&r)[C][F]) {
    for (std::size_t i = 0; i < F; ++i)
        for (std::size_t j = 0; j < C; ++j)
            r[j][i] = a[i][j];
}
```
Al llevar las dimensiones en el tipo, el compilador verifica la compatibilidad.

**5.** El recorrido por columnas es varias veces más lento porque cada acceso
salta a una línea de caché distinta. Véase `07-arreglos-multidimensionales.md`,
§7.7, con la medición tomada en el equipo del curso.
