# Práctica 2 · Referencias, punteros y `const`

> Bloque 6 de la exposición · 15 min

Solución de referencia: `soluciones/solucion-practica-2.cpp`

---

## Ejercicio 1 · Escribir la firma (4 min)

Escribe la declaración de una función que:

1. reciba un `std::vector<double>` que **no** va a modificar;
2. reciba un `int` que **sí** va a modificar;
3. reciba un `std::string` opcional (puede no haber ninguno);
4. devuelva el mínimo y el máximo de un vector en una sola llamada.

## Ejercicio 2 · Detectar el error de vida (4 min)

¿Qué está mal en cada función? ¿Cuál de los dos errores detecta el compilador?

```cpp
const std::string& saluda(const std::string& nombre) {
    std::string mensaje = "Hola, " + nombre;
    return mensaje;
}

int& primer_elemento(std::vector<int>& v) {
    v.push_back(0);
    return v[0];
}
```

## Ejercicio 3 · Lectura de `const` (3 min)

Para cada declaración, indica si las dos operaciones son legales.

| Declaración | `*p = 5;` | `p = &otro;` |
|---|---|---|
| `int* p = &x;` | | |
| `const int* p = &x;` | | |
| `int* const p = &x;` | | |
| `const int* const p = &x;` | | |

## Ejercicio 4 · Reto (4 min)

Escribe una función que reciba dos punteros a `int` y ponga a cero el que
apunte al valor mayor. Debe funcionar aunque alguno de los dos punteros sea
nulo. Después reescríbela con referencias y explica qué cambia.

---

## Soluciones

**1.**
```cpp
double promedio(const std::vector<double>& datos);          // 1
void duplica(int& n);                                       // 2
void registra(const std::string* mensaje);                  // 3  (o std::optional)
struct Extremos { double minimo, maximo; };
Extremos extremos(const std::vector<double>& datos);        // 4
```

**2.** La primera devuelve una referencia a una variable local: queda colgante
en cuanto la función retorna. **El compilador sí avisa**
(`-Wreturn-stack-address`). La segunda es más sutil: `push_back` puede
realojar el vector, pero como la referencia se toma *después* del `push_back`,
esta versión concreta es válida. Sería incorrecta al revés:

```cpp
int& r = v[0];
v.push_back(0);   // aquí r puede quedar colgante
return r;
```

El compilador **no** detecta ese caso; AddressSanitizer sí.

**3.**

| Declaración | `*p = 5;` | `p = &otro;` |
|---|---|---|
| `int* p` | sí | sí |
| `const int* p` | no | sí |
| `int* const p` | sí | no |
| `const int* const p` | no | no |

**4.** Con punteros hay que comprobar el nulo; con referencias, no, porque el
lenguaje garantiza que hay objeto. A cambio, la versión con referencias no
puede expresar "no hay segundo valor". Es exactamente el criterio F.60.
