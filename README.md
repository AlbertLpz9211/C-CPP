# Programación Avanzada — C / C++

Espacio de trabajo para la unidad de aprendizaje **Programación Avanzada**
de la Maestría en Ciencias e Ingeniería (Plan 2018), Unidad Académica de
Ciencias Básicas e Ingenierías, **Universidad Autónoma de Nayarit**.

## 1. Datos de la unidad de aprendizaje

| | |
|---|---|
| **Unidad de aprendizaje** | Programación Avanzada |
| **Tipo** | Especializante · Curso-Taller |
| **Semestre** | I |
| **Prerrequisito** | Programación Básica |
| **Línea de formación** | Inteligencia Artificial y Robótica |
| **Créditos** | 8 |
| **Programa elaborado/actualizado** | 14 de febrero de 2024 |

**Distribución de horas:** 40 de teoría · 30 de práctica · 58 de trabajo
independiente · **128 horas totales**, en sesiones de 4 horas por semana.

## 2. Objetivo

Al culminar la unidad, el estudiante habrá adquirido un conocimiento integral
de la programación, desde los fundamentos de la programación orientada a
objetos hasta patrones de diseño, programación concurrente y gestión eficiente
de memoria, con las habilidades teóricas y prácticas para enfrentar desafíos
en el desarrollo de software de alta complejidad.

Objetivos declarados en el programa:

1. **Habilidades avanzadas de programación** — uso efectivo de POO e
   implementación de patrones de diseño avanzados.
2. **Técnicas de desarrollo escalable** — metodologías para software robusto
   y escalable, con prácticas de codificación eficientes y sostenibles.
3. **Conceptos avanzados** — programación concurrente, gestión eficiente de
   memoria y estructuras de datos avanzadas.

## 3. Contenido temático

### 1. Introducción
- 1.1 Paradigma de la programación orientada a objetos y visual
- 1.2 Lenguajes de programación orientada a objetos y visual
- 1.3 Elementos del modelo de objetos

### 2. Objetos y clases
- 2.1 Declaración de clases: atributos, métodos y encapsulamiento
- 2.2 Instanciación de una clase
- 2.3 Referencia al objeto actual
- 2.4 Métodos: declaración, mensajes, paso de parámetros, retorno de valores
- 2.5 Constructores y destructores: declaración, uso y aplicaciones
- 2.6 Sobrecarga de métodos
- 2.7 Sobrecarga de operadores

### 3. Herencia
- 3.1 Definición: clase base, clase derivada
- 3.2 Clases base públicas, protegidas y privadas
- 3.3 Referencia al objeto de la clase base
- 3.4 Constructores y destructores en clases derivadas

### 4. Polimorfismo
- 4.1 Definición
- 4.2 Clases abstractas: definición, métodos abstractos, implementación y
  modelado de clases abstractas
- 4.3 Reutilización de código
- 4.4 Tipos de excepciones
- 4.5 Gestión de excepciones: manejo y lanzamiento de excepciones

### 5. Programación visual
- 5.1 Objetos, controles y componentes
- 5.2 Entornos de desarrollo
- 5.3 Programación orientada a eventos
- 5.4 Control de eventos
- 5.5 Cajas de diálogo

## 4. Evaluación

| Rubro | Peso |
|---|---:|
| Exposiciones | 20% |
| Desarrollo de programas | 30% |
| Exámenes | 20% |
| Proyecto integrador | 30% |

**Criterios de acreditación:** calificación mínima de 80/100, entrega del 100%
de las actividades de aprendizaje y asistencia mínima del 90% de las clases.

**Evidencias de aprendizaje:** algoritmos de POO, interfaces de programación
visual, examen escrito y proyecto integrador.

## 5. Entorno de desarrollo

Configurado para macOS (Apple Silicon) con Apple clang: **C17** y **C++20**,
compilando con `-Wall -Wextra -Wpedantic`.

### Compilar con CMake
```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
./build/hola_c
./build/hola_cpp
```

### Desde VS Code
- **⇧⌘B** → compila el archivo abierto (`clang`/`clang++` con `-g`) en `build/`.
- **F5** → compila y depura el archivo abierto con LLDB.
- Paleta (**⇧⌘P**) → *CMake: Configure* / *CMake: Build* para todo el proyecto.

Extensiones requeridas (declaradas en `.vscode/extensions.json`):
`ms-vscode.cpptools`, `ms-vscode.cmake-tools`, `twxs.cmake`.

## 6. Estructura del repositorio

```
.
├── CMakeLists.txt      objetivos de compilación (C17 / C++20)
├── src/                código fuente de prácticas y ejercicios
├── include/            cabeceras propias
├── build/              salida de compilación (ignorada)
├── fuentes-curso/      programa y material del curso (ignorado)
└── .vscode/            tareas, depuración e IntelliSense
```

Convención sugerida para las prácticas: nombrar los archivos por unidad,
por ejemplo `src/u2_clases.cpp`, `src/u3_herencia.cpp`, `src/u4_polimorfismo.cpp`,
y registrar cada uno como `add_executable` en `CMakeLists.txt`.

## 7. Acervos de consulta

**Básicos**
- Taylor, David. *Object Oriented Information Systems: Planning and Implementation*. Wiley, 1992.
- Larman, Craig. *UML y patrones: introducción al análisis y diseño orientado a objetos*. Prentice Hall, 1999.
- Winblad, Ann L.; Edwards, Samuel R. *Software orientado a objetos*. Addison-Wesley / Díaz de Santos, 1993.
- Deitel, Paul; Deitel, Harvey. *Cómo programar en C++*. Pearson, 2014.
- Deitel, Paul; Deitel, Harvey. *Intro to Python for Computer Science and Data Science*. Pearson, 2020.
- Cuevas Álvarez, Alberto. *Aplicaciones gráficas en Python*. Ra-Ma, 2018.

**Complementarios**
- Matthes, Eric. *Curso intensivo de Python*. Anaya Multimedia, 2021.
- Ramírez Jiménez, Óscar. *Python a fondo*. Marcombo, 2021.
