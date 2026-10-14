# 5. Arreglos unidimensionales

> Bloque 7 de la exposición · 25 min · ejemplos `13`, `14`, `15`

## 5.1 Definición

Un arreglo es un **bloque contiguo de N objetos del mismo tipo**, con N fijo y
conocido en tiempo de compilación. Todo lo demás se deduce de esas dos
propiedades: contigüidad y tamaño fijo.

```cpp
int v[5];       // tipo: int[5]; 5 objetos int seguidos en memoria
```

La norma (`[dcl.array]/1`) exige que el tamaño sea *una expresión constante
convertida de tipo `std::size_t`* con valor mayor que cero. De ahí sale la
limitación más importante:

```cpp
int n;
std::cin >> n;
int malo[n];        // NO es C++ estándar
```

Eso es un *arreglo de longitud variable* (VLA), una extensión de C99 que C++
nunca adoptó. Algunos compiladores lo aceptan como extensión; con
`-Wpedantic` avisan. La respuesta correcta en C++ es `std::vector<int> v(n);`.

## 5.2 Declaración e inicialización

| Forma | Resultado |
|---|---|
| `int a[5] = {10,20,30,40,50};` | los cinco valores dados |
| `int b[5] = {1,2};` | `1 2 0 0 0` — lo que falta se inicializa a cero |
| `int c[5] = {};` | los cinco a cero |
| `int d[] = {7,8,9};` | tamaño deducido: 3 |
| `int e[3];` | valores **indeterminados**; leerlos es comportamiento indefinido |

En C++11 en adelante se puede omitir el `=`: `int a[5]{10,20,30,40,50};`.

## 5.3 Índices y direcciones

Los índices válidos van de `0` a `N-1`. El operador `[]` no es magia: por
definición, `v[i]` equivale a `*(v + i)`, y la dirección resultante es

```
&v[i] == dirección_base + i * sizeof(T)
```

Esto explica por qué los índices empiezan en cero: el índice es un
*desplazamiento* desde el inicio, no una posición ordinal. También explica que
`v[i]` y `i[v]` sean la misma expresión, curiosidad que suele funcionar bien
como anécdota en clase.

## 5.4 Tamaño

```cpp
sizeof(a)                  // bytes que ocupa TODO el arreglo
sizeof(a) / sizeof(a[0])   // número de elementos, forma clásica
std::size(a)               // número de elementos, C++17, <iterator>
```

`std::size` es preferible: es más legible y **falla al compilar** si se aplica
a un puntero, que es justo el error que la forma clásica no detecta.

## 5.5 Recorrido

```cpp
// Clásico, con índice
for (std::size_t i = 0; i < std::size(a); ++i) { ... a[i] ... }

// Basado en rango, C++11: no hay índices que equivocar
for (int valor : a) { ... }

// Para modificar hace falta referencia
for (int& valor : a) { valor *= 2; }
```

El `for` basado en rango funciona sobre un arreglo **solo mientras el tipo
conserve su tamaño**. Dentro de una función que recibió el arreglo como
parámetro ya no funciona, porque el parámetro es un puntero (documento 6).

Nótese que `for (int valor : a)` copia cada elemento; con elementos grandes se
escribe `for (const auto& valor : a)`.

## 5.6 El arreglo no comprueba límites

`v[10]` en un arreglo de cinco elementos **compila y se ejecuta**. Lee o
escribe memoria que no le pertenece. El estándar lo llama comportamiento
indefinido: el programa puede imprimir basura, corromper otra variable,
funcionar hoy y fallar mañana, o abrir un agujero de seguridad.

Este es el origen histórico del *desbordamiento de búfer*, una de las clases
de vulnerabilidad más explotadas de la historia del software. No es un detalle
académico.

### Qué sí avisa

| Herramienta | Qué detecta | Cuándo |
|---|---|---|
| `-Warray-bounds` | índice constante fuera de rango | compilación |
| `std::array::at()` / `vector::at()` | cualquier índice fuera de rango | ejecución, lanza `std::out_of_range` |
| AddressSanitizer (`-fsanitize=address`) | accesos fuera de rango reales | ejecución |
| UndefinedBehaviorSanitizer | índices fuera de rango, entre otras cosas | ejecución |
| `_LIBCPP_HARDENING_MODE` | comprobaciones en la biblioteca estándar | ejecución |

El compilador solo puede avisar de lo que puede calcular. En
`14_fuera_de_rango.cpp` el índice se deriva de `argc` precisamente para
demostrar ese límite: escrito como literal, clang lo detecta; calculado en
ejecución, no.

### El error de un elemento

```cpp
for (int i = 0; i <= 5; ++i)   // MAL: recorre 6 posiciones de un arreglo de 5
for (int i = 0; i <  5; ++i)   // BIEN
```

El índice válido máximo es `N-1`. La condición correcta usa `<`, nunca `<=`.

## 5.7 Lo que un arreglo no puede hacer

- **No se puede asignar**: `a = b;` no compila.
- **No se puede copiar** en una inicialización: `int b[5] = a;` no compila.
- **No se puede devolver** desde una función.
- **No se puede comparar**: `a == b` compara direcciones, no contenidos.
- **No conoce su tamaño** una vez pasado a una función.

`std::array<T,N>` sí puede hacer todo eso, con el mismo rendimiento y sin
sobrecosto de memoria.

## 5.8 Algoritmos típicos

`15_arreglo_algoritmos.cpp` recoge los cuatro que cubren la mayoría de los
ejercicios del tema: acumular (media), buscar un extremo (máximo), búsqueda
lineal y ordenamiento por burbuja. Todos comparten el mismo esqueleto:

```cpp
for (std::size_t i = 0; i < n; ++i) { /* trabajar con v[i] */ }
```

La biblioteca estándar ya trae versiones probadas y más rápidas en
`<algorithm>` y `<numeric>`: `std::sort`, `std::find`, `std::max_element`,
`std::accumulate`. Merece la pena mostrarlas al final del bloque, después de
haber escrito los bucles a mano.

## 5.9 Fuentes

- ISO/IEC 14882, `[dcl.array]` y `[expr.sub]`.
- Stroustrup, B. *The C++ Programming Language*, 4.ª ed., cap. 7 "Pointers,
  Arrays, and References".
- Deitel & Deitel. *Cómo programar en C++*, 9.ª ed., cap. 7 "Plantillas de
  clase array y vector" y cap. 8 "Apuntadores".
- C++ Core Guidelines, I.13 ("Do not pass an array as a single pointer") y
  F.24 ("Use a span<T> ... to designate a half-open sequence").
