# 0. Guion de la exposición · 4 horas

**Temas asignados:** paso de argumentos por valor · paso de argumentos por
referencia · arreglos y arreglos multidimensionales.

**Idea que sostiene toda la sesión:** los dos temas son el mismo tema. Pasar
un argumento es decidir *qué se copia*. Un arreglo es el caso en que la
respuesta es "ni el objeto ni un alias, sino una dirección". El bloque 8
(decaimiento) es la bisagra que los une, y conviene anunciarlo desde el
principio para que la sesión tenga un arco y no se sienta como dos clases
pegadas.

## Distribución del tiempo

| Bloque | Contenido | Min | Acumulado |
|---|---|---:|---:|
| 0 | Apertura, objetivos y repaso de funciones | 10 | 0:10 |
| 1 | Modelo de memoria y mecánica de la llamada | 15 | 0:25 |
| 2 | Paso por valor | 30 | 0:55 |
| 3 | **Práctica guiada 1** | 15 | 1:10 |
| — | *Receso* | 10 | 1:20 |
| 4 | Paso por referencia | 35 | 1:55 |
| 5 | `const`, punteros vs. referencias | 20 | 2:15 |
| 6 | **Práctica guiada 2** | 15 | 2:30 |
| — | *Receso* | 10 | 2:40 |
| 7 | Arreglos unidimensionales | 25 | 3:05 |
| 8 | Arreglos como parámetros: el decaimiento | 20 | 3:25 |
| 9 | Arreglos multidimensionales | 25 | 3:50 |
| 10 | Alternativas modernas, cierre y preguntas | 10 | 4:00 |

Los dos recesos no son opcionales: cuatro horas seguidas de C++ no se
sostienen. Si vas retrasado, el material recortable es el bloque 10 y la
segunda mitad del 5; **no** recortes las prácticas.

---

## Bloque 0 · Apertura (10 min)

- Presentación y encuadre: estos temas cierran la parte de fundamentos que
  vieron Abraham y David; a partir de aquí empieza la orientación a objetos.
- Enunciar el arco de la sesión: "vamos a responder una sola pregunta, ¿qué le
  llega realmente a una función cuando la llamas?".
- Repaso rápido de lo que ya vieron: definición de función, parámetros,
  retorno. Solo lo necesario para enlazar.
- Acuerdo de vocabulario: **parámetro** es lo declarado, **argumento** es lo
  que se escribe en la llamada. Se usará toda la sesión.

## Bloque 1 · Modelo de memoria (15 min)

**Documento:** `01-modelo-de-memoria.md` · **Ejemplo:** `01_marco_de_pila.cpp`

- Las cuatro regiones de memoria, en una diapositiva.
- El marco de pila: qué contiene y cuándo nace y muere.
- Ejecutar `exp_01_marco_de_pila` y hacer notar que las direcciones bajan al
  anidar llamadas, y que dos llamadas consecutivas reutilizan la misma zona.
- **Mensaje que debe quedar:** un parámetro es una variable local más. La
  pregunta del día es qué se guarda en esa variable.

## Bloque 2 · Paso por valor (30 min)

**Documento:** `02-paso-por-valor.md` · **Ejemplos:** `02`, `03`, `04`, `05`

1. Definición y demostración con direcciones (`exp_02_paso_por_valor`).
   Antes de ejecutar, **preguntar al grupo qué va a imprimir**. El error
   esperado es creer que el original cambia.
2. `exp_03_swap_roto`: el intercambio que no intercambia. Dejar la pregunta
   abierta: "la lógica está bien, ¿entonces qué falla?". No responder todavía;
   se resuelve en el bloque 4. Esa tensión sostiene la primera hora.
3. Qué se copia exactamente: fundamentales, estructuras, clases con memoria
   dinámica. Anticipar que los arreglos son la excepción.
4. `exp_04_costo_de_la_copia`: contar copias y medir tiempo. Es la
   diapositiva que justifica `const&`.
5. Cuándo el paso por valor **es** lo correcto (`exp_05`). Evita que el grupo
   salga con la idea equivocada de que "por valor es malo".
6. Enunciar F.16 como conclusión del bloque.

## Bloque 3 · Práctica guiada 1 (15 min)

**Archivo:** `ejercicios/practica-1-paso-de-argumentos.md`

Trabajo individual o por parejas, con el compilador abierto. Recorrer al final
las soluciones en voz alta. Si el grupo va rápido, el ejercicio 4 es el reto.

## Bloque 4 · Paso por referencia (35 min)

**Documento:** `03-paso-por-referencia.md` · **Ejemplos:** `06` a `10`

1. Qué es una referencia: alias, tres reglas, `&r == &objeto`
   (`exp_06_referencias_basico`).
2. **Cerrar el problema del bloque 2**: `exp_07_swap_por_referencia`. Mostrar
   los dos archivos lado a lado; el cuerpo es idéntico, cambian dos símbolos.
   Es el momento de mayor impacto de la sesión.
3. Comparar con la versión de C con punteros y con `std::swap`.
4. Señalar que en el punto de llamada `f(x)` se ve igual en los dos casos: la
   firma es la única fuente de información.
5. `const T&` (`exp_08_referencia_const`): no copia, no modifica y acepta
   temporales, literales y objetos `const`.
6. Riesgos: referencias colgantes (`exp_09`, ejecutar con
   `ASAN_OPTIONS=detect_stack_use_after_return=1`) y la invalidación al crecer
   un `vector`.
