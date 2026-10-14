# Exposición · Paso de argumentos y arreglos en C++

Material completo para una sesión de **4 horas** de la unidad de aprendizaje
*Programación Avanzada*.

**Temas asignados:** paso de argumentos por valor · paso de argumentos por
referencia · arreglos y arreglos multidimensionales.

**Idea que sostiene la sesión:** los dos temas son el mismo. Pasar un
argumento es decidir qué se copia; un arreglo es el caso en que la respuesta
no es ni el objeto ni un alias, sino una dirección. El bloque del
*decaimiento* (documento 6) es la bisagra entre ambos.

## Contenido

| Carpeta | Qué hay |
|---|---|
| `base-conocimiento/` | Los apuntes: teoría, citas de la norma y de las guías, tablas de decisión |
| `src/` | 24 ejemplos ejecutables, numerados por bloque, con su explicación en la cabecera |
| `ejercicios/` | Tres prácticas con soluciones |
| `presentacion/` | La presentación en formato LibreOffice Impress (`.odp`) |

## Empezar por aquí

**`base-conocimiento/00-guion-de-4-horas.md`** — el guion minuto a minuto, con
la distribución de los diez bloques, qué ejecutar en cada uno y la lista de
comprobación previa.

## Base de conocimiento

| Documento | Bloque | Min |
|---|---|---:|
| [00 · Guion de 4 horas](base-conocimiento/00-guion-de-4-horas.md) | — | 240 |
| [01 · Modelo de memoria y mecánica de la llamada](base-conocimiento/01-modelo-de-memoria.md) | 1 | 15 |
| [02 · Paso de argumentos por valor](base-conocimiento/02-paso-por-valor.md) | 2 | 30 |
| [03 · Paso de argumentos por referencia](base-conocimiento/03-paso-por-referencia.md) | 4 | 35 |
| [04 · Punteros, referencias y `const`](base-conocimiento/04-punteros-vs-referencias.md) | 5 | 20 |
| [05 · Arreglos unidimensionales](base-conocimiento/05-arreglos-unidimensionales.md) | 7 | 25 |
| [06 · Arreglos como parámetros: el decaimiento](base-conocimiento/06-arreglos-como-parametros.md) | 8 | 20 |
| [07 · Arreglos multidimensionales](base-conocimiento/07-arreglos-multidimensionales.md) | 9 | 25 |
| [08 · Qué usar en lugar del arreglo crudo](base-conocimiento/08-alternativas-modernas.md) | 10 | 10 |
| [09 · Errores frecuentes y preguntas](base-conocimiento/09-errores-frecuentes-y-preguntas.md) | — | — |
| [10 · Bibliografía y fuentes](base-conocimiento/10-bibliografia.md) | — | — |

## Ejemplos de código

Cada archivo lleva en la cabecera su objetivo, el bloque al que pertenece, qué
observar al ejecutarlo y las trampas del tema. Están pensados para ejecutarse
en vivo.

