# Práctica 1 · Paso de argumentos por valor

> Bloque 3 de la exposición · 15 min · trabajo individual o por parejas

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

Esta función debería duplicar el valor recibido. Compila y se ejecuta, pero no
funciona. Explica por qué y corrígela **sin cambiar `main`**.

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

## Ejercicio 3 · Elegir la forma de paso (4 min)

Para cada función, decide si el parámetro debe ir por valor, por `const&` o
por `&`, y justifica en una línea.

| Función | Parámetro | Tu elección |
|---|---|---|
| `double area(? radio)` | `double` | |
| `void imprime(? texto)` | `std::string` | |
| `void a_mayusculas(? texto)` | `std::string` | |
| `int cuenta_pares(? datos)` | `std::vector<int>` | |
| `void ordena(? datos)` | `std::vector<int>` | |

## Ejercicio 4 · Reto (4 min)

¿Cuántas veces se ejecuta el constructor de copia en este programa? Cuéntalas
antes de comprobarlo.

```cpp
struct Dato {
    Dato() = default;
    Dato(const Dato&) { std::cout << "copia\n"; }
};

void por_valor(Dato d) {}
void por_referencia(const Dato& d) {}

int main() {
    Dato d;
    por_valor(d);
    por_referencia(d);
    Dato otro = d;
    por_valor(otro);
}
```

---

## Soluciones

**1.** Imprime `dentro: a=8 b=3` y `fuera : x=3 y=8`. La función intercambia
correctamente sus copias; los originales no se tocan. Es el mismo mecanismo de
`03_swap_roto.cpp` con aritmética en lugar de variable temporal.

**2.** El parámetro es una copia. La corrección es `void duplica(int& n)`; la
llamada en `main` no cambia. Alternativa: `int duplica(int n) { return n*2; }`
con `valor = duplica(valor);`, pero eso sí modificaría `main`.

**3.**

| Función | Elección | Razón |
|---|---|---|
| `area(double radio)` | valor | tipo barato de copiar |
| `imprime(const std::string& texto)` | `const&` | entrada, objeto caro de copiar |
| `a_mayusculas(std::string& texto)` | `&` | entrada y salida: lo modifica |
| `cuenta_pares(const std::vector<int>& datos)` | `const&` | solo lee |
| `ordena(std::vector<int>& datos)` | `&` | lo modifica |

**4.** Tres copias: `por_valor(d)`, `Dato otro = d;` y `por_valor(otro)`. La
llamada `por_referencia(d)` no copia nada.
