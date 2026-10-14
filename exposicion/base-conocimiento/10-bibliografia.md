# 10. Bibliografía y fuentes

## 10.1 Normativas

- **ISO/IEC 14882:2020**, *Programming languages — C++*. Secciones citadas en
  esta base de conocimiento: `[dcl.array]` (declaración de arreglos),
  `[conv.array]` (conversión de arreglo a puntero), `[dcl.fct]` (ajuste de
  parámetros), `[dcl.ref]` (referencias), `[basic.stc]` (duración de
  almacenamiento), `[class.temporary]` (temporales), `[views.span]`.
- **Borrador de trabajo del estándar**, consultable libremente en
  <https://eel.is/c++draft/>. Es la referencia práctica: el texto normativo
  con enlaces por párrafo.

## 10.2 Guías de estilo

- **C++ Core Guidelines**, Bjarne Stroustrup y Herb Sutter (eds.).
  <https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines>
  Reglas usadas en esta exposición:
  - F.15 *Prefer simple and conventional ways of passing information*
  - F.16 *For "in" parameters, pass cheaply-copied types by value and others by reference to const*
  - F.17 *For "in-out" parameters, pass by reference to non-const*
  - F.20 *For "out" output values, prefer return values to output parameters*
  - F.21 *To return multiple "out" values, prefer returning a struct*
  - F.24 *Use a span\<T\> or a span_p\<T\> to designate a half-open sequence*
  - F.60 *Prefer T\* over T& when "no argument" is a valid option*
  - I.11 *Never transfer ownership by a raw pointer (T\*) or reference (T&)*
  - I.13 *Do not pass an array as a single pointer*

## 10.3 Libros

**De referencia del curso**

- Deitel, P. y Deitel, H. *Cómo programar en C++*, 9.ª ed. Pearson.
  Capítulo 6 (funciones y paso de argumentos), capítulo 7 (arreglos, `array`
  y `vector`) y capítulo 8 (apuntadores y su relación con los arreglos). Es el
  texto básico declarado en el programa de la unidad de aprendizaje.

**Fundamentales**

- Stroustrup, B. *The C++ Programming Language*, 4.ª ed. Addison-Wesley, 2013.
  Capítulo 7, "Pointers, Arrays, and References", y capítulo 12, "Functions".
- Stroustrup, B. *A Tour of C++*, 3.ª ed. Addison-Wesley, 2022. Versión breve
  y actualizada a C++20; útil para preparar la exposición en poco tiempo.
- Lippman, S., Lajoie, J. y Moo, B. *C++ Primer*, 5.ª ed. Addison-Wesley, 2012.
  Tratamiento muy didáctico del paso de argumentos y de los arreglos.

**Buenas prácticas**

- Meyers, S. *Effective C++*, 3.ª ed. Addison-Wesley, 2005. Ítem 20: *Prefer
  pass-by-reference-to-const to pass-by-value*.
- Meyers, S. *Effective Modern C++*. O'Reilly, 2014. Paso de argumentos con
  semántica de movimiento y referencias universales.
- Sutter, H. y Alexandrescu, A. *C++ Coding Standards*. Addison-Wesley, 2004.
- Josuttis, N. *The C++ Standard Library*, 2.ª ed. Addison-Wesley, 2012.
  Referencia de `std::array`, `std::vector` y algoritmos.

**Contexto histórico y de sistemas**

- Kernighan, B. y Ritchie, D. *The C Programming Language*, 2.ª ed. Prentice
  Hall, 1988. Capítulo 5, sobre punteros y arreglos: el origen del
  decaimiento y de la aritmética de punteros que C++ heredó.
- Drepper, U. *What Every Programmer Should Know About Memory*. Red Hat, 2007.
  Explica las líneas de caché y la localidad de referencia que hacen que el
  orden de los bucles anidados cambie el rendimiento.

## 10.4 Recursos en línea

- **cppreference.com** — <https://en.cppreference.com/> Referencia técnica de
  la biblioteca y del lenguaje; más legible que la norma.
- **Compiler Explorer** — <https://godbolt.org/> Muestra el ensamblador
  generado. Excelente para demostrar en vivo la diferencia real entre pasar un
  `int` por valor y por referencia.
- **C++ Insights** — <https://cppinsights.io/> Muestra el código que el
  compilador genera realmente: constructores de copia implícitos,
  decaimiento, deducción de plantillas.
- **Documentación de AddressSanitizer** —
  <https://clang.llvm.org/docs/AddressSanitizer.html>

## 10.5 Cómo se verificó este material

Todos los ejemplos de `exposicion/src/` se compilaron y ejecutaron en macOS
sobre Apple Silicon con Apple clang 21, en modo C++20, con
`-Wall -Wextra -Wpedantic -Wshadow` y con AddressSanitizer y
UndefinedBehaviorSanitizer activos. Los 24 archivos compilan sin ningún aviso.
Las mediciones de tiempo que aparecen en la base de conocimiento se tomaron en
ese mismo equipo y son reproducibles con las instrucciones incluidas en cada
archivo.
