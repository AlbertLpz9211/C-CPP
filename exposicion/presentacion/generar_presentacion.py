#!/usr/bin/env python3
"""Genera la presentacion de la exposicion.

    python3.12 generar_presentacion.py

Produce paso-de-argumentos-y-arreglos.pptx y, si LibreOffice esta instalado,
lo convierte a .odp (formato de LibreOffice Impress), que es el entregable.

Cada diapositiva lleva notas del orador: que decir y que ejecutar.
"""

import os
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from slide_kit import Mazo  # noqa: E402

m = Mazo()

# ===========================================================================
# Apertura
# ===========================================================================
m.portada(
    "Paso de argumentos y arreglos en C++",
    "Por valor · por referencia · arreglos y arreglos multidimensionales",
    "Alberto López",
    "Programación Avanzada · Maestría en Ciencias e Ingeniería · UACBI, UAN",
    notas="Presentarse y encuadrar: estos temas cierran la parte de fundamentos "
          "que expusieron Abraham y David. A partir de aquí empieza la orientación "
          "a objetos, y todo lo que sigue (constructores, sobrecarga, herencia) "
          "depende de entender bien cómo se pasan los argumentos.")

m.vinetas(
    "Lo que vamos a ver",
    ["**Una sola pregunta** sostiene las cuatro horas: ¿qué le llega realmente a "
     "una función cuando la llamas?",
     "Tres respuestas posibles: una **copia** del dato, un **alias** del original, "
     "o una **dirección**.",
     "El paso por valor y el paso por referencia son las dos primeras.",
     "Los arreglos son la tercera, y por eso se ven en la misma sesión.",
     "Cada bloque termina con **código ejecutándose**, no con una diapositiva."],
    sub="El hilo de la sesión",
    notas="Insistir en que no son dos temas pegados: el bloque 8 (decaimiento) es "
          "la bisagra que los une. Anunciarlo aquí para que la sesión tenga arco.")

m.tabla(
    "Programa de la sesión",
    ["Bloque", "Contenido", "Min"],
    [["0", "Apertura y repaso de funciones", "10"],
     ["1", "Modelo de memoria y mecánica de la llamada", "15"],
     ["2", "Paso por valor", "30"],
     ["3", "Práctica guiada 1", "15"],
     ["", "Receso", "10"],
     ["4", "Paso por referencia", "35"],
     ["5", "const, punteros y referencias", "20"],
     ["6", "Práctica guiada 2", "15"],
     ["", "Receso", "10"],
     ["7", "Arreglos unidimensionales", "25"],
     ["8", "Arreglos como parámetros: el decaimiento", "20"],
     ["9", "Arreglos multidimensionales", "25"],
     ["10", "Alternativas modernas y cierre", "10"]],
    anchos=[1, 7, 1],
    size=13,
    notas="Dos recesos, marcados. Avisar de que habrá dos prácticas con el "
          "compilador abierto, para que traigan la computadora lista.")

m.tabla(
    "Vocabulario: parámetro y argumento",
    ["Término", "Qué es", "Dónde vive"],
    [["**Parámetro**", "la variable declarada en la lista de la función", "dentro de la función"],
     ["**Argumento**", "la expresión escrita en la llamada", "en el llamador"]],
    sub="Lo vamos a usar toda la sesión",
    pie="La pregunta del día: ¿qué relación hay entre el parámetro y el argumento?",
    anchos=[2, 6, 3],
    notas="Fijar el vocabulario ahora ahorra confusión durante cuatro horas. "
          "En español también se dice parámetro formal y parámetro real, pero "
          "conviene usar parámetro/argumento porque es lo que aparece en la norma "
          "y en los mensajes del compilador.")

m.codigo(
    "Parámetro y argumento",
    r"""
void f(int parametro);        // 'parametro' es el parámetro

int main() {
    int x = 5;

    f(x);                     // 'x' es el argumento
    f(x + 1);                 // el argumento puede ser cualquier expresión
    f(42);                    // ...incluso un literal
}
""",
    pie="Dos respuestas posibles: ninguna relación salvo el valor copiado, o el mismo objeto con dos nombres.",
    notas="Leer las tres llamadas en voz alta. Señalar que el argumento no tiene "
          "por qué ser una variable: puede ser cualquier expresión que produzca un valor.")

# ===========================================================================
# Bloque 1 - Modelo de memoria
# ===========================================================================
m.seccion("1", "Modelo de memoria", "15 minutos",
          ["Dónde vive cada cosa", "El marco de pila", "Qué ocurre exactamente en una llamada"],
          notas="Sin este bloque, 'por valor' y 'por referencia' se memorizan como "
                "una regla arbitraria. Con él, se deducen solas. No alargarlo: 15 minutos.")

m.tabla(
    "Las cuatro regiones de memoria",
    ["Región", "Duración", "Qué contiene", "Quién la administra"],
    [["Código", "estática", "las instrucciones compiladas", "el cargador del sistema"],
     ["Datos estáticos", "estática", "globales, `static`, literales de cadena", "el compilador"],
     ["**Pila**", "**automática**", "**parámetros, variables locales**", "**el compilador**"],
     ["Montón", "dinámica", "`new`, y el interior de `vector` y `string`", "el programador o un contenedor"]],
    anchos=[2, 2, 4, 3],
    size=13,
    pie="Todo lo declarado dentro de una función sin static tiene duración automática: nace y muere con su ámbito.",
    notas="La fila de la pila es la que importa hoy. La frase 'nace al llegar a su "
          "declaración y muere al salir de su ámbito' es la causa de la mitad de "
          "los errores del tema, incluidas las referencias colgantes.")

m.codigo(
    "El marco de pila",
    r"""
Direcciones altas
┌───────────────────────────────┐
│  marco de main                │   local_main
├───────────────────────────────┤
│  marco de nivel_1             │   profundidad, local
├───────────────────────────────┤
│  marco de nivel_2             │   profundidad, local
├───────────────────────────────┤
│  marco de nivel_3             │   profundidad, local   <- cima
└───────────────────────────────┘
Direcciones bajas
""",
    sub="Cada llamada abre uno; al volver, se descarta",
    pie="En arm64 y x86-64 la pila crece hacia direcciones menores.",
    size=15,
    notas="Cada marco contiene la dirección de retorno, los parámetros, las "
          "variables locales y los registros a preservar. Al volver no se borra "
          "nada: solo se mueve el puntero de pila, y la siguiente llamada reutiliza "
          "esa memoria con lo que haya quedado dentro. De ahí sale el problema de "
          "las referencias colgantes que veremos en el bloque 5.")

m.vinetas(
    "Qué ocurre al llamar a f(x)",
    ["Se evalúa la expresión `x`.",
     "Se reserva espacio para el marco de `f`.",
     "**Se inicializa el parámetro** copiando el valor del argumento.",
     "Se ejecuta el cuerpo de la función.",
     "Se destruyen los objetos locales y se libera el marco.",
     "",
     "Con un parámetro `int&` cambia solo el paso 3: el parámetro **no es un "
     "objeto nuevo**, se liga al objeto del llamador."],
    sub="void f(int p) — paso por valor",
    notas="El paso 3 es todo el tema de hoy. Con referencia, el compilador guarda "
          "en la práctica la dirección, pero eso es un detalle de implementación: "
          "la norma solo dice que el parámetro es otro nombre del mismo objeto.")