7. Parámetros de salida frente a valor de retorno (`exp_10`), con F.20 y F.21.

## Bloque 5 · `const`, punteros y referencias (20 min)

**Documento:** `04-punteros-vs-referencias.md` · **Ejemplos:** `11`, `12`

- Tabla comparativa referencia/puntero.
- Criterio F.60: referencia por omisión; puntero cuando "no hay argumento" sea
  válido.
- El punto que siempre se confunde: **un puntero también viaja por valor**.
- Las cuatro combinaciones de `const` con punteros y la regla de lectura de
  derecha a izquierda (`exp_12_const_y_punteros`).
- Cerrar con la **tabla de decisión** del documento 3, §3.8. Es la diapositiva
  que conviene que fotografíen.

## Bloque 6 · Práctica guiada 2 (15 min)

**Archivo:** `ejercicios/practica-2-referencias-y-const.md`

## Bloque 7 · Arreglos unidimensionales (25 min)

**Documento:** `05-arreglos-unidimensionales.md` · **Ejemplos:** `13`, `14`, `15`

1. Definición: bloque contiguo, tamaño fijo en tiempo de compilación.
2. Por qué `int v[n]` con `n` leído del usuario **no** es C++ (`[dcl.array]/1`).
3. Formas de inicialización y cálculo del tamaño (`std::size` frente a
   `sizeof(a)/sizeof(a[0])`).
4. Contigüidad: ejecutar `exp_13_arreglo_basico` y mostrar las direcciones
   separadas exactamente por `sizeof(T)`.
5. `exp_14_fuera_de_rango`: sin comprobación de límites. Ejecutarlo dos veces,
   con y sin `ASAN_OPTIONS=detect_stack_use_after_return=1`, para mostrar que
   el mismo programa a veces "funciona" y a veces aborta. Conectar con
   seguridad informática: es el origen del desbordamiento de búfer.
6. Algoritmos típicos (`exp_15`) y sus equivalentes de `<algorithm>`.

## Bloque 8 · El decaimiento (20 min)

**Documento:** `06-arreglos-como-parametros.md` · **Ejemplos:** `16`, `17`, `18`

**Este es el bloque bisagra de la exposición.** Anunciarlo como tal.

1. La pregunta: ¿un arreglo se pasa por valor o por referencia? Respuesta: ni
   una cosa ni la otra.
2. Las dos reglas de la norma, citadas: `[conv.array]/1` y `[dcl.fct]/5`.
3. `exp_16_decaimiento`: `sizeof` fuera vale 40 y dentro vale 8. Las tres
   declaraciones son la misma función.
4. La consecuencia contraintuitiva: la función **sí** puede modificar el
   arreglo del llamador, aunque parezca paso por valor.
5. Las soluciones: `T (&)[N]` con plantilla (`exp_17`) y `std::span`
   (`exp_18`), con I.13 y F.24.

## Bloque 9 · Arreglos multidimensionales (25 min)

**Documento:** `07-arreglos-multidimensionales.md` · **Ejemplos:** `19` a `23`

1. Una matriz es un arreglo de arreglos. `m[i]` es una **fila**, no un
   elemento.
2. Orden por filas y la fórmula `base + (i*C + j)*sizeof(T)`. Ejecutar
   `exp_19_matriz_basica`: los desplazamientos confirman la fórmula.
3. Pasar matrices (`exp_20`): por qué se puede omitir la primera dimensión y
   no las demás; por qué `int**` no sirve.
4. Operaciones: suma, transpuesta y producto (`exp_21`).
5. Tres dimensiones y la fórmula general (`exp_22`).
6. **Cierre fuerte del bloque:** `exp_23_orden_de_recorrido`, compilado con
   `-O2`. El mismo cálculo tarda unas 30 veces más al invertir los bucles.
   Es el mejor argumento de la sesión sobre por qué importa entender la
   disposición en memoria.

## Bloque 10 · Cierre (10 min)

**Documento:** `08-alternativas-modernas.md` · **Ejemplo:** `24`

- `std::array`, `std::vector`, `std::span` y la matriz aplanada.
- Tabla de criterio final.
- Repaso de los tres mensajes de la sesión (abajo).
- Preguntas. Tener a mano `09-errores-frecuentes-y-preguntas.md`.

---

## Los tres mensajes que deben quedar

1. **Elegir cómo se pasa un argumento es elegir qué se copia.** Por valor
   copia el objeto; por referencia no copia nada y crea un alias.
2. **Un arreglo no se copia nunca al pasarlo: decae a puntero** y pierde su
   tamaño. Por eso hay que pasar el tamaño aparte, o usar `std::span`.
3. **La memoria es contigua y por filas.** De ahí salen el índice base cero,
   la fórmula `i*C + j` y una diferencia de rendimiento de 30 veces por
   cambiar el orden de dos bucles.

## Lista de comprobación antes de exponer

- [ ] `cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug && cmake --build build`
      ejecutado y sin avisos.
- [ ] `exp_23_orden_de_recorrido` compilado aparte con `-O2` (los sanitizers
      distorsionan la medición).
- [ ] Terminal con letra grande y tema claro, probada en el proyector.
- [ ] Editor abierto con `03_swap_roto.cpp` y `07_swap_por_referencia.cpp`
      lado a lado.
- [ ] `godbolt.org` abierto en una pestaña, por si surge la pregunta sobre el
      código generado.
- [ ] Prácticas 1 y 2 impresas o compartidas.
- [ ] Cronómetro visible. El bloque 4 es el que más se alarga.
