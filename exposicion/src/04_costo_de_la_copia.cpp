// ===========================================================================
// 04 - Cuanto cuesta una copia
// Bloque 2 (30 min) - Paso de argumentos por valor
//
// OBJETIVO
//   El paso por valor no solo cambia la SEMANTICA (el original no se toca);
//   tambien tiene un COSTO. Aqui se hace visible de dos formas:
//     a) contando construcciones y copias con una clase instrumentada;
//     b) midiendo el tiempo de pasar un vector grande por valor vs por const&.
//
// LO QUE SUELE SORPRENDER
//   Pasar por valor un objeto con memoria dinamica (std::string, std::vector)
//   copia TODO el contenido, no solo el "objeto pequeno" que se ve en el codigo.
//
// GUIA
//   C++ Core Guidelines F.16: "For 'in' parameters, pass cheaply-copied types
//   by value and others by reference to const". Regla practica: si el objeto
//   no es mayor que 2 o 3 punteros (16-24 bytes en 64 bits) y es trivial de
//   copiar, pasalo por valor; si no, por referencia a const.
// ===========================================================================

#include <chrono>
#include <iostream>
#include <string>
#include <vector>

// --- Clase instrumentada: informa cada vez que se construye o se copia -----
class Registro {
public:
    explicit Registro(std::string nombre) : nombre_(std::move(nombre)) {
        ++construcciones;
        std::cout << "    + construido  " << nombre_ << '\n';
    }

    Registro(const Registro& otro) : nombre_(otro.nombre_) {
        ++copias;
        std::cout << "    * COPIADO     " << nombre_ << '\n';
    }

    ~Registro() {
        ++destrucciones;
        std::cout << "    - destruido   " << nombre_ << '\n';
    }

    Registro& operator=(const Registro&) = delete;

    static int construcciones;
    static int copias;
    static int destrucciones;

private:
    std::string nombre_;
};

int Registro::construcciones = 0;
int Registro::copias = 0;
int Registro::destrucciones = 0;

void por_valor(Registro r) {  // <-- copia al entrar, destruccion al salir
    (void)r;
    std::cout << "    (trabajando dentro de por_valor)\n";
}

void por_referencia_const(const Registro& r) {  // <-- ni copia ni destruccion
    (void)r;
    std::cout << "    (trabajando dentro de por_referencia_const)\n";
}

// --- Medicion de tiempo con un vector grande -------------------------------
long long suma_por_valor(std::vector<int> datos) {
    long long total = 0;
    for (int v : datos) {
        total += v;
    }
    return total;
}

long long suma_por_referencia(const std::vector<int>& datos) {
    long long total = 0;
    for (int v : datos) {
        total += v;
    }
    return total;
}

int main() {
    std::cout << "PARTE 1: contar copias\n";
    Registro r{"expediente"};

    std::cout << "  llamada por valor:\n";
    por_valor(r);

    std::cout << "  llamada por referencia a const:\n";
    por_referencia_const(r);

    std::cout << "\n  Copias realizadas: " << Registro::copias << " (todas por el paso por valor)\n";

    // --- Parte 2 -----------------------------------------------------------
    const std::size_t n = 5'000'000;
    std::vector<int> datos(n, 1);
    const int repeticiones = 20;

    using reloj = std::chrono::steady_clock;

    auto t0 = reloj::now();
    long long acumulado_valor = 0;
    for (int i = 0; i < repeticiones; ++i) {
        acumulado_valor += suma_por_valor(datos);  // copia 5 millones de int cada vez
    }
    auto t1 = reloj::now();

    long long acumulado_ref = 0;
    for (int i = 0; i < repeticiones; ++i) {
        acumulado_ref += suma_por_referencia(datos);  // no copia nada
    }
    auto t2 = reloj::now();

    auto ms = [](auto desde, auto hasta) {
        return std::chrono::duration_cast<std::chrono::milliseconds>(hasta - desde).count();
    };

    std::cout << "\nPARTE 2: " << repeticiones << " llamadas con un vector de " << n
              << " enteros (" << (n * sizeof(int)) / (1024 * 1024) << " MiB)\n"
              << "  por valor            : " << ms(t0, t1) << " ms  (resultado " << acumulado_valor
              << ")\n"
              << "  por referencia const : " << ms(t1, t2) << " ms  (resultado " << acumulado_ref
              << ")\n\n"
              << "NOTA: compilado en Debug con sanitizers la diferencia se exagera,\n"
              << "pero el orden de magnitud se mantiene en Release. La copia se paga\n"
              << "aunque la funcion solo lea los datos.\n";
    return 0;
}
