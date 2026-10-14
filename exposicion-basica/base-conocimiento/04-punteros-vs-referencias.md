# 4. Punteros, referencias y `const`

> Bloque 5 de la exposición · 20 min · ejemplos `11`, `12`

## 4.1 Las dos herramientas

Punteros y referencias resuelven el mismo problema —dar a una función acceso
al objeto del llamador— pero no son intercambiables. Se diferencian en lo que
**permiten**:

| | `T&` (referencia) | `T*` (puntero) |
|---|---|---|
| Puede ser nulo | no | sí (`nullptr`) |
| Se puede reapuntar | no | sí |
| Debe inicializarse | sí | no |
| Sintaxis en la llamada | `f(x)` | `f(&x)` |
| Sintaxis de uso | `x` | `*p`, `p->` |
| Aritmética | no | sí (`p + 1`) |
| Puede apuntar a un arreglo entero | sí, con `T (&)[N]` | apunta al primer elemento |
| Ocupa memoria | conceptualmente no | sí, una dirección |

## 4.2 El criterio

C++ Core Guidelines **F.60**: *"Prefer `T*` over `T&` when 'no argument' is a
valid option"*.

Traducido a una regla de trabajo:

> Usa referencia por omisión. Usa puntero cuando la ausencia de dato sea un
> caso legítimo que la función deba manejar.

Un `T*` obliga a comprobar `nullptr`; un `T&` te ahorra esa comprobación
porque el lenguaje garantiza que hay un objeto. Menos comprobaciones significa
menos código y menos caminos que probar.

Alternativa moderna cuando el dato es opcional pero no quieres punteros:
`std::optional<T>` (por valor) o `std::optional<std::reference_wrapper<T>>`.

## 4.3 El punto que siempre se confunde

**Un puntero también se pasa por valor.** La función recibe una *copia de la
dirección*.

```cpp
void f(int* p) {
    *p = 10;        // SÍ afecta al objeto del llamador
    p = nullptr;    // NO afecta al puntero del llamador
}
```

Para que la función pueda cambiar *el puntero* del llamador hace falta
`int*&` (referencia a puntero) o `int**` (puntero a puntero). Es exactamente
la misma distinción de siempre, aplicada un nivel más arriba.

## 4.4 Dónde va el `const`

La regla de lectura es **de derecha a izquierda a partir del identificador**:

| Declaración | Lectura | ¿`*p = ...`? | ¿`p = ...`? |
|---|---|---|---|
| `int* p` | puntero a `int` | sí | sí |
| `const int* p` | puntero a `int` constante | **no** | sí |
| `int* const p` | puntero constante a `int` | sí | **no** |
| `const int* const p` | puntero constante a `int` constante | **no** | **no** |

`const int*` e `int const*` son el mismo tipo. La segunda forma hace la regla
de derecha a izquierda más evidente; la primera es la que se ve en la práctica.

Con referencias no hay ambigüedad: como la referencia nunca se reapunta, solo
existen dos casos, `const T&` (leer) y `T&` (leer y escribir).

### En parámetros de función

```cpp
void imprime(const int* datos, std::size_t n);  // promete no modificar
void llena  (int* datos, std::size_t n);        // va a escribir
```

Poner `const` donde corresponde no es cosmética: es la **única documentación
que el compilador verifica**. Además, un parámetro `const T&` acepta objetos
`const` y temporales que un `T&` rechazaría.

## 4.5 Reglas prácticas sobre punteros crudos

Las Core Guidelines son tajantes con los punteros que *poseen* memoria:

- **I.11**: *"Never transfer ownership by a raw pointer (`T*`) or reference
  (`T&`)"*. Para transferir propiedad se usa `std::unique_ptr` o
  `std::shared_ptr`.
- **I.13**: *"Do not pass an array as a single pointer"*. Para una secuencia
  contigua se usa `std::span`.

En código moderno, un `T*` en una firma significa "observo este objeto, que
puede no existir", nunca "me hago cargo de liberarlo".

## 4.6 Preguntas de comprobación

1. ¿Por qué `int& r = nullptr;` no compila?
2. Una función recibe `int* p` y hace `p = new int(5);`. ¿Qué le pasa al
   puntero del llamador? ¿Qué le pasa a la memoria reservada?
3. ¿Qué diferencia hay entre `const int* p` e `int* const p`?
4. ¿Cuándo elegirías `T*` en lugar de `T&` en un parámetro?

## 4.7 Fuentes

- C++ Core Guidelines, F.60, I.11, I.13.
- Stroustrup, B. *The C++ Programming Language*, 4.ª ed., cap. 7 "Pointers,
  Arrays, and References".
- Deitel & Deitel. *Cómo programar en C++*, 9.ª ed., cap. 8 "Apuntadores".
- ISO/IEC 14882, `[dcl.ptr]`, `[dcl.ref]`, `[basic.type.qualifier]`.