m.demo(
    "01_marco_de_pila.cpp",
    "./build/bin/exp_01_marco_de_pila",
    ["Las direcciones **bajan** conforme se anidan las llamadas.",
     "Dos cadenas de llamadas consecutivas reutilizan **la misma memoria**.",
     "Un parámetro es una variable local más del marco."],
    notas="Ejecutarlo dos veces para que vean que las direcciones cambian entre "
          "ejecuciones (ASLR) pero la relación entre ellas no. Lo importante es la "
          "relación, no el valor.")

# ===========================================================================
# Bloque 2 - Paso por valor
# ===========================================================================
m.seccion("2", "Paso de argumentos por valor", "30 minutos",
          ["Qué se copia exactamente", "El intercambio que no intercambia",
           "Cuánto cuesta una copia", "Cuándo es la opción correcta"],
          notas="Bloque largo. El clímax es el swap roto: dejar la pregunta abierta "
                "y no responderla hasta el bloque 4.")

m.mensaje("En el paso por valor, el parámetro es un **objeto independiente** "
          "que se inicializa copiando el valor del argumento.",
          "A partir de ahí, no existe ninguna relación entre los dos.",
          notas="Leerla despacio. Es la definición que hay que retener.")

m.codigo(
    "Paso por valor",
    r"""
void intenta_modificar(int copia) {
    std::cout << &copia;      // dirección A
    copia = 999;              // modifica SOLO la variable local
}

int main() {
    int original = 42;
    std::cout << &original;   // dirección B, distinta de A

    intenta_modificar(original);

    std::cout << original;    // sigue valiendo 42
}
""",
    resaltar=(2, 3),
    pie="Direcciones distintas significan objetos distintos. Solo se copió el valor inicial.",
    notas="Antes de ejecutar, PREGUNTAR al grupo qué va a imprimir. El error "
          "esperado es creer que 'original' cambia a 999. La demostración que "
          "convence no es la explicación, son las direcciones.")

m.demo(
    "02_paso_por_valor.cpp",
    "./build/bin/exp_02_paso_por_valor",
    ["Preguntar **antes** de ejecutar qué va a imprimir.",
     "Comparar las direcciones de dentro y de fuera.",
     "Repetirlo con una estructura: se copia campo por campo."],
    notas="Pedir que levanten la mano quienes creen que imprime 999. Sirve para "
          "medir el punto de partida del grupo.")

m.tabla(
    "Qué se copia exactamente",
    ["Tipo del parámetro", "Qué ocurre", "Coste"],
    [["`int`, `double`, `char`, punteros", "se copian los bits", "uno o dos ciclos"],
     ["estructura o clase", "se invoca el **constructor de copia**", "depende de la clase"],
     ["`std::string`, `std::vector`", "copia **profunda** de todo el contenido", "proporcional al tamaño"],
     ["**arreglo crudo**", "**no se copia**: decae a puntero", "constante"]],
    anchos=[4, 5, 3],
    size=14,
    pie="La última fila es la excepción del lenguaje. Es el tema del bloque 8.",
    notas="Anticipar aquí la excepción de los arreglos crea expectativa y prepara "
          "la bisagra de la sesión. Un vector de un millón de enteros ocupa 24 "
          "bytes como objeto, pero copiarlo copia cuatro megabytes.")

m.codigo(
    "El intercambio que no intercambia",
    r"""
void intercambia_mal(int a, int b) {
    int temporal = a;
    a = b;
    b = temporal;
    // aquí a y b sí están intercambiadas
}                             // ...y aquí mueren las dos

int main() {
    int x = 1, y = 2;
    intercambia_mal(x, y);
    std::cout << x << y;      // imprime 1 2
}
""",
    sub="La lógica es correcta. El resultado es nulo.",
    resaltar=(5, 6),
    pie="¿Entonces qué falla?",
    notas="NO responder todavía. Esta pregunta abierta sostiene la primera hora y "
          "se cierra en el bloque 4 con el mismo cuerpo de función y dos símbolos "
          "de más. Dejarla escrita en el pizarrón si hay.")

m.demo(
    "03_swap_roto.cpp",
    "./build/bin/exp_03_swap_roto",
    ["La función **sí** intercambia: sus copias.",
     "Al terminar, el marco se libera y las copias desaparecen.",
     "Para modificar los argumentos, la función necesita saber **dónde viven**."],
    notas="Cerrar el bloque con la pregunta en el aire. Anunciar que la respuesta "
          "llega después del receso.")

m.vinetas(
    "Ventajas del paso por valor",
    ["**Aísla al llamador.** La función no puede alterar sus datos.",
     "**Sin problemas de vida.** El parámetro es dueño de su valor; no puede quedar colgante.",
     "**Sin aliasing.** El compilador sabe que no comparte memoria con nada y optimiza mejor.",
     "**Rápido para tipos pequeños.** Un `int` viaja en un registro; una referencia obliga a leer memoria."],
    notas="El cuarto punto sorprende a mucha gente: pasar un int por referencia "
          "suele ser más lento que copiarlo.")

m.vinetas(
    "Límites del paso por valor",
    ["**No puede modificar el argumento.** El caso canónico es el intercambio.",
     "**Cuesta.** Para objetos grandes, la copia se paga en tiempo y memoria.",
     "**No admite tipos no copiables**, como `std::unique_ptr` o `std::mutex`.",
     "**Trunca el polimorfismo** (*object slicing*): al pasar un objeto derivado "
     "por valor en un parámetro de la clase base, la parte derivada se pierde."],
    notas="El slicing es un error silencioso: compila, se ejecuta y da resultados "
          "incorrectos. Mencionarlo aquí y volver a él cuando vean herencia.")

m.codigo(
    "Object slicing",
    r"""
struct Figura  { virtual double area() const { return 0; } };
struct Circulo : Figura { double r; double area() const override; };

void dibuja(Figura f);          // MAL: recibe solo la parte 'Figura'
void dibuja(const Figura& f);   // BIEN: conserva el tipo dinámico

Circulo c;
dibuja(c);   // con la primera firma, el área siempre da 0
""",
    resaltar=(3, 4),
    pie="Compila, se ejecuta y da un resultado incorrecto. Sin ningún aviso.",
    notas="Este ejemplo enlaza con el tema de polimorfismo del programa del curso. "
          "Es una buena forma de mostrar que el tema de hoy no se agota hoy.")

m.demo(
    "04_costo_de_la_copia.cpp",
    "./build/bin/exp_04_costo_de_la_copia",
    ["Una clase instrumentada **anuncia cada copia** que ocurre.",
     "Veinte llamadas con un vector de 5 millones de enteros, por valor y por `const&`.",
     "La copia se paga aunque la función solo lea los datos."],
    notas="Esta es la diapositiva que justifica const&. Si el tiempo aprieta, "
          "basta con la primera parte (contar copias).")

m.vinetas(
    "Cuándo el paso por valor SÍ es lo correcto",
    ["**Tipos baratos de copiar.** Si no supera dos o tres punteros (16–24 bytes "
     "en 64 bits) y la copia es trivial, por valor.",
     "**Cuando la función necesita su propia copia de trabajo.** Si de todos modos "
     "vas a copiar dentro, pide la copia en el parámetro.",
     "**Parámetros sumidero.** Cuando la función se queda con el dato: "
     "`Usuario(std::string n) : nombre_(std::move(n)) {}`"],
    sub="Que no se vayan con la idea de que 'por valor es malo'",
    notas="El segundo caso además permite al compilador eliminar copias (copy "
          "elision). El tercero es semántica de movimiento: mencionarlo sin "
          "profundizar, es tema de otra sesión.")