| # | Archivo | Bloque | Qué demuestra |
|---:|---|---|---|
| 01 | `01_marco_de_pila.cpp` | 1 | Cada llamada abre un marco; la pila crece hacia abajo |
| 02 | `02_paso_por_valor.cpp` | 2 | El parámetro y el argumento tienen direcciones distintas |
| 03 | `03_swap_roto.cpp` | 2 | El intercambio que no intercambia |
| 04 | `04_costo_de_la_copia.cpp` | 2 | Contar copias y medir el tiempo que cuestan |
| 05 | `05_valor_cuando_conviene.cpp` | 2 | Los tres casos en que el paso por valor es correcto |
| 06 | `06_referencias_basico.cpp` | 4 | La referencia es un alias: misma dirección |
| 07 | `07_swap_por_referencia.cpp` | 4 | El mismo cuerpo, dos símbolos `&`, otro resultado |
| 08 | `08_referencia_const.cpp` | 5 | `const T&` no copia, no modifica y acepta temporales |
| 09 | `09_referencias_colgantes.cpp` | 5 | **Falla a propósito**: referencia colgante e invalidación |
| 10 | `10_salida_por_parametro.cpp` | 4 | Parámetros de salida frente a valor de retorno |
| 11 | `11_punteros_vs_referencias.cpp` | 5 | Cuándo usar cada uno; el puntero también viaja por valor |
| 12 | `12_const_y_punteros.cpp` | 5 | Las cuatro combinaciones de `const` |
| 13 | `13_arreglo_basico.cpp` | 7 | Declaración, inicialización, contigüidad, recorrido |
| 14 | `14_fuera_de_rango.cpp` | 7 | **Falla a propósito**: sin comprobación de límites |
| 15 | `15_arreglo_algoritmos.cpp` | 7 | Media, máximo, búsqueda y ordenamiento |
| 16 | `16_decaimiento.cpp` | 8 | `sizeof` vale 40 fuera y 8 dentro |
| 17 | `17_arreglo_por_referencia.cpp` | 8 | `T (&v)[N]` conserva el tamaño |
| 18 | `18_span.cpp` | 8 | Una firma para arreglo, `array` y `vector` |
| 19 | `19_matriz_basica.cpp` | 9 | Orden por filas y la fórmula `i*C + j` |
| 20 | `20_matriz_parametros.cpp` | 9 | Las cuatro formas de recibir una matriz |
| 21 | `21_matriz_operaciones.cpp` | 9 | Suma, transpuesta y producto |
| 22 | `22_arreglo_3d.cpp` | 9 | Tres dimensiones y la fórmula general |
| 23 | `23_orden_de_recorrido.cpp` | 9 | Invertir dos bucles cuesta 30 veces más tiempo |
| 24 | `24_alternativas_modernas.cpp` | 10 | `array`, `vector`, `span` y la matriz aplanada |

## Compilar y ejecutar

Desde la raíz del repositorio:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
./build/bin/exp_01_marco_de_pila
```

Cada archivo de `src/` genera un ejecutable `exp_<nombre>` en `build/bin/`.
Todos compilan sin ningún aviso con `-Wall -Wextra -Wpedantic -Wshadow`, y en
Debug se ejecutan con AddressSanitizer y UndefinedBehaviorSanitizer.

### Los dos ejemplos que fallan a propósito

`09_referencias_colgantes` y `14_fuera_de_rango` demuestran comportamiento
indefinido. Para que los sanitizadores lo detengan y muestren el informe:

```sh
ASAN_OPTIONS=detect_stack_use_after_return=1 ./build/bin/exp_09_referencias_colgantes
ASAN_OPTIONS=detect_stack_use_after_return=1 ./build/bin/exp_14_fuera_de_rango
```

Vale la pena ejecutarlos **también sin esa variable**: el mismo programa
termina sin quejarse. Esa es justamente la lección sobre el comportamiento
indefinido.

### La medición de rendimiento

`23_orden_de_recorrido` mide tiempos, y los sanitizadores los distorsionan.
Compilarlo aparte, optimizado:

```sh
clang++ -std=c++20 -O2 exposicion/src/23_orden_de_recorrido.cpp -o /tmp/recorrido
/tmp/recorrido
```

## Ejercicios

| Práctica | Cuándo | Contenido |
|---|---|---|
| [Práctica 1](ejercicios/practica-1-paso-de-argumentos.md) | Bloque 3, 15 min | Paso por valor |
| [Práctica 2](ejercicios/practica-2-referencias-y-const.md) | Bloque 6, 15 min | Referencias, punteros y `const` |
| [Práctica 3](ejercicios/practica-3-arreglos.md) | Para llevar | Arreglos y matrices |

Las soluciones están en `ejercicios/soluciones/` como programas completos que
compilan y se ejecutan. No forman parte de los objetivos de CMake; se compilan
a mano con la línea indicada en la cabecera de cada uno.

## Presentación

`presentacion/paso-de-argumentos-y-arreglos.odp` — LibreOffice Impress, 16:9,
con notas del orador en cada diapositiva. Las notas contienen lo que hay que
decir y qué ejemplo ejecutar en cada momento.
