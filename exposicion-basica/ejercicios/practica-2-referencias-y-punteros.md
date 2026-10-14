# Práctica 2 · Referencias y punteros

> Bloque 7 de la exposición · 15 min · por parejas

Solución de referencia: `soluciones/solucion-practica-2.cpp`

---

## Ejercicio 1 · Elegir la forma de paso (4 min)

Para cada función, decide si el parámetro debe ir por valor (`int`), por
referencia (`int&`) o por referencia constante (`const int&`), y justifica en
una línea.

| Intención de la función | Parámetro | Tu elección |
|---|---|---|
| `double raiz(? x)` — calcula la raíz cuadrada | `double` | |
| `void incrementa(? contador)` — le suma 1 | `int` | |
| `void imprime(? nota)` — solo la muestra | `double` | |
| `void intercambia(? a, ? b)` | `int` | |
| `bool es_positivo(? n)` | `int` | |

## Ejercicio 2 · Predecir la salida (4 min)

```cpp
#include <iostream>

void f(int a, int& b) {
    a = a * 10;
    b = b * 10;
}

int main() {
    int x = 1, y = 1;
    f(x, y);
    std::cout << x << ' ' << y << '\n';

    int& r = x;
    r = 50;
    std::cout << x << ' ' << r << '\n';
}
```

Escribe las dos líneas de salida antes de ejecutarlo.

## Ejercicio 3 · Dos resultados en una función (4 min)

Escribe una función que, dados dos números enteros, devuelva **a la vez** el
cociente entero y el resto:

```cpp
void divide(int a, int b, int& cociente, int& resto);
```

Compruébala con `divide(17, 5, c, r)`: debe dejar `c = 3` y `r = 2`.

Después, escribe la misma función con punteros:

```cpp
void divide_con_punteros(int a, int b, int* cociente, int* resto);
```

¿Qué cambia en la llamada?

## Ejercicio 4 · Reto (3 min)

Esta función quiere poner a cero la variable del llamador, pero no funciona.
Explica por qué y arréglala de dos maneras: con referencia y con puntero.

```cpp
void pon_a_cero(int n) {
    n = 0;
}
```

---

### Lo que hay que llevarse

- `int n` copia · `int& n` es la misma variable · `const int& n` la ve pero no
  la toca.
- La llamada `f(x)` se ve **igual** con copia y con referencia: hay que leer la
  firma de la función.
- Con punteros, la llamada avisa a la vista: `f(&x)`.