m.mensaje("F.16 — *For \"in\" parameters, pass cheaply-copied types by value "
          "and others by reference to const*",
          "C++ Core Guidelines · Bjarne Stroustrup y Herb Sutter (eds.)",
          size=28,
          notas="Es la regla que resume el bloque. Se cita en inglés porque así "
                "aparece en la guía y así la van a encontrar al buscarla.")

m.practica(
    "Práctica 1 · Paso por valor",
    "ejercicios/practica-1-paso-de-argumentos.md",
    ["Predecir la salida de un intercambio aritmético por valor.",
     "Encontrar y corregir el error en una función que debería duplicar.",
     "Elegir la forma de paso para cinco funciones y justificarla.",
     "Reto: contar cuántas veces se ejecuta el constructor de copia."],
    "15 minutos · individual o por parejas, con el compilador abierto",
    notas="Recorrer las soluciones en voz alta al final. Si el grupo va rápido, "
          "el ejercicio 4 es el reto. Después de esto, receso de 10 minutos.")

# ===========================================================================
# Bloque 4 - Paso por referencia
# ===========================================================================
m.seccion("4", "Paso de argumentos por referencia", "35 minutos",
          ["La referencia es un alias", "El intercambio que sí funciona",
           "const T&: leer sin copiar", "Referencias colgantes"],
          notas="Bloque más largo de la sesión y el de mayor impacto. Empezar "
                "recordando la pregunta abierta del bloque 2.")

m.vinetas(
    "Qué es una referencia",
    ["Una referencia `T&` es **otro nombre para un objeto que ya existe**.",
     "",
     (1, "**Debe inicializarse** al declararse. No existe una referencia vacía."),
     (1, "**No se puede reapuntar.** Queda ligada a ese objeto de por vida."),
     (1, "**No puede ser nula.** Siempre hay un objeto detrás."),
     "",
     "La comprobación cabe en una línea: `&referencia == &objeto` es **verdadero**."],
    sub="No es un objeto nuevo. No es un puntero con azúcar sintáctico.",
    notas="Las tres reglas se derivan de la definición: si es otro nombre de algo, "
          "tiene que haber algo que nombrar desde el principio, y no puede pasar a "
          "nombrar otra cosa.")

m.codigo(
    "El alias, en código",
    r"""
int valor = 42;
int& alias = valor;        // 'alias' NO es un objeto nuevo

&valor == &alias           // true: misma dirección, mismo objeto

alias = 7;                 // valor ahora vale 7

int otro = 100;
alias = otro;              // asigna el VALOR de otro a valor;
                           // alias SIGUE siendo alias de valor
""",
    resaltar=(3,),
    pie="Escribir en el alias es escribir en el objeto original.",
    notas="La línea 'alias = otro' es la que más confunde. Insistir: una referencia "
          "no se reapunta nunca, ni con asignación ni de ninguna otra forma.")

m.demo(
    "06_referencias_basico.cpp",
    "./build/bin/exp_06_referencias_basico",
    ["`&valor == &alias` da verdadero: es el mismo objeto.",
     "Mostrar las dos declaraciones comentadas que **no compilan**.",
     "Un parámetro `int&` modifica el objeto del llamador."],
    notas="Descomentar en vivo 'int& sin_inicializar;' para que vean el error del "
          "compilador: 'declaration of reference variable requires an initializer'.")

m.dos_codigos(
    "El mismo cuerpo, dos símbolos de diferencia",
    "No funciona",
    r"""
void intercambia_mal(int a, int b)
{
    int temporal = a;
    a = b;
    b = temporal;
}

int x = 1, y = 2;
intercambia_mal(x, y);
// x=1  y=2
""",
    "Funciona",
    r"""
void intercambia(int& a, int& b)
{
    int temporal = a;
    a = b;
    b = temporal;
}

int x = 1, y = 2;
intercambia(x, y);
// x=2  y=1
""",
    sub="La respuesta a la pregunta del bloque 2",
    pie="El cuerpo es idéntico. Cambian dos símbolos & en la lista de parámetros.",
    notas="ESTE es el momento de mayor impacto de la sesión. Mostrar los dos "
          "archivos lado a lado en el editor, no solo en la diapositiva. Hacer una "
          "pausa antes de explicar.")

m.demo(
    "07_swap_por_referencia.cpp",
    "./build/bin/exp_07_swap_por_referencia",
    ["La versión con referencias, la versión de C con punteros y `std::swap`.",
     "Las tres hacen lo mismo; cambia la sintaxis y las garantías.",
     "Con punteros hay que comprobar `nullptr`; con referencias, no."],
    notas="Señalar que la versión de C obliga a escribir intercambia(&x, &y): la "
          "llamada avisa visualmente. En C++ la llamada se ve igual que la del "
          "paso por valor. Es el tema de la siguiente diapositiva.")

m.mensaje("En el punto de llamada, `f(x)` se ve **exactamente igual** con paso "
          "por valor y con paso por referencia.",
          "La declaración de la función es la única fuente de información. Por eso hay que leer las firmas.",
          size=30,
          notas="Es una diferencia importante frente a C, donde f(&x) avisa a la "
                "vista. Es también el argumento a favor de poner const siempre que "
                "el parámetro no deba cambiar.")

m.vinetas(
    "Las tres formas de parámetro por referencia",
    [(1, "`const T&` — referencia a const: **entrada**, sin copiar. La más común de C++."),
     (1, "`T&` — referencia no const: **entrada y salida**. Modifica el argumento."),
     (1, "`T&&` — referencia a rvalue: **sumidero**, se va a mover."),
     "",
     "`T&&` pertenece a la semántica de movimiento y queda fuera de esta sesión. "
     "Basta con saber que existe."],
    notas="No abrir el tema de rvalue references: es una sesión entera. Solo "
          "nombrarlo para que no les sorprenda al leer código.")

m.codigo(
    "const T&: no copia y no modifica",
    r"""
std::size_t longitud(const std::string& texto) {
    // texto[0] = 'X';   // error: cannot assign to variable
    return texto.size(); //        with const-qualified type
}

void agrega_saludo(std::string& texto) {   // sin const: SÍ modifica
    texto = "Hola, " + texto;
}
""",
    pie="const no es cosmética: es la única documentación que el compilador verifica.",
    notas="Escribir const cuando el parámetro no debe cambiar convierte una "
          "intención en una garantía comprobada en compilación.")

m.tabla(
    "const T& acepta argumentos que T& rechaza",
    ["Llamada", "`const std::string&`", "`std::string&`"],
    [["`f(nombre)` — un lvalue", "sí", "sí"],
     ["`f(\"literal\")` — conversión", "sí", "**no**"],
     ["`f(std::string{\"t\"})` — temporal", "sí", "**no**"],
     ["`f(objeto_const)`", "sí", "**no**"]],
    anchos=[6, 3, 3],
    pie="Permitir modificar un temporal que va a morir en la siguiente línea casi siempre es un error. El lenguaje lo prohíbe.",
    notas="Además, un const& ligado a un temporal EXTIENDE la vida de ese temporal "
          "mientras la referencia siga viva. Es lo que permite escribir "
          "promedio({30.0, 40.0}) sin nombrar el vector.")

m.demo(
    "08_referencia_const.cpp",
    "./build/bin/exp_08_referencia_const",
    ["`const&` no copia, no modifica y acepta temporales y objetos `const`.",
     "Descomentar en vivo las dos llamadas que **no compilan**.",
     "Vida extendida de un temporal ligado a `const&`."],
    notas="Los mensajes de error de clang aquí son muy claros: 'candidate function "
          "not viable: expects an lvalue' y 'binding value of type const "
          "std::string to reference drops qualifiers'.")

