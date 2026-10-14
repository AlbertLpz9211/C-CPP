# Práctica 3 · Arreglos

> Para llevar · resuélvela con el compilador abierto

Solución de referencia: `soluciones/solucion-practica-3.cpp`

---

## Ejercicio 1 · Recorridos básicos

Declara un arreglo `int notas[10]` con diez calificaciones inventadas y
escribe funciones para:

1. `double media(const int v[], int n)`
2. `int maximo(const int v[], int n)`
3. `int minimo(const int v[], int n)`
4. `int cuenta_aprobados(const int v[], int n)` — cuenta los mayores o iguales
   a 6

Todas reciben el tamaño como segundo parámetro. Explica en un comentario por
qué hace falta.

## Ejercicio 2 · Modificar un arreglo desde una función

Escribe `void suma_a_todos(int v[], int n, int cantidad)` que sume `cantidad`
a cada elemento.

Luego responde:

1. ¿Por qué funciona, si no pusimos `&` en ningún sitio?
2. ¿Qué pasaría si la firma fuera `void suma_a_todos(const int v[], int n, int cantidad)`?

## Ejercicio 3 · El error de uno

Este bucle tiene un error. Encuéntralo, corrígelo y explica qué pasa si no se
corrige.

```cpp
int v[5] = {1, 2, 3, 4, 5};
for (int i = 0; i <= 5; ++i) {
    std::cout << v[i] << ' ';
}
```

## Ejercicio 4 · Invertir un arreglo

Escribe `void invierte(int v[], int n)` que deje el arreglo al revés **sin
usar un segundo arreglo**. Usa la función `intercambia` por referencia que
viste en clase.

## Ejercicio 5 · Matriz

Declara `int m[3][4]` con valores a tu elección y escribe:

1. `void imprime(const int m[][4], int filas)`
2. `int suma_fila(const int m[][4], int fila)`
3. `int suma_columna(const int m[][4], int filas, int columna)`

Responde: ¿por qué el parámetro lleva `[][4]` y no `[][]`?

## Ejercicio 6 · Reto

Escribe `void transpuesta(const int origen[][3], int destino[][3], int filas)`
para una matriz cuadrada de 3×3: `destino[j][i] = origen[i][j]`.

---

### Lo que hay que llevarse

- Un arreglo se pasa siempre como **dirección**: no se copia y la función
  puede modificarlo.
- Como el tamaño no viaja, hay que **pasarlo aparte**.
- `const` en el parámetro es la forma de prometer que la función solo lee.
- En una matriz, todas las dimensiones menos la primera son obligatorias en la
  declaración del parámetro.
