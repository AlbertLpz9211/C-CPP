# 9. Errores frecuentes, preguntas y respuestas

Material de apoyo para la sesión de preguntas y para el repaso final.

## 9.1 Los diez errores que más se ven

| # | Error | Por qué ocurre | Corrección |
|---|---|---|---|
| 1 | La función no modifica la variable del llamador | parámetro por valor | usar `T&` |
| 2 | `swap` que no intercambia nada | el clásico del punto 1 | `void swap(int& a, int& b)` |
| 3 | `sizeof(v)/sizeof(v[0])` dentro de una función | el arreglo decayó a puntero | pasar el tamaño, usar `std::span` o `T (&)[N]` |
| 4 | Bucle `for (i = 0; i <= n; ++i)` | el índice máximo es `n-1` | cambiar `<=` por `<` |
| 5 | `int v[n]` con `n` leído del usuario | los VLA no son C++ | `std::vector<int> v(n);` |
| 6 | Devolver una referencia a una variable local | se ignoró el aviso del compilador | devolver por valor |
| 7 | Guardar una referencia a `v[0]` y luego hacer `push_back` | el vector se realojó | guardar el índice |
| 8 | Pasar una matriz como `int**` | `int[3][4]` decae a `int (*)[4]` | `int m[][4]` o plantilla |
| 9 | Programa lento al recorrer matrices | bucles en el orden equivocado | último índice en el bucle interno |
| 10 | Copiar `vector`/`string` en cada llamada | parámetro por valor | `const T&` |

## 9.2 Preguntas que suele hacer el grupo

**¿Pasar por referencia es siempre más rápido?**
No. Para tipos pequeños (`int`, `double`, punteros) el paso por valor suele ser
más rápido: el dato viaja en un registro, mientras que la referencia obliga a
un acceso a memoria. La regla F.16 existe justamente por eso.

**¿La referencia ocupa memoria?**
La norma no lo especifica. En la práctica el compilador la implementa como una
dirección cuando hace falta, y la elimina por completo cuando puede. No se
puede tomar `sizeof` de una referencia como tal: `sizeof(r)` devuelve el tamaño
del objeto referido.

**Si un arreglo se pasa "por valor", ¿por qué la función puede modificarlo?**
Porque un arreglo no se pasa por valor. Decae a puntero: lo que se copia es la
dirección, no los elementos. Es la excepción del lenguaje y conviene decirla
con esas palabras.

**¿Por qué los índices empiezan en cero?**
Porque el índice es un desplazamiento desde la dirección base:
`v[i]` significa `*(v + i)`. El primer elemento está a desplazamiento cero.

**¿`std::span` copia los datos?**
No. Guarda dirección y tamaño, dos palabras. Por eso se pasa por valor y por
eso puede quedar colgante si el contenedor original muere.

**¿Cuándo uso puntero y cuándo referencia?**
Referencia por omisión. Puntero cuando "no hay argumento" sea un caso válido
(F.60), o cuando necesites aritmética de punteros.

**¿`const T&` sirve para `int`?**
Compila, pero no aporta nada y suele ser más lento. Para tipos baratos de
copiar, `int` a secas.

**¿Qué pasa si escribo fuera de un arreglo?**
Comportamiento indefinido. El programa puede funcionar, imprimir basura,
corromper otra variable o abortar. No hay ninguna garantía, y esa
imprevisibilidad es lo peligroso.

## 9.3 Comprobaciones rápidas para el cierre

1. ¿Qué imprime este programa y por qué?
   ```cpp
   void f(int a) { a = 10; }
   int main() { int x = 1; f(x); std::cout << x; }
   ```
2. Escribe la firma de una función que reciba un arreglo de `double` y
   devuelva su promedio, en las cuatro formas vistas.
3. ¿De qué tipo es `m[1]` si `m` es `int m[3][4]`?
4. Corrige: `int suma(int v[]) { int s = 0; for (std::size_t i = 0; i < sizeof(v)/sizeof(v[0]); ++i) s += v[i]; return s; }`
5. ¿Por qué `void f(int** m)` no acepta un `int m[3][4]`?

### Respuestas

1. Imprime `1`. `a` es una copia; modificarla no afecta a `x`.
2. `double promedio(const double* v, std::size_t n);` ·
   `template<std::size_t N> double promedio(const double (&v)[N]);` ·
   `double promedio(std::span<const double> v);` ·
   `double promedio(const std::vector<double>& v);`
3. `int[4]`: una fila entera.
4. `v` es un `int*`; `sizeof(v)/sizeof(v[0])` vale 2 en un sistema de 64 bits.
   Hay que recibir el tamaño: `int suma(const int* v, std::size_t n)`.
5. Porque `int[3][4]` es un bloque contiguo de 12 enteros y decae a
   `int (*)[4]`, mientras que `int**` supone un arreglo de direcciones de fila.

## 9.4 Herramientas que conviene mostrar

```sh
# Compilar con todos los avisos
clang++ -std=c++20 -Wall -Wextra -Wpedantic archivo.cpp -o programa

# Detectar errores de memoria en ejecución
clang++ -std=c++20 -g -fsanitize=address,undefined archivo.cpp -o programa
ASAN_OPTIONS=detect_stack_use_after_return=1 ./programa

# Ver el ensamblador o probar en línea
# https://godbolt.org  (Compiler Explorer)
```

`godbolt.org` es especialmente útil en esta exposición: permite mostrar en
vivo que el paso por valor de un `int` genera una instrucción y el paso por
referencia genera un acceso a memoria.