m.mensaje("Una referencia **no es dueña** del objeto al que apunta.",
          "Si el objeto muere antes que la referencia, usarla es comportamiento indefinido.",
          notas="Aquí empieza la parte de riesgos. Es el precio de no copiar.")

m.dos_codigos(
    "Las dos causas de referencia colgante",
    "A · devolver una local",
    r"""
int& colgante() {
    int local = 1234;
    return local;      // muere aquí
}

int& r = colgante();
std::cout << r;        // basura

// El compilador SÍ avisa:
// warning: reference to stack
// memory ... returned
""",
    "B · el contenedor crece",
    r"""
std::vector<int> v{10, 20, 30};
int& primero = v[0];

for (int i = 0; i < 1000; ++i)
    v.push_back(i);    // realoja

std::cout << primero;  // colgante

// El compilador NO avisa.
// AddressSanitizer sí.
""",
    pie="Solución práctica: no devuelvas referencias a locales, y guarda el ÍNDICE, no la referencia.",
    notas="El caso B es el más peligroso porque no hay ningún aviso. Cuando un "
          "vector supera su capacidad, reserva un bloque nuevo, mueve los "
          "elementos y libera el anterior: toda referencia, puntero o iterador al "
          "contenido queda invalidado.")

m.demo(
    "09_referencias_colgantes.cpp",
    "ASAN_OPTIONS=detect_stack_use_after_return=1 \\\n    ./build/bin/exp_09_referencias_colgantes",
    ["Ejecutarlo **primero sin** la variable de entorno: termina sin quejarse.",
     "Ejecutarlo **después con** ella: AddressSanitizer aborta y señala la línea.",
     "El mismo programa, dos comportamientos. Eso es comportamiento indefinido."],
    notas="Este contraste es la mejor explicación de qué significa 'comportamiento "
          "indefinido': no es que falle, es que no hay ninguna garantía. Ejecutar "
          "las dos versiones seguidas.")

m.dos_codigos(
    "Devolver resultados: dos estilos",
    "Parámetros de salida",
    r"""
void estadisticas(
    const std::vector<double>& d,
    double& minimo,
    double& maximo,
    double& media);

double mn = 0, mx = 0, md = 0;
estadisticas(datos, mn, mx, md);

// ¿cuáles entran y cuáles salen?
// hay que ir a ver la firma
""",
    "Valor de retorno (preferido)",
    r"""
struct Estadisticas {
    double minimo, maximo, media;
};

Estadisticas estadisticas(
    const std::vector<double>& d);

auto [mn, mx, md] =
    estadisticas(datos);

// se lee sola
""",
    sub="F.20 y F.21 de las Core Guidelines",
    pie="El valor de retorno no se puede ignorar por accidente y no obliga a declarar variables vacías antes.",
    notas="El enlace estructurado (auto [a, b, c]) es de C++17 y está disponible en "
          "el estándar del curso. F.20: prefer return values to output parameters. "
          "F.21: to return multiple out values, prefer returning a struct.")

m.demo(
    "10_salida_por_parametro.cpp",
    "./build/bin/exp_10_salida_por_parametro",
    ["Los tres estilos: parámetros de salida, `struct` de retorno y entrada/salida real.",
     "`T&` sigue siendo correcto cuando el parámetro **entra con un valor y sale modificado**.",
     "Ejemplo: normalizar un vector en el sitio."],
    notas="Aclarar que F.20 no prohíbe T&: lo que dice es que si el parámetro SOLO "
          "sale, mejor devolverlo. Si entra y sale, T& es lo correcto.")

# ===========================================================================
# Bloque 5 - const, punteros y referencias
# ===========================================================================
m.seccion("5", "const, punteros y referencias", "20 minutos",
          ["Cuándo usar cada uno", "El puntero también viaja por valor",
           "Dónde va el const", "Tabla de decisión"],
          notas="Bloque de consolidación. Termina con la diapositiva que conviene "
                "que fotografíen.")

m.tabla(
    "Referencia y puntero",
    ["", "`T&` referencia", "`T*` puntero"],
    [["Puede ser nulo", "no", "sí (`nullptr`)"],
     ["Se puede reapuntar", "no", "sí"],
     ["Debe inicializarse", "sí", "no"],
     ["En la llamada", "`f(x)`", "`f(&x)`"],
     ["Al usarlo", "`x`", "`*p`  `p->`"],
     ["Aritmética", "no", "sí (`p + 1`)"]],
    anchos=[4, 4, 4],
    pie="No son intercambiables: se diferencian en lo que PERMITEN.",
    notas="Recorrer la tabla de arriba abajo. Cada fila es una decisión de diseño "
          "que el lenguaje toma por ti al elegir una u otra.")

m.mensaje("F.60 — *Prefer `T*` over `T&` when \"no argument\" is a valid option*",
          "Traducido: referencia por omisión; puntero cuando la ausencia de dato sea un caso legítimo.",
          size=28,
          notas="Un T* obliga a comprobar nullptr; un T& te ahorra esa comprobación "
                "porque el lenguaje garantiza que hay objeto. Menos comprobaciones, "
                "menos código, menos caminos que probar.")

m.codigo(
    "El punto que siempre se confunde",
    r"""
void f(int* p) {
    *p = 10;            // SÍ afecta al objeto del llamador
    p = nullptr;        // NO afecta al puntero del llamador
}
""",
    sub="Un puntero también se pasa por valor",
    pie="La función recibe una COPIA de la dirección. Para cambiar el puntero del llamador hace falta int*& o int**.",
    resaltar=(1, 2),
    notas="Es exactamente la misma distinción de siempre, aplicada un nivel más "
          "arriba. Si lo entienden aquí, han entendido el tema completo.")

m.tabla(
    "Dónde va el const",
    ["Declaración", "Lectura (de derecha a izquierda)", "`*p = 5`", "`p = &otro`"],
    [["`int* p`", "puntero a int", "sí", "sí"],
     ["`const int* p`", "puntero a int **constante**", "**no**", "sí"],
     ["`int* const p`", "puntero **constante** a int", "sí", "**no**"],
     ["`const int* const p`", "puntero constante a int constante", "**no**", "**no**"]],
    anchos=[4, 6, 2, 2],
    size=13,
    pie="const int* e int const* son el mismo tipo. Con referencias no hay ambigüedad: solo const T& y T&.",
    notas="La regla de lectura de derecha a izquierda a partir del identificador "
          "resuelve todos los casos, incluidos los de tres niveles. Ejemplo en "
          "parámetros: void imprime(const int* datos, size_t n) promete no modificar.")

m.tabla(
    "Tabla de decisión",
    ["Intención", "Parámetro", "Regla"],
    [["Entrada, tipo barato de copiar", "`T`", "F.16"],
     ["Entrada, tipo caro de copiar", "`const T&`", "F.16"],
     ["Entrada y salida", "`T&`", "F.17"],
     ["Solo salida", "valor de retorno", "F.20"],
     ["Varias salidas", "`struct` de retorno", "F.21"],
     ["Puede no haber argumento", "`T*` o `std::optional`", "F.60"],
     ["Secuencia contigua", "`std::span<T>`", "F.24, I.13"]],
    anchos=[6, 4, 2],
    sub="La diapositiva que conviene fotografiar",
    notas="Decirlo explícitamente: 'esta es la que hay que guardar'. Resume las "
          "cuatro horas en siete líneas. La última fila todavía no la hemos "
          "justificado: es el bloque 8.")

