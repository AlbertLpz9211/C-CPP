# 7. Arreglos multidimensionales

> Bloque 9 de la exposición · 25 min · ejemplos `19`, `20`, `21`, `22`, `23`

## 7.1 La idea central

`int m[3][4]` **no** es una tabla con propiedades especiales. Es un arreglo de
3 elementos, y cada elemento es a su vez un arreglo de 4 `int`.

> `[dcl.array]/9` — "Cuando varias especificaciones *array of* son adyacentes
> se crea un tipo de arreglo multidimensional."

De esa frase salen todas las reglas del tema. En particular:

- `m` es de tipo `int[3][4]`.
- `m[i]` es de tipo `int[4]` — **una fila entera**, no un elemento.
- `m[i][j]` es de tipo `int`.

## 7.2 Orden por filas (*row-major*)

C y C++ guardan la matriz **fila por fila**, en un único bloque contiguo:

```
int m[3][4]:

[ m00 m01 m02 m03 | m10 m11 m12 m13 | m20 m21 m22 m23 ]
  ---- fila 0 ----   ---- fila 1 ----   ---- fila 2 ----
índice lineal: 0..3        4..7             8..11
```

La dirección de `m[i][j]` es:

```
base + (i * COLUMNAS + j) * sizeof(T)
```

La norma lo explica con un ejemplo en `[dcl.array]/9`: en `x3d[i][j][k]` el
índice `i` se multiplica por el tamaño completo del objeto formado por las
dimensiones restantes.

Fortran, MATLAB, R y Julia usan el orden inverso (*column-major*). Es una
causa clásica de errores al portar código numérico o al interoperar con
bibliotecas de álgebra lineal como BLAS y LAPACK.

## 7.3 Inicialización

```cpp
int m[3][4] = {{1,2,3,4},
               {5,6,7,8},
               {9,10,11,12}};        // por filas, legible

int m2[3][4] = {1,2,3,4,5,6,7,8,9,10,11,12};   // válido, menos claro

int m3[2][3] = {{1}, {4,5}};         // resto a cero: {1,0,0},{4,5,0}

int m4[3][4] = {};                   // todo a cero
```

## 7.4 Tamaños

```cpp
sizeof(m)          // toda la matriz
sizeof(m[0])       // una fila
sizeof(m[0][0])    // un elemento

filas    = sizeof(m)    / sizeof(m[0]);
columnas = sizeof(m[0]) / sizeof(m[0][0]);
```

## 7.5 Recorrido

```cpp
for (int i = 0; i < FILAS; ++i)
    for (int j = 0; j < COLUMNAS; ++j)
        m[i][j] ...

// Basado en rango: la variable externa DEBE ser referencia a fila
for (const auto& fila : m)      // fila es 'const int (&)[4]'
    for (int valor : fila)
        ...
```

Si se escribe `for (auto fila : m)` el compilador intentaría copiar un arreglo,
que no se puede copiar; en la práctica `fila` decae a puntero y el bucle
interno deja de compilar. Es un error muy común y merece mencionarse.

## 7.6 Pasar una matriz a una función

Aplicando el decaimiento del documento 6: `int m[3][4]` decae a **puntero a
arreglo de 4 `int`**, es decir `int (*)[4]`. **No decae a `int**`.**

```cpp
void f(int m[][4], int filas);   // válido: solo la 1.ª dimensión puede omitirse
void f(int m[3][4], int filas);  // el 3 se ignora
void f(int (*m)[4], int filas);  // la firma real de las dos anteriores
void f(int** m, ...);            // ERROR conceptual: no es una matriz
```

El compilador necesita conocer **todas las dimensiones menos la primera**,
porque sin el número de columnas no puede calcular `i * COLUMNAS + j`.

### Por qué `int**` no funciona

`int**` significa "puntero a puntero a `int`": supone que en memoria hay un
arreglo de **direcciones**, cada una apuntando a una fila suelta. Una matriz
`int[3][4]` es un único bloque de 12 enteros, sin ninguna tabla de
direcciones. Son disposiciones de memoria incompatibles, y el compilador lo
rechaza:

```
cannot initialize a parameter of type 'int **' with an lvalue of type 'int[3][4]'
```

### Las cuatro formas de pasarla

| Forma | Ventaja | Límite |
|---|---|---|
| `const int m[][C], int filas` | clásica, compatible con C | columnas fijas al compilar |
| `const int (*m)[C], int filas` | idéntica, sintaxis explícita | igual |
| `template<F,C> const int (&m)[F][C]` | conserva ambas dimensiones | genera código por cada tamaño |
| `const int* datos, int filas, int columnas` | dimensiones libres | índice calculado a mano |

La última —la **vista aplanada**— es la que usan por dentro las bibliotecas
numéricas: un solo bloque lineal y el índice `i * columnas + j`.

## 7.7 El orden de los bucles cambia el rendimiento

Es la demostración más contundente del bloque (`23_orden_de_recorrido.cpp`).
El mismo cálculo, con los dos bucles intercambiados:

```cpp
for (i) for (j) suma += m[i][j];   // por filas: memoria contigua
for (j) for (i) suma += m[i][j];   // por columnas: salta COLUMNAS*4 bytes
```

Medición real sobre una matriz de 2048 × 2048 enteros (16 MiB), compilada con
`-O2` en un Apple Silicon:

| Recorrido | Tiempo |
|---|---|
| por filas | 0.88 ms |
| por columnas | 25.84 ms |

Casi 30 veces más lento, con el mismo resultado numérico.

**Explicación.** La memoria se lee en bloques (*líneas de caché*, típicamente
64 o 128 bytes). Al leer `m[i][0]` el procesador trae de golpe los elementos
contiguos, que son el resto de la fila. Si el bucle avanza por la fila, esos
datos ya están en caché. Si avanza por columnas, cada acceso salta a otra
línea y casi siempre hay que ir a memoria principal.

> **Regla:** en C y C++, el **último índice** debe ser el del bucle **más
> interno**.

## 7.8 Tres dimensiones y la fórmula general

Para `T v[D0][D1][D2]`, el elemento `v[i][j][k]` está en

```
base + ( i*D1*D2 + j*D2 + k ) * sizeof(T)
```

El patrón se generaliza: cada índice se multiplica por el producto de todas
las dimensiones que quedan a su derecha.

A partir de tres dimensiones, lo habitual en código profesional es usar un
bloque lineal con la fórmula del índice encapsulada en una clase (véase
`24_alternativas_modernas.cpp`) o `std::mdspan`, incorporado en C++23.

## 7.9 Preguntas de comprobación

1. ¿De qué tipo es `m[1]` si `m` es `int[3][4]`?
2. ¿Por qué se puede omitir la primera dimensión al declarar el parámetro,
   pero no la segunda?
3. ¿Cuál es el índice lineal de `m[2][3]` en una matriz de 4 columnas?
4. Dos programas calculan la misma suma de una matriz de 16 MiB y uno tarda 30
   veces más. ¿Qué los diferencia?

## 7.10 Fuentes

- ISO/IEC 14882, `[dcl.array]/9`.
- Stroustrup, B. *The C++ Programming Language*, 4.ª ed., cap. 7 "Pointers,
  Arrays, and References".
- Deitel & Deitel. *Cómo programar en C++*, 9.ª ed., cap. 7, "Arreglos
  bidimensionales".
- Drepper, U. *What Every Programmer Should Know About Memory* (2007), §3,
  sobre líneas de caché y localidad.
