# 3. Paso de argumentos por referencia

> Bloque 4 de la exposición · 35 min · ejemplos `06`, `07`, `08`, `09`, `10`

## 3.1 Qué es una referencia

Una referencia `T&` es **otro nombre para un objeto que ya existe**. No es un
objeto nuevo, no reserva memoria propia (conceptualmente) y no es un puntero
con azúcar sintáctico: es un *alias*.

Tres reglas que la definen:

1. **Debe inicializarse** en su declaración. No existe una referencia vacía.
2. **No se puede reapuntar.** Queda ligada a ese objeto de por vida. Escribir
   `alias = otro;` asigna el *valor* de `otro` al objeto original; no cambia a
   qué objeto se refiere `alias`.
3. **No puede ser nula.** Siempre hay un objeto detrás.

La comprobación en clase es una sola línea: `&referencia == &objeto` da
verdadero. Misma dirección, mismo objeto.

## 3.2 El paso por referencia

Cuando un parámetro se declara `T&`, el parámetro se liga al argumento del
llamador. No hay copia. Escribir en el parámetro es escribir en el argumento.

```cpp
void intercambia(int& a, int& b) {   // dos símbolos '&' cambian todo
    int temporal = a;
    a = b;
    b = temporal;
}

int main() {
    int x = 1, y = 2;
    intercambia(x, y);   // x vale 2, y vale 1
}
```

**Detalle que hay que señalar en la exposición:** en el punto de llamada,
`intercambia(x, y)` se escribe exactamente igual que la versión por valor. La
sintaxis de la llamada no revela nada. Solo la declaración de la función dice
si los argumentos pueden cambiar. Es una diferencia importante frente a C,
donde `f(&x)` avisa visualmente.

## 3.3 Las tres formas de parámetro por referencia

| Forma | Nombre | Significado | Uso |
|---|---|---|---|
| `const T&` | referencia a `const` | entrada, sin copiar | leer objetos grandes |
| `T&` | referencia no const | entrada y salida | modificar el argumento |
| `T&&` | referencia a rvalue | sumidero, se va a mover | `std::move`, constructores de movimiento |

`T&&` pertenece al tema de semántica de movimiento y queda fuera del alcance
de esta exposición; basta mencionar que existe.

## 3.4 `const T&`: el parámetro más común de C++

Combina las dos ventajas: no copia y no permite modificar. Además **acepta más
argumentos** que `T&`:

```cpp
std::size_t longitud(const std::string& texto);

longitud(nombre);                  // lvalue: sí
longitud("literal");               // temporal creado por conversión: sí
longitud(std::string{"temp"});     // temporal: sí
longitud(objeto_const);            // objeto const: sí
```

Un `T&` no const rechaza los tres últimos casos. El motivo tiene sentido:
permitir que una función modifique un temporal que va a morir en la siguiente
línea casi siempre es un error del programador, así que el lenguaje lo prohíbe.

Un `const T&` ligado a un temporal **extiende la vida** de ese temporal hasta
el final de la vida de la referencia. Es lo que permite escribir
`promedio({30.0, 40.0})` sin nombrar el vector.

## 3.5 Ventajas del paso por referencia

1. **Permite modificar el argumento**: es la única forma (junto con punteros)
   de que una función cambie los datos del llamador.
2. **No copia**: coste constante, independientemente del tamaño del objeto.
3. **Conserva el tipo dinámico**: no hay *slicing*; el polimorfismo funciona.
4. **Admite tipos no copiables**.

## 3.6 Riesgos

### Referencias colgantes (`09_referencias_colgantes.cpp`)

Una referencia **no es dueña** del objeto. Si el objeto muere primero, queda
colgante y usarla es comportamiento indefinido. Dos causas dominan:

- **Devolver una referencia a una variable local.** El compilador avisa
  (`-Wreturn-stack-address`), pero el aviso se puede ignorar.
- **Guardar una referencia a un elemento de un contenedor que después crece.**
  Cuando un `std::vector` supera su capacidad, reserva un bloque nuevo, mueve
  los elementos y libera el anterior. Toda referencia, puntero o iterador al
  contenido queda invalidado. La solución práctica es guardar el **índice**,
  no la referencia.

### Modificación no evidente

`procesa(datos)` puede alterar `datos` sin que se note al leer la llamada. Es
el argumento a favor de `const` por omisión: si el parámetro no necesita
cambiar, ponle `const` y el compilador lo garantiza.

### Aliasing

Si dos parámetros por referencia designan el mismo objeto, el resultado puede
sorprender:

```cpp
void suma_en(int& destino, const int& a, const int& b) {
    destino = 0;
    destino += a;
    destino += b;
}
int x = 5;
suma_en(x, x, x);   // no da 10
```

## 3.7 Parámetros de salida frente a valor de retorno

El paso por referencia permite "devolver" varios datos escribiendo en
parámetros de salida. Es la técnica clásica heredada de C, pero C++ moderno
prefiere el valor de retorno (`10_salida_por_parametro.cpp`):

- **F.20**: *"For 'out' output values, prefer return values to output
  parameters"*.
- **F.21**: *"To return multiple 'out' values, prefer returning a struct"*.

```cpp
// Clásico
void estadisticas(const std::vector<double>& d, double& min, double& max, double& media);

// Preferido
struct Estadisticas { double minimo, maximo, media; };
Estadisticas estadisticas(const std::vector<double>& d);

auto [mn, mx, md] = estadisticas(datos);   // enlace estructurado, C++17
```

El valor de retorno no se puede ignorar por accidente, no obliga a declarar
variables sin inicializar antes de la llamada y se compone con otras
expresiones.

## 3.8 Tabla de decisión

| Intención | Parámetro | Regla |
|---|---|---|
| Entrada, tipo barato de copiar | `T` | F.16 |
| Entrada, tipo caro de copiar | `const T&` | F.16 |
| Entrada y salida | `T&` | F.17 |
| Solo salida | valor de retorno | F.20 |
| Varias salidas | `struct` de retorno | F.21 |
| Puede no haber argumento | `T*` u `std::optional` | F.60 |
| Secuencia contigua | `std::span<T>` | F.24, I.13 |

## 3.9 Fuentes

- C++ Core Guidelines, F.15–F.21, F.24, F.60.
- Stroustrup, B. *The C++ Programming Language*, 4.ª ed., cap. 7 "Pointers,
  Arrays, and References" y cap. 12 "Functions".
- Deitel & Deitel. *Cómo programar en C++*, 9.ª ed., cap. 6.
- ISO/IEC 14882, `[dcl.ref]` (referencias) y `[class.temporary]` (extensión de
  la vida de temporales).