m.demo(
    "11 y 12 · punteros, referencias y const",
    "./build/bin/exp_11_punteros_vs_referencias\n./build/bin/exp_12_const_y_punteros",
    ["Argumento obligatorio frente a argumento opcional.",
     "Aritmética de punteros para recorrer.",
     "Las cuatro combinaciones de `const`, con los errores comentados."],
    notas="Si el tiempo aprieta, este es el par de demostraciones recortable: la "
          "tabla anterior ya transmite lo esencial.")

m.practica(
    "Práctica 2 · Referencias, punteros y const",
    "ejercicios/practica-2-referencias-y-const.md",
    ["Escribir cuatro firmas de función a partir de su intención.",
     "Detectar dos errores de vida y decir cuál atrapa el compilador.",
     "Completar la tabla de lectura de const.",
     "Reto: la misma función con punteros y con referencias."],
    "15 minutos · por parejas",
    notas="Después de esta práctica, receso de 10 minutos. Es la mitad exacta de "
          "la sesión: hasta aquí, paso de argumentos; a partir de aquí, arreglos.")

# ===========================================================================
# Bloque 7 - Arreglos unidimensionales
# ===========================================================================
m.seccion("7", "Arreglos unidimensionales", "25 minutos",
          ["Bloque contiguo, tamaño fijo", "Índices y direcciones",
           "Sin comprobación de límites", "Algoritmos típicos"],
          notas="Segunda mitad de la sesión. Recordar el arco: seguimos "
                "respondiendo la misma pregunta, qué le llega a la función.")

m.mensaje("Un arreglo es un **bloque contiguo de N objetos del mismo tipo**, "
          "con N fijo y conocido en tiempo de compilación.",
          "Todo lo demás se deduce de esas dos propiedades: contigüidad y tamaño fijo.",
          notas="Insistir: no hay ninguna otra magia. La velocidad, el índice base "
                "cero y todas las limitaciones salen de esta frase.")

m.codigo(
    "El tamaño debe ser constante",
    r"""
int v[5];              // bien: 5 es una expresión constante

const int N = 10;
int w[N];              // bien: N es constante

int n;
std::cin >> n;
int malo[n];           // NO es C++ estándar (esto es un VLA de C99)

std::vector<int> bien(n);   // ESTA es la respuesta correcta
""",
    resaltar=(8,),
    pie="[dcl.array]/1 — el tamaño debe ser una expresión constante convertida de tipo std::size_t, mayor que cero.",
    notas="Algunos compiladores aceptan el VLA como extensión; con -Wpedantic "
          "avisan. Es una de las diferencias más visibles entre C y C++, y una "
          "pregunta frecuente de examen.")

m.tabla(
    "Formas de inicializar",
    ["Declaración", "Resultado"],
    [["`int a[5] = {10,20,30,40,50};`", "los cinco valores dados"],
     ["`int b[5] = {1,2};`", "`1 2 0 0 0` — lo que falta se pone a cero"],
     ["`int c[5] = {};`", "los cinco a cero"],
     ["`int d[] = {7,8,9};`", "tamaño deducido: 3"],
     ["`int e[3];`", "valores **indeterminados**: leerlos es comportamiento indefinido"]],
    anchos=[5, 7],
    pie="Desde C++11 se puede omitir el =:  int a[5]{10,20,30,40,50};",
    notas="La última fila es fuente de errores difíciles de reproducir: a veces "
          "sale cero por casualidad y el programa parece correcto.")

m.codigo(
    "Índices y direcciones",
    r"""
v[i]  ==  *(v + i)            // por definición del operador []

&v[i] ==  dirección_base + i * sizeof(T)
""",
    sub="Por qué los índices empiezan en cero",
    pie="El índice es un DESPLAZAMIENTO desde el inicio, no una posición ordinal. El primer elemento está a desplazamiento cero.",
    size=17,
    notas="Curiosidad que funciona bien en clase: como v[i] es *(v+i) y la suma es "
          "conmutativa, i[v] también compila y significa lo mismo. No usarlo nunca, "
          "pero explica muy bien qué es realmente el operador corchete.")

m.codigo(
    "Tamaño y recorrido",
    r"""
sizeof(a)                  // bytes que ocupa TODO el arreglo
sizeof(a) / sizeof(a[0])   // número de elementos, forma clásica
std::size(a)               // número de elementos, C++17, <iterator>

for (std::size_t i = 0; i < std::size(a); ++i)  { ... a[i] ... }

for (int valor : a)        { ... }        // C++11, sin índices
for (int& valor : a)       { valor *= 2; } // con & para modificar
""",
    resaltar=(2,),
    pie="std::size es preferible: falla al compilar si se aplica a un puntero, que es justo el error que la forma clásica no detecta.",
    notas="El for basado en rango funciona sobre un arreglo SOLO mientras el tipo "
          "conserve su tamaño. Dentro de una función que recibió el arreglo como "
          "parámetro ya no funciona. Es el anuncio del bloque 8.")

m.demo(
    "13_arreglo_basico.cpp",
    "./build/bin/exp_13_arreglo_basico",
    ["Las cinco formas de inicializar, con su resultado real.",
     "Las direcciones de los elementos, separadas exactamente por `sizeof(T)`.",
     "Recorrido clásico, por rango y por rango con referencia."],
    notas="La tabla de direcciones es la demostración de la contigüidad. Señalar "
          "que la diferencia entre &a[0] y &a[i] es siempre i*4 bytes.")

m.mensaje("Un arreglo **no comprueba sus límites**. `v[10]` en un arreglo de "
          "cinco elementos compila y se ejecuta.",
          "Lee o escribe memoria que no le pertenece. El estándar lo llama comportamiento indefinido.",
          size=30,
          notas="Conectar con seguridad informática: este es el origen histórico "
                "del desbordamiento de búfer, una de las clases de vulnerabilidad "
                "más explotadas de la historia del software. No es un detalle "
                "académico.")

m.tabla(
    "Qué sí avisa",
    ["Herramienta", "Qué detecta", "Cuándo"],
    [["`-Warray-bounds`", "índice **constante** fuera de rango", "compilación"],
     ["`array::at()` / `vector::at()`", "cualquier índice fuera de rango", "ejecución, lanza `std::out_of_range`"],
     ["AddressSanitizer", "accesos fuera de rango reales", "ejecución"],
     ["UndefinedBehaviorSanitizer", "índices fuera de rango, entre otras cosas", "ejecución"]],
    anchos=[5, 5, 5],
    size=13,
    pie="El compilador solo puede avisar de lo que puede calcular. Si el índice se conoce hasta la ejecución, no hay aviso.",
    notas="En 14_fuera_de_rango.cpp el índice se deriva de argc precisamente para "
          "demostrar ese límite: escrito como literal, clang lo detecta; calculado "
          "en ejecución, no.")

m.codigo(
    "El error de un elemento",
    r"""
for (int i = 0; i <= 5; ++i)   // MAL: recorre SEIS posiciones
for (int i = 0; i <  5; ++i)   // BIEN
""",
    sub="off by one",
    pie="El índice válido máximo es N-1. La condición correcta usa <, nunca <=.",
    size=17,
    resaltar=(0,),
    notas="Es el error más frecuente del tema y el más fácil de evitar. Repetirlo "
          "como consigna: 'menor que, nunca menor o igual'.")

