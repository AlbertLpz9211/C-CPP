# 1. Modelo de memoria y mecánica de la llamada a función

> Bloque 1 de la exposición · 15 min · ejemplo `01_marco_de_pila.cpp`

Sin este bloque, "por valor" y "por referencia" se memorizan como una regla
arbitraria. Con él, las dos formas de paso se deducen solas.

## 1.1 Dónde vive cada cosa

Un programa en ejecución organiza su memoria en cuatro regiones. La norma no
las nombra así (habla de *duración de almacenamiento*), pero toda
implementación real las tiene:

| Región | Duración de almacenamiento | Qué contiene | Quién la administra |
|---|---|---|---|
| Código (*text*) | estática | las instrucciones compiladas | el cargador del sistema |
| Datos estáticos | estática | variables globales, `static`, literales de cadena | el compilador |
| Pila (*stack*) | automática | parámetros, variables locales, dirección de retorno | el compilador, automáticamente |
| Montón (*heap*) | dinámica | lo que se pide con `new` / `malloc` / lo que hay dentro de `vector` y `string` | el programador (o un contenedor RAII) |

Los cuatro términos de la norma son: `static`, `thread`, `automatic` y
`dynamic storage duration`. Todo lo que se declara dentro de una función sin
`static` tiene **duración automática**: nace al llegar a su declaración y
muere al salir de su ámbito. Esa frase es la causa de la mitad de los errores
del tema, incluidas las referencias colgantes.

## 1.2 El marco de pila

Cada llamada a función crea un **marco de pila** (*stack frame*), un bloque de
memoria que contiene:

1. la dirección de retorno (a dónde volver);
2. los **parámetros** de la función;
3. sus **variables locales**;
4. registros que hay que preservar.

```
Direcciones altas
┌───────────────────────────┐
│ marco de main             │  local_main
├───────────────────────────┤
│ marco de nivel_1          │  profundidad, local
├───────────────────────────┤
│ marco de nivel_2          │  profundidad, local
├───────────────────────────┤
│ marco de nivel_3          │  profundidad, local   <- cima de la pila
└───────────────────────────┘
Direcciones bajas
```

En arm64 y x86-64 la pila **crece hacia direcciones menores**. Por eso
`01_marco_de_pila.cpp` imprime direcciones cada vez más pequeñas conforme se
anidan las llamadas. Al volver de una función, su marco simplemente se
descarta: no se borra nada, solo se mueve el puntero de pila. La siguiente
llamada reutiliza esa misma memoria, con lo que haya quedado dentro.

**Consecuencia directa:** devolver una referencia o un puntero a una variable
local es devolver la dirección de un marco que ya no existe.

## 1.3 Argumento y parámetro no son lo mismo

Vale la pena fijar el vocabulario desde el principio, porque el resto de la
exposición depende de él:

- **Parámetro** (*parameter*, parámetro formal): la variable declarada en la
  lista de la función. Existe dentro de la función.
- **Argumento** (*argument*, parámetro real): la expresión que se escribe en
  la llamada. Existe en el llamador.

```cpp
void f(int parametro);   // 'parametro' es el parámetro

int main() {
    int x = 5;
    f(x);                // 'x' es el argumento
    f(x + 1);            // el argumento puede ser cualquier expresión
}
```

La pregunta de todo este tema es: **¿qué relación hay entre el parámetro y el
argumento?**

- Ninguna, salvo el valor inicial copiado → **paso por valor**.
- Son el mismo objeto con dos nombres → **paso por referencia**.

## 1.4 Qué ocurre exactamente en una llamada

Para `f(x)` con `void f(int p)`:

1. Se evalúa la expresión `x`.
2. Se reserva espacio para el marco de `f`.
3. Se **inicializa** `p` copiando el valor de `x`. La norma lo describe como
   inicialización por copia del parámetro a partir del argumento.
4. Se ejecuta el cuerpo de `f` usando `p`.
5. Al terminar, se destruyen los objetos locales (y `p`) y se libera el marco.

Con `void f(int& p)` el paso 3 cambia: `p` no es un objeto nuevo, se liga al
objeto designado por `x`. En la práctica el compilador guarda la dirección de
`x`, pero eso es un detalle de implementación: la norma solo dice que `p` es
otro nombre del mismo objeto.

En arm64 (macOS, Linux, iOS) los primeros ocho argumentos enteros o de puntero
viajan en registros `x0`–`x7`, no en memoria; los demás en la pila. Es
material de cultura general y explica por qué pasar un `int` por referencia
puede ser *más lento* que pasarlo por valor: la referencia obliga a acceder a
memoria, el `int` viaja en un registro.

## 1.5 Preguntas de comprobación

1. ¿Por qué dos llamadas consecutivas a la misma función imprimen la misma
   dirección para sus variables locales?
2. Si la pila crece hacia direcciones menores, ¿qué relación hay entre
   `&local_main` y `&local` dentro de `nivel_3`?
3. ¿Qué diferencia hay entre el *ámbito* de una variable y su *duración de
   almacenamiento*?

## 1.6 Fuentes

- ISO/IEC 14882, `[basic.stc]` (duración de almacenamiento) y `[expr.call]`.
- Stroustrup, B. *The C++ Programming Language*, 4.ª ed., cap. 12 "Functions".
- Deitel & Deitel. *Cómo programar en C++*, 9.ª ed., cap. 6 "Funciones y una
  introducción a la recursividad" (pila de llamadas y registros de activación).
