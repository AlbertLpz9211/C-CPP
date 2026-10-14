# Tarea Integradora · Sistema de Monitoreo de Calificaciones y Estadísticas

> **Curso:** Programación en C++ · Exposición Básica: Funciones, Argumentos y Arreglos  
> **Modalidad:** Tarea individual para entregar  
> **Archivo de entrega:** `tarea_sistema_notas.cpp`  
> **Compilación exigida:** `g++ -std=c++17 -Wall -Wextra -Wpedantic tarea_sistema_notas.cpp -o tarea`

---

## 🎯 Objetivo de la Tarea

Diseñar e implementar un programa en C++ estructurado en funciones modulares que demuestre el dominio de **todos los conceptos vistos en la sesión**:

1. **Paso por valor**: cálculo numérico y transformaciones sin alterar el original.
2. **Paso por referencia (`T&`)**: modificación de variables del llamador y retorno de múltiples resultados.
3. **Paso por referencia constante (`const T&`)**: lectura eficiente de tipos sin copias innecesarias y con protección de datos.
4. **Punteros (`T*`)**: uso para opcionalidad o búsqueda con comprobación explícita de `nullptr`.
5. **Arreglos unidimensionales**: procesamiento contiguo, paso como `const T v[], int n`, algoritmos de recorrido.
6. **Arreglos bidimensionales (Matrices)**: orden Row-Major, paso a función con columnas fijas `const T m[][COLUMNAS], int filas`.
7. **Modularidad y const-correctness**: separación clara de responsabilidades y prototipos.

---

## 🏢 Contexto del Problema

Un profesor universitario necesita un sistema de terminal en C++ para procesar las calificaciones de un grupo de estudiantes a lo largo de varios parciales:

* El grupo tiene **5 estudiantes**.
* Cada estudiante cursa **3 parciales** en el cuatrimestre.
* Por tanto, las calificaciones se representan en una matriz `double calificaciones[5][3]`.

---

## 📋 Requisitos de las Funciones a Implementar

Tu código debe incluir **obligatoriamente** las siguientes funciones, respetando exactamente sus firmas y su tipo de paso de argumentos:

### 1. Inicialización y Entrada de Datos (Paso por Referencia)
```cpp
// Lee o asigna la nota de un estudiante específico en un parcial.
// Modifica la variable 'nota_alumno' directamente en memoria mediante referencia.
void actualizar_calificacion(double& nota_alumno, double nueva_nota);
```
* **Requisito técnico:** Debe usar **paso por referencia** (`double&`). Si `nueva_nota` no está entre `0.0` y `10.0`, la función no debe modificar el original y debe imprimir un mensaje de error.

### 2. Estadísticas de un Estudiante (Arreglo 1D y Referencias de Salida)
```cpp
// Recibe las 3 notas de UN solo estudiante como arreglo 1D.
// Devuelve simultáneamente: el promedio (por valor con return) y el mínimo y máximo (por referencia).
double calcular_estadisticas_alumno(const double parciales[], int num_parciales, 
                                    double& nota_min, double& nota_max);
```
* **Requisitos técnicos:**
  * El arreglo `parciales` se pasa como `const double[]` con su tamaño `int num_parciales` para evitar el decaimiento sin control de tamaño.
  * El promedio se devuelve con `return` (paso por valor).
  * `nota_min` y `nota_max` se devuelven rellenando las variables mediante **referencias de salida**.

### 3. Escala y Curva de Puntos (Paso por Valor)
```cpp
// Aplica una bonificación porcentual por desempeño.
// Recibe la nota por valor y devuelve la nueva nota calculada sin tocar el original.
double aplicar_bonificacion(double nota_original, double porcentaje_extra);
```
* **Requisito técnico:** Debe usar **paso por valor** (`double`). Demuestra que la nota original del estudiante no cambia a menos que el llamador decida reasignarla explícitamente.

### 4. Búsqueda y Punteros (Comprobación de `nullptr`)
```cpp
// Busca si algún alumno obtuvo una calificación perfecta (10.0) en el parcial indicado.
// Si lo encuentra, devuelve un PUNTERO directo a ese elemento de la matriz.
// Si nadie tiene 10.0, devuelve nullptr.
const double* buscar_calificacion_perfecta(const double matriz[][3], int filas, int parcial);
```
* **Requisitos técnicos:**
  * Recibe la matriz con su dimensión de columnas fijada (`[][3]`) y el número de filas aparte.
  * Devuelve un **puntero** (`const double*`).
  * En `main()`, el alumno debe comprobar obligatoriamente `if (ptr != nullptr)` antes de desreferenciarlo.

### 5. Reporte General de la Matriz (Matriz 2D y Referencia Constante)
```cpp
// Imprime la tabla completa de calificaciones en formato tabular.
// Recibe la matriz completa y un título descriptivo pasado por referencia constante.
void imprimir_sabana_notas(const double matriz[][3], int filas, const std::string& titulo);
```
* **Requisitos técnicos:**
  * La matriz se pasa como `const double[][3]`.
  * `titulo` se pasa como `const std::string&` (cero copias de texto, garantía de solo lectura).

---

## 💻 Función `main()` de Demostración

Tu `main()` debe estructurar una prueba completa y ordenada que evidencie el funcionamiento de cada una de las 5 funciones:

1. Declarar la matriz `double notas[5][3]` con datos iniciales de prueba.
2. Imprimir la sábana original llamando a `imprimir_sabana_notas`.
3. Usar `actualizar_calificacion` para corregir una calificación por referencia y mostrar que el cambio se reflejó en la matriz.
4. Para cada uno de los 5 alumnos, llamar a `calcular_estadisticas_alumno` e imprimir su promedio, nota mínima y máxima.
5. Aplicar una bonificación simulada del 10% a un alumno con `aplicar_bonificacion` y verificar que la nota original en la matriz no se corrompió.
6. Invocar `buscar_calificacion_perfecta`:
   - Mostrar el resultado cuando existe un 10.0 (imprimiendo la dirección de memoria y el valor con `*ptr`).
   - Mostrar el resultado cuando no existe ningún 10.0 (manejando el caso `nullptr` sin que el programa truene).

---

## 📊 Rúbrica de Evaluación (100 Puntos)

| Criterio | Puntos | Descripción |
| :--- | :---: | :--- |
| **Const-correctness y Seguridad** | 20 pts | Uso riguroso de `const` en arreglos, matrices y referencias de lectura. |
| **Paso por Referencia (`&`)** | 20 pts | Modificación correcta de variables en `actualizar_calificacion` y retorno múltiple en estadísticas. |
| **Paso por Valor** | 15 pts | Demostración de independencia de memoria en `aplicar_bonificacion`. |
| **Punteros y Verificación de `nullptr`** | 20 pts | Búsqueda con retorno de dirección y comprobación estricta de puntero nulo antes de desreferenciar. |
| **Arreglos y Matrices (Decaimiento)** | 15 pts | Correcto paso de tamaño en 1D (`v[], int n`) y fijación de columnas en 2D (`m[][3], int filas`). |
| **Compilación Limpia y Formato** | 10 pts | Cero advertencias con `-Wall -Wextra -Wpedantic`. Código ordenado con comentarios claros. |

---

## 🚀 Entrega

* Sube tu archivo fuente único `tarea_sistema_notas.cpp`.
* En la cabecera del archivo, incluye en un comentario tu nombre completo, matrícula y la fecha de entrega.