m.demo(
    "14_fuera_de_rango.cpp",
    "./build/bin/exp_14_fuera_de_rango\nASAN_OPTIONS=detect_stack_use_after_return=1 ./build/bin/exp_14_fuera_de_rango",
    ["Ejecutarlo **dos veces**: sin sanitizador, termina; con él, aborta.",
     "`std::array::at()` lanza `std::out_of_range` y se puede atrapar.",
     "Los centinelas alrededor del arreglo muestran qué se corrompe."],
    notas="El contraste entre las dos ejecuciones es la mejor definición práctica "
          "de comportamiento indefinido que se puede dar en clase.")

m.vinetas(
    "Lo que un arreglo NO puede hacer",
    ["**No se puede asignar**: `a = b;` no compila.",
     "**No se puede copiar** al inicializar: `int b[5] = a;` no compila.",
     "**No se puede devolver** desde una función.",
     "**No se puede comparar**: `a == b` compara direcciones, no contenidos.",
     "**No conoce su tamaño** una vez pasado a una función.",
     "",
     "`std::array<T,N>` sí puede hacer todo eso, con el mismo rendimiento y sin "
     "sobrecosto de memoria."],
    notas="Esta lista justifica el bloque 10. Guardarla: es el argumento para "
          "usar std::array en código nuevo.")

m.demo(
    "15_arreglo_algoritmos.cpp",
    "./build/bin/exp_15_arreglo_algoritmos",
    ["Media, máximo, búsqueda lineal y ordenamiento por burbuja.",
     "Todos comparten el mismo esqueleto de recorrido.",
     "Al final, los equivalentes de `<algorithm>`: `sort`, `find`, `max_element`."],
    notas="Escribir los bucles a mano primero y mostrar la biblioteca después. El "
          "orden inverso quita la práctica que necesitan para los exámenes.")

# ===========================================================================
# Bloque 8 - Decaimiento
# ===========================================================================
m.seccion("8", "Arreglos como parámetros: el decaimiento", "20 minutos",
          ["La bisagra entre los dos temas de la sesión"],
          notas="Anunciarlo como el bloque bisagra. Aquí se responde por qué los "
                "dos temas de la exposición son en realidad uno.")

m.mensaje("¿Un arreglo se pasa por valor o por referencia?",
          "Ni una cosa ni la otra.",
          size=36,
          notas="Dejar la pregunta unos segundos. Muchos dirán 'por referencia', "
                "porque han visto que la función puede modificar el arreglo. La "
                "respuesta correcta es más interesante.")

m.codigo(
    "Las dos reglas de la norma",
    r"""
[conv.array]/1
  "Una expresión E de tipo 'arreglo de N T' puede convertirse
   a un prvalue de tipo 'puntero a T'."

[dcl.fct]/5
  "Después de determinar el tipo de cada parámetro, todo parámetro
   de tipo 'arreglo de T' se ajusta para ser 'puntero a T'."
""",
    sub="ISO/IEC 14882 — decaimiento, array-to-pointer decay",
    size=15,
    pie="La primera describe la conversión en el punto de llamada; la segunda, el ajuste del parámetro.",
    notas="Citar la norma aquí da peso a la explicación y les enseña que el "
          "estándar es consultable: eel.is/c++draft está disponible gratis y con "
          "enlace por párrafo.")

m.codigo(
    "Las tres declaraciones son la MISMA función",
    r"""
void f(int v[10]);    // el 10 se ignora por completo
void f(int v[]);
void f(int* v);       // esta es la firma real de las tres
""",
    pie="Declarar las tres en el mismo programa da error: redefinition of 'f'.",
    size=17,
    resaltar=(2,),
    notas="El número entre corchetes no reserva nada, no se comprueba y no impide "
          "pasar un arreglo de otro tamaño. Es puramente decorativo, y por eso "
          "engaña a tanta gente.")

m.dos_codigos(
    "sizeof deja de servir",
    "En main",
    r"""
int datos[10];

sizeof(datos);      // 40

std::size(datos);   // 10

for (int x : datos) // compila
""",
    "Dentro de la función",
    r"""
void f(int v[10]) {

    sizeof(v);      // 8

    // std::size(v) NO compila

    // for (int x : v) NO compila
}
""",
    pie="Calcular sizeof(v)/sizeof(v[0]) dentro de la función es uno de los errores más frecuentes del lenguaje.",
    notas="Clang lo detecta con -Wsizeof-array-argument. En el ejemplo 16 el aviso "
          "está silenciado con un pragma para que el proyecto compile limpio; "
          "comentarlo en vivo para mostrar el diagnóstico real.")

m.mensaje("Como solo viaja la dirección, un arreglo **nunca se copia** al "
          "pasarlo, y la función **sí puede modificar** los elementos del llamador.",
          "Es la única excepción a la regla 'por valor significa copia'.",
          size=30,
          notas="Este es el punto contraintuitivo que hay que decir con esas "
                "palabras exactas. Enlaza con la tabla del bloque 2 donde ya se "
                "anticipó la excepción.")

m.demo(
    "16_decaimiento.cpp",
    "./build/bin/exp_16_decaimiento",
    ["`sizeof` vale 40 fuera de la función y 8 dentro.",
     "La función modifica el arreglo del llamador sin haberlo copiado.",
     "El decaimiento también ocurre fuera de las llamadas: `int* p = datos;`"],
    notas="Descomentar en vivo una de las dos sobrecargas comentadas para mostrar "
          "el error 'redefinition of recibe_como_arreglo'.")

m.dos_codigos(
    "Solución 1 · conservar el tamaño",
    "Tamaño fijo",
    r"""
void f(int (&v)[10]);

// los paréntesis son
// obligatorios:
// int& v[10] sería un
// arreglo de referencias,
// que no existe en C++
""",
    "Tamaño deducido",
    r"""
template <std::size_t N>
void g(const int (&v)[N]);

// N lo deduce el compilador
// en cada llamada.
// Dentro funcionan sizeof,
// std::size y el for por rango
""",
    pie="La referencia a arreglo conserva el tamaño porque el tamaño forma parte del tipo.",
    notas="Leer la declaración con la regla de siempre: v es una referencia a un "
          "arreglo de 10 int. Es la forma idiomatica anterior a C++20.")

m.codigo(
    "Solución 2 · std::span (C++20)",
    r"""
double media(std::span<const double> datos);

double crudo[4]         = {1, 2, 3, 4};
std::array<double,3> a  = {10, 20, 30};
std::vector<double> v   = {5, 5, 5, 5, 5};

media(crudo);    // las tres llamadas usan
media(a);        // la MISMA firma
media(v);
""",
    sub="dirección + tamaño, en un objeto de 16 bytes",
    pie="I.13 — Do not pass an array as a single pointer.  ·  F.24 — Use a span<T> to designate a half-open sequence.",
    notas="span no es dueño de nada: es una vista. Se pasa por valor, como un "
          "puntero, y no copia los elementos. Cuidado: puede quedar colgante igual "
          "que una referencia si el contenedor original muere o se realoja.")

m.tabla(
    "Las cuatro formas de recibir una secuencia",
    ["Forma", "Conserva tamaño", "Cualquier tamaño", "Acepta vector", "Estándar"],
    [["`T* v, std::size_t n`", "manual", "sí", "con `.data()`", "C++98"],
     ["`T (&v)[N]`", "sí", "no", "no", "C++98"],
     ["`template<N> T (&v)[N]`", "sí", "sí", "no", "C++98"],
     ["`std::span<T>`", "sí", "sí", "**sí**", "C++20"],
     ["`const std::vector<T>&`", "sí", "sí", "sí", "C++98"]],
    anchos=[5, 3, 3, 3, 2],
    size=13,
    notas="Si solo se llevan una fila, que sea la de span. Si el proyecto es C++17 "
          "o anterior, la plantilla con N deducido es la mejor alternativa.")

