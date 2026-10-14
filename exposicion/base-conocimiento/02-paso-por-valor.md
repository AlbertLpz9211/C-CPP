# 2. Paso de argumentos por valor

> Bloque 2 de la exposición · 30 min · ejemplos `02`, `03`, `04`, `05`

## 2.1 Definición

En el paso por valor, el parámetro es un **objeto independiente** que se
inicializa copiando el valor del argumento. A partir de ese momento no existe
ninguna relación entre los dos.

```cpp
void f(int copia) {   // 'copia' es un objeto nuevo
    copia = 999;      // se modifica el objeto local, nada más
}

int main() {
    int original = 42;
    f(original);          // original sigue valiendo 42
}
```

La demostración que convence no es la explicación, sino imprimir las
direcciones: `&copia` dentro de la función y `&original` fuera son distintas.
Dos direcciones distintas significan dos objetos distintos.

## 2.2 Qué se copia exactamente

- **Tipos fundamentales** (`int`, `double`, `char`, `bool`, punteros, enums):
  se copian los bits. Es una operación de uno o dos ciclos.
- **Estructuras y clases**: se invoca el **constructor de copia**. Si es
  trivial, se copian los bits; si no, se ejecuta el código que el autor de la
  clase haya escrito.
- **Clases con memoria dinámica** (`std::string`, `std::vector`): la copia es
  *profunda*. Copiar un `vector` de un millón de enteros reserva memoria nueva
  y copia un millón de enteros, aunque el objeto `vector` en sí ocupe 24 bytes.
- **Arreglos crudos**: **no se copian**. Es la excepción, y se explica en el
  documento 6: el arreglo decae a puntero.

`04_costo_de_la_copia.cpp` hace visible este punto de dos maneras: con una
clase instrumentada que anuncia cada copia, y midiendo con `<chrono>` el
tiempo de 20 llamadas con un vector de cinco millones de enteros.

## 2.3 Ventajas

1. **Aísla al llamador.** La función no puede alterar sus datos. Al leer la
   llamada `f(x)` con `f` recibiendo por valor, se sabe que `x` no cambia.
2. **Sin problemas de vida.** El parámetro es dueño de su valor; no puede
   quedar colgante.
3. **Sin *aliasing*.** El compilador sabe que el parámetro no comparte memoria
   con nada más y puede optimizar con más libertad.
4. **Rápido para tipos pequeños.** Un `int` viaja en un registro; una
   referencia a `int` obliga a leer memoria.

## 2.4 Límites

1. **No puede modificar el argumento.** El caso canónico es el intercambio de
   dos variables (`03_swap_roto.cpp`): la lógica es correcta y el resultado es
   nulo, porque intercambia sus propias copias.
2. **Cuesta.** Para objetos grandes la copia se paga en tiempo y en memoria.
3. **No admite tipos no copiables**, como `std::unique_ptr` o `std::mutex`.
4. **Trunca el polimorfismo** (*object slicing*): si un parámetro es de la
   clase base y se pasa un objeto derivado por valor, la parte derivada se
   pierde en la copia. Es un error silencioso.

```cpp
struct Figura      { virtual double area() const { return 0; } };
struct Circulo : Figura { double r; double area() const override; };

void dibuja(Figura f);    // MAL: recibe solo la parte 'Figura'
void dibuja(const Figura& f);  // BIEN: conserva el tipo dinámico
```

## 2.5 Cuándo es la opción correcta

Contra la intuición de muchos cursos, el paso por valor es lo adecuado en tres
situaciones muy frecuentes (`05_valor_cuando_conviene.cpp`):

1. **Tipos baratos de copiar.** La guía práctica: si el objeto no supera dos o
   tres punteros (16–24 bytes en un sistema de 64 bits) y su copia es trivial,
   pásalo por valor.
2. **Cuando la función necesita su propia copia de trabajo.** Si de todos
   modos vas a copiar dentro del cuerpo, pide la copia en el parámetro. Es más
   claro y permite al compilador eliminar copias (*copy elision*).
3. **Parámetros sumidero.** Cuando la función se queda con el dato:
   `Usuario(std::string nombre) : nombre_(std::move(nombre)) {}`. Un argumento
   temporal se *mueve*, no se copia.

## 2.6 La regla oficial

C++ Core Guidelines, **F.16**: *"For 'in' parameters, pass cheaply-copied
types by value and others by reference to `const`"*. La guía sugiere
considerar barato de copiar todo lo que no exceda de dos a tres punteros.

Meyers, *Effective C++*, ítem 20: *"Prefer pass-by-reference-to-const to
pass-by-value"*, con la excepción explícita de los tipos fundamentales, los
iteradores y los objetos función.

## 2.7 Errores frecuentes

| Síntoma | Causa | Corrección |
|---|---|---|
| "La función no modifica mi variable" | parámetro por valor | usar `T&` |
| El programa se arrastra en un bucle | copiar `vector`/`string` en cada llamada | usar `const T&` |
| Se pierde el comportamiento de la clase derivada | *slicing* al pasar la base por valor | usar `const Base&` |
| No compila con `unique_ptr` | el tipo no es copiable | pasar por referencia o mover |

## 2.8 Fuentes

- C++ Core Guidelines, F.15, F.16, F.20.
- Meyers, S. *Effective C++*, 3.ª ed., ítem 20.
- Deitel & Deitel. *Cómo programar en C++*, 9.ª ed., cap. 6, "Paso de
  argumentos: llamada por valor y llamada por referencia".
- Stroustrup, B. *The C++ Programming Language*, 4.ª ed., cap. 12
  "Functions".
