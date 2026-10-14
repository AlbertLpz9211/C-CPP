# Exposición Básica · Paso de Argumentos y Arreglos en C++

Material completo para una sesión de **4 horas** de fundamentos prácticos de programación en C++.

**Temas cubiertos:**
1. Anatomía de funciones (declaración, definición, prototipos, void vs retorno, ámbito).
2. Mecánica de la memoria y la pila (marcos de llamada, direcciones contiguas).
3. Paso de argumentos por valor (copia de variables, `swap_roto`, cuándo usar valor).
4. Paso de argumentos por referencia (alias, `swap` correcto, parámetros de salida, `const T&`).
5. Punteros básicos (`*` y `&`, comparativa valor vs referencia vs puntero).
6. Arreglos unidimensionales (bloques contiguos, recorridos, algoritmos, peligro fuera de rango).
7. Arreglos a funciones (decaimiento a puntero, pérdida de `sizeof`, paso de tamaño obligatorio).
8. Arreglos multidimensionales (matrices, almacenamiento Row-Major, fórmula `i*COLUMNAS + j`, por qué `[][COLUMNAS]` es obligatorio).
9. Síntesis integradora y árbol de decisiones de diseño de firmas.

---

## 📂 Estructura del Directorio

| Carpeta / Archivo | Descripción |
| :--- | :--- |
| [`src/`](./src/) | **20 programas ejecutables en C++17** diseñados para demostraciones en vivo. |
| [`presentacion/`](./presentacion/) | Diapositivas profesionales en **PDF**, **ODP** (LibreOffice Impress) y **PPTX** (PowerPoint), con notas del orador en cada lámina. |
| [`ejercicios/`](./ejercicios/) | 3 prácticas guiadas en clase y la [**Tarea Integradora**](./ejercicios/tarea-integradora.md) con su [solución](./ejercicios/soluciones/solucion-tarea-integradora.cpp). |
| [`base-conocimiento/`](./base-conocimiento/) | Apuntes teóricos detallados, citas de la norma ISO de C++ y guías de estudio. |
| [`CMakeLists.txt`](./CMakeLists.txt) | Configuración CMake autónoma con `-Wall -Wextra -Wpedantic` y sanitizadores AddressSanitizer/UBSan. |

---

## 🎯 Diapositivas de la Presentación

Ubicadas en [`presentacion/`](./presentacion/):
* [**`paso-de-argumentos-y-arreglos-basico.pdf`**](./presentacion/paso-de-argumentos-y-arreglos-basico.pdf) — Diapositivas listas para proyectar en PDF.
* [**`paso-de-argumentos-y-arreglos-basico.odp`**](./presentacion/paso-de-argumentos-y-arreglos-basico.odp) — Presentación editable para LibreOffice Impress (con consola del presentador y notas del orador).
* [**`paso-de-argumentos-y-arreglos-basico.pptx`**](./presentacion/paso-de-argumentos-y-arreglos-basico.pptx) — Archivo editable para Microsoft PowerPoint.
* [`generar_presentacion.py`](./presentacion/generar_presentacion.py) — Script generador reproducible en Python con `slide_kit.py`.

---

## ⚙️ Compilación y Ejecución de los Ejemplos

Desde este directorio:

```bash
# 1. Configurar el proyecto con CMake en modo Debug
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug

# 2. Compilar los 20 ejecutables
cmake --build build

# 3. Ejecutar cualquier ejemplo demostrativo
./build/bin/bas_01_funcion_basica
./build/bin/bas_06_paso_por_valor
./build/bin/bas_10_swap_por_referencia
./build/bin/bas_17_arreglo_a_funcion
./build/bin/bas_20_repaso_final
```