m.demo(
    "17 y 18 · conservar el tamaño",
    "./build/bin/exp_17_arreglo_por_referencia\n./build/bin/exp_18_span",
    ["Plantilla con `N` deducido: una sola función para todos los tamaños.",
     "`std::span` con arreglo crudo, `std::array` y `std::vector`.",
     "Subvistas sin copiar: `first`, `last`, `subspan`."],
    notas="Mostrar en el ejemplo 17 la llamada comentada que no compila: "
          "imprime_diez(tres), porque int[3] no es int[10].")

# ===========================================================================
# Bloque 9 - Multidimensionales
# ===========================================================================
m.seccion("9", "Arreglos multidimensionales", "25 minutos",
          ["Un arreglo de arreglos", "Orden por filas", "Pasar matrices",
           "Por qué el orden de los bucles cambia el rendimiento"],
          notas="Último bloque de contenido. Termina con la demostración más "
                "contundente de la sesión.")

m.codigo(
    "int m[3][4] es un arreglo de arreglos",
    r"""
int m[3][4];       // 3 elementos, y cada uno es un arreglo de 4 int

m          es de tipo   int[3][4]
m[i]       es de tipo   int[4]     <- UNA FILA ENTERA, no un elemento
m[i][j]    es de tipo   int
""",
    sub="[dcl.array]/9 — cuando varias especificaciones 'array of' son adyacentes se crea un tipo multidimensional",
    resaltar=(4,),
    size=16,
    pie="De esta frase salen todas las reglas del tema.",
    notas="Que m[i] sea una fila entera es la clave para entender el paso a "
          "funciones y el for basado en rango sobre matrices.")

m.codigo(
    "Orden por filas (row-major)",
    r"""
int m[3][4] en memoria, un único bloque contiguo:

[ m00 m01 m02 m03 | m10 m11 m12 m13 | m20 m21 m22 m23 ]
  ---- fila 0 ----   ---- fila 1 ----   ---- fila 2 ----
índice lineal:
    0   1   2   3      4   5   6   7      8   9  10  11

     &m[i][j]  ==  base + (i * COLUMNAS + j) * sizeof(T)
""",
    resaltar=(7,),
    size=15,
    pie="Fortran, MATLAB, R y Julia usan el orden inverso, columna por columna. Es una causa clásica de errores al portar código numérico.",
    notas="La fórmula es la que hay que retener. Es la misma que aparece en el "
          "bloque 10 al construir una matriz sobre un vector aplanado, y la que "
          "explica la diferencia de rendimiento del final del bloque.")

m.demo(
    "19_matriz_basica.cpp",
    "./build/bin/exp_19_matriz_basica",
    ["Los desplazamientos en bytes **confirman la fórmula** `i*C + j`.",
     "`sizeof(m)`, `sizeof(m[0])` y `sizeof(m[0][0])`: matriz, fila y elemento.",
     "`m[1][2]` y `*(m[1]+2)` son la misma expresión."],
    notas="La tabla de desplazamientos es la prueba visual de que la matriz es un "
          "solo bloque contiguo. Detenerse en ella.")

m.codigo(
    "for basado en rango sobre una matriz",
    r"""
for (const auto& fila : m) {      // fila es 'const int (&)[4]'
    for (int valor : fila) {
        ...
    }
}

// for (auto fila : m)   <- MAL: intentaría copiar un arreglo;
//                          fila decae a puntero y el bucle
//                          interno deja de compilar
""",
    resaltar=(0,),
    pie="La variable externa DEBE ser referencia a fila.",
    notas="Error muy común. Merece la pena escribirlo mal en vivo para que vean el "
          "mensaje del compilador.")

m.codigo(
    "Pasar una matriz a una función",
    r"""
void f(int m[][4], int filas);    // válido: solo la 1ª dimensión se omite
void f(int m[3][4], int filas);   // el 3 se ignora
void f(int (*m)[4], int filas);   // la firma REAL de las dos anteriores

void f(int** m, ...);             // ERROR conceptual: no es una matriz
""",
    resaltar=(4,),
    pie="int[3][4] decae a 'puntero a arreglo de 4 int', es decir int (*)[4]. NO decae a int**.",
    notas="El compilador necesita conocer todas las dimensiones menos la primera, "
          "porque sin el número de columnas no puede calcular i*COLUMNAS+j.")

m.codigo(
    "Por qué int** no funciona",
    r"""
int m[3][4]        un único bloque de 12 enteros
                   [ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]

int**              un arreglo de DIRECCIONES, cada una
                   apuntando a una fila suelta
                   [ *]--> [ ][ ][ ][ ]
                   [ *]--> [ ][ ][ ][ ]
                   [ *]--> [ ][ ][ ][ ]
""",
    sub="Disposiciones de memoria incompatibles",
    size=15,
    pie="error: cannot initialize a parameter of type 'int **' with an lvalue of type 'int[3][4]'",
    notas="Este diagrama resuelve de un golpe una de las confusiones más "
          "persistentes del tema. Dejarlo en pantalla mientras se explica.")

m.demo(
    "20 y 21 · matrices como parámetros y operaciones",
    "./build/bin/exp_20_matriz_parametros\n./build/bin/exp_21_matriz_operaciones",
    ["Las cuatro formas de recibir una matriz, incluida la vista aplanada.",
     "Suma, transpuesta y producto con plantillas.",
     "Al llevar las dimensiones en el tipo, **el compilador verifica** la compatibilidad."],
    notas="En el ejemplo 21, mencionar las dos llamadas comentadas que no "
          "compilan: sumar matrices de distinto tamaño y multiplicar matrices "
          "incompatibles. Con punteros crudos esa comprobación se pierde.")

m.codigo(
    "Tres dimensiones y la fórmula general",
    r"""
T v[D0][D1][D2]

  v[i][j][k]  está en  base + ( i*D1*D2 + j*D2 + k ) * sizeof(T)


Cada índice se multiplica por el producto de todas las
dimensiones que quedan a su derecha.
""",
    size=16,
    resaltar=(2,),
    pie="Es lo que dice el ejemplo de [dcl.array]/9 de la norma.",
    notas="A partir de tres dimensiones, lo habitual en código profesional es usar "
          "un bloque lineal con la fórmula del índice, o std::mdspan, incorporado "
          "en C++23.")

m.tabla(
    "El orden de los bucles cambia el rendimiento",
    ["Recorrido", "Código", "Tiempo"],
    [["Por filas", "`for (i) for (j) suma += m[i][j];`", "**0.88 ms**"],
     ["Por columnas", "`for (j) for (i) suma += m[i][j];`", "**25.84 ms**"]],
    sub="Matriz de 2048 × 2048 int (16 MiB), clang -O2, Apple Silicon",
    anchos=[3, 7, 2],
    pie="Mismo resultado numérico. Casi 30 veces más lento.",
    notas="Explicación: la memoria se lee en bloques (líneas de caché, 64 o 128 "
          "bytes). Al leer m[i][0] el procesador trae de golpe el resto de la "
          "fila. Si el bucle avanza por la fila, esos datos ya están en caché. Si "
          "avanza por columnas, cada acceso salta a otra línea.")

m.mensaje("En C y C++, el **último índice** debe ser el del bucle **más interno**.",
          "Cambiar el orden de dos bucles anidados es la optimización más barata que existe en cómputo con matrices.",
          size=32,
          notas="Es la consigna que deben llevarse del bloque 9. Sirve para "
                "matrices, imágenes, tensores y cualquier dato tabulado.")

