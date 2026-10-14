# 6. Arreglos como parámetros: el decaimiento

> Bloque 8 de la exposición · 20 min · ejemplos `16`, `17`, `18`

Este es el documento que **une los dos temas de la exposición**. Hasta aquí
había dos formas de pasar un argumento: por valor y por referencia. Los
arreglos no usan ninguna de las dos.

## 6.1 La regla

Un arreglo **no se pasa por valor ni por referencia**: se convierte en un
puntero a su primer elemento. A esa conversión se le llama **decaimiento**
(*array-to-pointer decay*).

Dos reglas de la norma lo establecen:

> `[conv.array]/1` — "Una expresión E de tipo *arreglo de N T* o *arreglo de
> límite desconocido de T* puede convertirse a un prvalue de tipo *puntero a
> T*."

> `[dcl.fct]/5` — "Después de determinar el tipo de cada parámetro, todo
> parámetro de tipo *arreglo de T* o de tipo función T se ajusta para ser
> *puntero a T*."

La primera describe la conversión de la expresión en el punto de llamada; la
segunda, el ajuste del parámetro en la declaración de la función.

## 6.2 Las consecuencias

### Las tres declaraciones son la misma función

```cpp
void f(int v[10]);   // el 10 se ignora por completo
void f(int v[]);
void f(int* v);      // esta es la firma real de las tres
```

Declarar las tres en el mismo programa da error de redefinición. El número
entre corchetes es puramente decorativo: no reserva nada, no se comprueba y no
impide pasar un arreglo de otro tamaño.

### `sizeof` deja de servir

```cpp
int datos[10];
sizeof(datos);        // 40 en un sistema con int de 4 bytes

void f(int v[10]) {
    sizeof(v);        // 8: el tamaño de un PUNTERO
}
```

Calcular `sizeof(v)/sizeof(v[0])` dentro de una función que recibió el arreglo
como parámetro es uno de los errores más frecuentes del lenguaje. Clang lo
detecta con `-Wsizeof-array-argument`.

### El arreglo nunca se copia

Como solo viaja la dirección, pasar un arreglo es barato **siempre**, y la
función **puede modificar los elementos del llamador** aunque la sintaxis
parezca un paso por valor. Es la única excepción a la regla "por valor
significa copia".

### Hay que pasar el tamaño aparte

```cpp
double media(const double* v, std::size_t n);
```

Es la firma clásica de C. Funciona, pero deja abierta la puerta a
desincronizar los dos argumentos, que es exactamente el fallo que produce
desbordamientos de búfer.

## 6.3 Las cuatro soluciones

### 1. Puntero + tamaño (clásico)

```cpp
double media(const double* v, std::size_t n);
```
Universal y compatible con C. Requiere disciplina del llamador.

### 2. Referencia a arreglo (conserva el tamaño)

```cpp
void f(int (&v)[10]);          // solo acepta int[10]

template <std::size_t N>
void g(const int (&v)[N]);     // N deducido por el compilador
```

Los paréntesis son obligatorios: `int& v[10]` significaría un arreglo de
referencias, que no existe en C++. Dentro de la función, `sizeof(v)`,
`std::size(v)` y el `for` basado en rango vuelven a funcionar, porque el tipo
conserva el tamaño.

### 3. `std::span<T>` (C++20, recomendado)

```cpp
double media(std::span<const double> datos);
```

`std::span` es un objeto ligero que guarda **dirección + tamaño**. No es dueño
de la memoria: es una vista sobre una secuencia contigua que ya existe. Ocupa
dos palabras (16 bytes en 64 bits) y se pasa por valor.

Una sola firma acepta arreglo crudo, `std::array` y `std::vector`, y el tamaño
viaja junto a los datos, de modo que ya no se pueden desincronizar.

- **I.13**: *"Do not pass an array as a single pointer"*.
- **F.24**: *"Use a `span<T>` or a `span_p<T>` to designate a half-open
  sequence"*.

Advertencia: como no es dueño de nada, un `span` puede quedar colgante igual
que una referencia si el contenedor original muere o se realoja.

### 4. Cambiar de contenedor

`std::array<T,N>` y `std::vector<T>` se pasan como cualquier otro objeto:
`const std::vector<T>&` para leer, `std::vector<T>&` para modificar. No
decaen, conocen su tamaño y se copian y devuelven con normalidad.

## 6.4 Tabla comparativa

| Forma | Conserva tamaño | Acepta cualquier tamaño | Acepta `vector` | Estándar |
|---|---|---|---|---|
| `T* v, std::size_t n` | manual | sí | con `.data()` | C++98 |
| `T (&v)[N]` | sí | no (tamaño fijo) | no | C++98 |
| `template<std::size_t N> T (&v)[N]` | sí | sí | no | C++98 |
| `std::span<T>` | sí | sí | sí | C++20 |
| `const std::vector<T>&` | sí | sí | sí | C++98 |

## 6.5 Preguntas de comprobación

1. ¿Cuántas funciones distintas declaran estas tres líneas?
   `void f(int v[5]); void f(int v[]); void f(int* v);`
2. ¿Por qué `for (int x : v)` no compila dentro de una función que recibió
   `int v[]`?
3. Una función recibe `int v[]` y hace `v[0] = 99;`. ¿Cambia el arreglo del
   llamador? ¿Por qué, si "por valor" significa copia?
4. ¿Qué ventaja tiene `std::span<const double>` frente a
   `const double*, std::size_t`?

## 6.6 Fuentes

- ISO/IEC 14882, `[conv.array]/1` y `[dcl.fct]/5`.
- C++ Core Guidelines, I.13, F.24.
- Stroustrup, B. *The C++ Programming Language*, 4.ª ed., cap. 7 "Pointers,
  Arrays, and References".
- Deitel & Deitel. *Cómo programar en C++*, 9.ª ed., cap. 8, "Relación entre
  apuntadores y arreglos".
