# Práctica 1 · Funciones y paso por valor

> Bloque 4 de la exposición · 15 min · individual o por parejas

Solución de referencia: `soluciones/solucion-practica-1.cpp`

---

## Ejercicio 1 · Predecir la salida (3 min)

Sin ejecutarlo, escribe qué imprime este programa y explica por qué.

```cpp
#include <iostream>

void misterio(int a, int b) {
    a = a + b;
    b = a - b;
    a = a - b;
    std::cout << "dentro: a=" << a << " b=" << b << '\n';
}

int main() {
    int x = 3, y = 8;
    misterio(x, y);
    std::cout << "fuera : x=" << x << " y=" << y << '\n';
}
```

## Ejercicio 2 · Encontrar el error (4 min)

Esta función debería duplicar el valor recibido. Compila y se ejecuta, pero
`valor` sigue valiendo 21. Explica por qué y corrígela **sin cambiar la
declaración de la función**, es decir, dejando el parámetro por valor.

```cpp
void duplica(int n) {
    n = n * 2;
}

int main() {
    int valor = 21;
    duplica(valor);
    std::cout << valor << '\n';   // se espera 42
}
```

> Pista: si el parámetro es una copia, el resultado tiene que salir de la
> función por el único camino que queda.

## Ejercicio 3 · Escribir tres funciones (5 min)

Escribe y prueba estas tres funciones. Todas reciben sus datos por valor.

| Función | Qué hace |
|---|---|
| `double perimetro_rectangulo(double base, double altura)` | devuelve el perímetro |
| `bool es_multiplo(int n, int divisor)` | devuelve `true` si `n` es múltiplo de `divisor` |
| `void imprime_cuenta_atras(int desde)` | imprime `desde, desde-1, ... , 1, 0` |

Fíjate en cuál devuelve un valor y cuál solo hace algo.

## Ejercicio 4 · Reto (3 min)

Escribe una función `int factorial(int n)` que calcule el factorial con un
bucle. Después responde por escrito:

1. ¿Modifica `factorial` la variable que se le pasa?
2. ¿Qué pasa si dentro de la función escribes `n = n - 1` en cada vuelta?
3. ¿Hace falta declarar una copia del parámetro para poder usarlo como
   contador?

---

### Lo que hay que llevarse

- Un parámetro por valor es una **variable nueva** de la función.
- Se puede modificar libremente dentro: es una copia de trabajo.
- Para que un resultado salga de la función, hay que **devolverlo con
  `return`**.