m.demo(
    "23_orden_de_recorrido.cpp",
    "clang++ -std=c++20 -O2 exposicion/src/23_orden_de_recorrido.cpp -o /tmp/recorrido\n/tmp/recorrido",
    ["Compilarlo **aparte con -O2**: los sanitizadores distorsionan la medición.",
     "Las dos sumas dan el mismo número.",
     "La diferencia de tiempo es de un orden de magnitud."],
    notas="Compilarlo en vivo delante del grupo. Que vean que es el mismo archivo "
          "y que solo cambia el orden de dos líneas.")

# ===========================================================================
# Bloque 10 - Cierre
# ===========================================================================
m.seccion("10", "Qué usar en lugar del arreglo crudo", "10 minutos",
          ["std::array, std::vector, std::span", "Matrices modernas", "Cierre"],
          notas="Cierre rápido. El objetivo es que sepan qué escribir en código "
                "nuevo, después de haber entendido cómo funciona lo de debajo.")

m.tabla(
    "Las tres herramientas",
    ["Herramienta", "Cuándo", "Qué aporta"],
    [["`std::array<T,N>`", "tamaño fijo, conocido al compilar",
      "no decae, conoce su tamaño, se copia y **se devuelve**"],
     ["`std::vector<T>`", "tamaño decidido al ejecutar",
      "crece, se redimensiona, libera sola su memoria"],
     ["`std::span<T>`", "**parámetros** de función",
      "dirección + tamaño; una firma para los tres"]],
    anchos=[3, 4, 6],
    size=14,
    pie="std::array no tiene ningún sobrecosto: sizeof(std::array<int,4>) == sizeof(int[4]) == 16.",
    notas="Insistir en que std::array no es 'más lento por ser de la biblioteca'. "
          "Es exactamente el mismo bloque de memoria, con una interfaz decente.")

m.tabla(
    "Matrices en C++ moderno",
    ["Opción", "Contigua", "Dimensiones", "Nota"],
    [["`std::array<std::array<T,C>,F>`", "sí", "fijas", "equivalente de `T m[F][C]`"],
     ["`std::vector<T>` aplanado + `i*C+j`", "sí", "en ejecución", "lo que usan las bibliotecas numéricas"],
     ["`std::vector<std::vector<T>>`", "**no**", "en ejecución", "cómodo pero **lento**: cada fila es un bloque suelto"],
     ["`std::mdspan` (C++23)", "sí", "en ejecución", "vista multidimensional sobre un bloque lineal"]],
    anchos=[5, 2, 3, 5],
    size=13,
    notas="La tercera opción es la que más se ve en trabajos de clase y la peor: N "
          "reservas independientes, memoria dispersa y un salto de puntero por "
          "fila. Decirlo explícitamente.")

m.codigo(
    "Una matriz que reúne todo lo visto hoy",
    r"""
class Matriz {
public:
    Matriz(std::size_t filas, std::size_t columnas)
        : filas_(filas), columnas_(columnas),
          datos_(filas * columnas, 0.0) {}

    double& operator()(std::size_t i, std::size_t j)
        { return datos_[i * columnas_ + j]; }

    double operator()(std::size_t i, std::size_t j) const
        { return datos_[i * columnas_ + j]; }

private:
    std::size_t filas_, columnas_;
    std::vector<double> datos_;      // contiguo, como el arreglo crudo
};
""",
    size=13,
    pie="Memoria contigua · la fórmula i*C+j · dimensiones que viajan con el objeto · const correcto en las dos sobrecargas.",
    notas="Es el resumen práctico de la sesión en veinte líneas. Si alguien "
          "pregunta por qué operator() y no operator[], decir que hasta C++23 el "
          "corchete solo admitía un argumento.")

m.tabla(
    "Criterio final",
    ["Situación", "Elección"],
    [["Tamaño fijo y conocido al compilar", "`std::array<T,N>`"],
     ["Tamaño decidido al ejecutar", "`std::vector<T>`"],
     ["Parámetro que recibe una secuencia", "`std::span<T>`"],
     ["Parámetro de entrada, objeto grande", "`const T&`"],
     ["Interoperar con C, o sistema embebido", "arreglo crudo"]],
    anchos=[7, 5],
    notas="Cerrar diciendo por qué seguimos estudiando arreglos crudos: hay que "
          "saber leerlos, porque están en C, en el código heredado, en los "
          "sistemas embebidos y en las entrevistas de trabajo.")

m.vinetas(
    "Los tres mensajes de la sesión",
    ["**Elegir cómo se pasa un argumento es elegir qué se copia.** Por valor "
     "copia el objeto; por referencia no copia nada y crea un alias.",
     "",
     "**Un arreglo nunca se copia al pasarlo: decae a puntero** y pierde su "
     "tamaño. Por eso hay que pasar el tamaño aparte, o usar `std::span`.",
     "",
     "**La memoria es contigua y por filas.** De ahí salen el índice base cero, "
     "la fórmula `i*C + j` y una diferencia de 30 veces por cambiar el orden de "
     "dos bucles."],
    size=20,
    notas="Si solo recuerdan tres frases de las cuatro horas, que sean estas. "
          "Leerlas despacio.")

m.vinetas(
    "Para seguir",
    ["**C++ Core Guidelines** — isocpp.github.io/CppCoreGuidelines · reglas F.15 a F.24, F.60, I.11, I.13",
     "**Deitel & Deitel**, *Cómo programar en C++*, 9.ª ed. — caps. 6, 7 y 8",
     "**Stroustrup**, *The C++ Programming Language*, 4.ª ed. — caps. 7 y 12",
     "**Meyers**, *Effective C++*, 3.ª ed. — ítem 20",
     "**eel.is/c++draft** — el texto de la norma, con enlace por párrafo",
     "**godbolt.org** — Compiler Explorer, para ver el código generado",
     "",
     "Base de conocimiento, 24 ejemplos y tres prácticas: `Repositorios/C-CPP/exposicion/`"],
    sub="Bibliografía y material de apoyo",
    size=17,
    notas="Mencionar que todo el material queda en el repositorio, con los "
          "ejemplos compilables y las prácticas con solución.")

m.mensaje("Gracias.  ¿Preguntas?",
          "Alberto López · Programación Avanzada · UACBI, UAN",
          size=40,
          notas="Tener a mano el documento 09-errores-frecuentes-y-preguntas.md, "
                "que recoge las preguntas que suele hacer el grupo con su respuesta.")

# ===========================================================================
salida_pptx = os.path.join(os.path.dirname(os.path.abspath(__file__)),
                           "paso-de-argumentos-y-arreglos.pptx")
m.guardar(salida_pptx)
print("Diapositivas generadas: %d" % len(m.prs.slides._sldIdLst))
print("Escrito: %s" % salida_pptx)

# --- Conversion a formato LibreOffice --------------------------------------
soffice = "/Applications/LibreOffice.app/Contents/MacOS/soffice"
if os.path.exists(soffice):
    destino = os.path.dirname(salida_pptx)
    for formato in ("odp", "pdf"):
        subprocess.run([soffice, "--headless", "--convert-to", formato,
                        "--outdir", destino, salida_pptx],
                       check=True, capture_output=True)
        print("Escrito: %s" % os.path.join(
            destino, "paso-de-argumentos-y-arreglos." + formato))
else:
    print("LibreOffice no encontrado; solo se genero el .pptx")
