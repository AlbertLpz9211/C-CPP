// ===========================================================================
// SOLUCIÓN DE REFERENCIA · TAREA INTEGRADORA
// Sistema de Monitoreo de Calificaciones y Estadísticas
//
// Demuestra los conceptos fundamentales:
//   1. Paso por referencia (&) para modificar variables y salidas múltiples
//   2. Paso por valor para funciones puras y copias de trabajo
//   3. Paso por referencia constante (const T&) para lectura segura sin copia
//   4. Punteros con retorno opcional y comprobación estricta de nullptr
//   5. Arreglos 1D a funciones con tamaño explícito (const T[], int n)
//   6. Matrices 2D a funciones con columnas fijas (const T[][COLUMNAS], int filas)
// ===========================================================================

#include <iostream>
#include <iomanip>
#include <string>

// Constantes globales de dimensionamiento
constexpr int NUM_ALUMNOS = 5;
constexpr int NUM_PARCIALES = 3;

// --- PROTOTIPOS DE FUNCIONES ---
void actualizar_calificacion(double& nota_alumno, double nueva_nota);

double calcular_estadisticas_alumno(const double parciales[], int num_parciales, 
                                    double& nota_min, double& nota_max);

double aplicar_bonificacion(double nota_original, double porcentaje_extra);

const double* buscar_calificacion_perfecta(const double matriz[][NUM_PARCIALES], 
                                           int filas, int parcial);

void imprimir_sabana_notas(const double matriz[][NUM_PARCIALES], 
                           int filas, const std::string& titulo);

// --- IMPLEMENTACIÓN DE FUNCIONES ---

// 1. Paso por referencia: modifica directamente la casilla de memoria del llamador
void actualizar_calificacion(double& nota_alumno, double nueva_nota) {
    if (nueva_nota < 0.0 || nueva_nota > 10.0) {
        std::cout << "[ERROR] Calificación inválida (" << nueva_nota 
                  << "). Debe estar entre 0.0 y 10.0. No se modifica.\n";
        return;
    }
    // Modificación directa gracias a la referencia (&)
    nota_alumno = nueva_nota;
}

// 2. Arreglo 1D y referencias de salida para devolver múltiples resultados
double calcular_estadisticas_alumno(const double parciales[], int num_parciales, 
                                    double& nota_min, double& nota_max) {
    if (num_parciales <= 0) {
        nota_min = 0.0;
        nota_max = 0.0;
        return 0.0;
    }

    double suma = 0.0;
    nota_min = parciales[0];
    nota_max = parciales[0];

    for (int i = 0; i < num_parciales; ++i) {
        suma += parciales[i];
        if (parciales[i] < nota_min) {
            nota_min = parciales[i];
        }
        if (parciales[i] > nota_max) {
            nota_max = parciales[i];
        }
    }

    // El promedio se devuelve por valor con return
    return suma / num_parciales;
}

// 3. Paso por valor: función matemática pura que no altera la variable original
double aplicar_bonificacion(double nota_original, double porcentaje_extra) {
    double factor = 1.0 + (porcentaje_extra / 100.0);
    double nota_bonificada = nota_original * factor;
    if (nota_bonificada > 10.0) {
        nota_bonificada = 10.0; // tope de calificación
    }
    return nota_bonificada;
}

// 4. Búsqueda y Punteros: devuelve la dirección física o nullptr si no existe
const double* buscar_calificacion_perfecta(const double matriz[][NUM_PARCIALES], 
                                           int filas, int parcial) {
    if (parcial < 0 || parcial >= NUM_PARCIALES) {
        return nullptr;
    }

    for (int i = 0; i < filas; ++i) {
        // En punto flotante, comparamos con un margen epsilon o exactitud razonable
        if (matriz[i][parcial] >= 9.999) {
            // Devolvemos la dirección de memoria de ese elemento específico
            return &matriz[i][parcial];
        }
    }

    return nullptr; // No se encontró ninguna nota perfecta
}

// 5. Matriz 2D y referencia constante (const std::string&)
void imprimir_sabana_notas(const double matriz[][NUM_PARCIALES], 
                           int filas, const std::string& titulo) {
    std::cout << "\n======================================================\n";
    std::cout << "  " << titulo << '\n';
    std::cout << "======================================================\n";
    std::cout << std::left << std::setw(12) << "Estudiante"
              << std::setw(12) << "Parcial 1"
              << std::setw(12) << "Parcial 2"
              << std::setw(12) << "Parcial 3" << '\n';
    std::cout << "------------------------------------------------------\n";

    std::cout << std::fixed << std::setprecision(1);
    for (int i = 0; i < filas; ++i) {
        std::cout << std::left << std::setw(12) << ("Alumno " + std::to_string(i + 1));
        for (int j = 0; j < NUM_PARCIALES; ++j) {
            std::cout << std::setw(12) << matriz[i][j];
        }
        std::cout << '\n';
    }
    std::cout << "======================================================\n\n";
}

// --- FUNCIÓN PRINCIPAL ---
int main() {
    // 1. Declaración de la matriz bidimensional inicial
    double notas[NUM_ALUMNOS][NUM_PARCIALES] = {
        {8.5, 9.0, 7.5},
        {6.0, 5.5, 6.5},
        {9.5, 8.0, 8.5},
        {4.0, 6.0, 5.0},
        {10.0, 9.5, 9.0}
    };

    // 2. Imprimir tabla inicial usando const std::string&
    std::string encabezado = "SÁBANA DE CALIFICACIONES (ORIGINAL)";
    imprimir_sabana_notas(notas, NUM_ALUMNOS, encabezado);

    // 3. Demostración de paso por referencia con actualizar_calificacion
    std::cout << "--- 1. Actualización de Calificación por Referencia ---\n";
    std::cout << "Nota anterior Alumno 2, Parcial 2: " << notas[1][1] << '\n';
    actualizar_calificacion(notas[1][1], 8.0);
    std::cout << "Nota modificada directamente en matriz: " << notas[1][1] << " (actualizada)\n";

    std::cout << "Intento con nota inválida (-2.5): ";
    actualizar_calificacion(notas[1][1], -2.5);

    // 4. Demostración de arreglos 1D y referencias de salida
    std::cout << "\n--- 2. Estadísticas de Alumnos (Arreglo 1D y Salidas Múltiples) ---\n";
    std::cout << std::fixed << std::setprecision(2);
    for (int i = 0; i < NUM_ALUMNOS; ++i) {
        double min_nota = 0.0;
        double max_nota = 0.0;
        // notas[i] es la dirección del inicio de la fila i (decae a arreglo 1D)
        double prom = calcular_estadisticas_alumno(notas[i], NUM_PARCIALES, min_nota, max_nota);

        std::cout << "Alumno " << (i + 1) 
                  << " -> Promedio: " << std::setw(5) << prom 
                  << " | Mínima: " << std::setw(4) << min_nota 
                  << " | Máxima: " << std::setw(4) << max_nota << '\n';
    }

    // 5. Demostración de paso por valor con aplicar_bonificacion
    std::cout << "\n--- 3. Bonificación por Valor (Independencia de Memoria) ---\n";
    double nota_original = notas[3][0]; // Alumno 4, Parcial 1 (4.0)
    double nota_con_bono = aplicar_bonificacion(nota_original, 20.0); // +20%
    std::cout << "Nota original en matriz:       " << nota_original << '\n';
    std::cout << "Nota calculada con bono (+20%): " << nota_con_bono << '\n';
    std::cout << "Verificación en la matriz:      " << notas[3][0] 
              << "  <-- INTACTA (paso por valor protegido)\n";

    // 6. Demostración de punteros y verificación estricta de nullptr
    std::cout << "\n--- 4. Búsqueda con Punteros y Verificación de nullptr ---\n";

    // Búsqueda en Parcial 1 (el alumno 5 tiene 10.0)
    const double* ptr_parcial1 = buscar_calificacion_perfecta(notas, NUM_ALUMNOS, 0);
    if (ptr_parcial1 != nullptr) {
        std::cout << "[ÉXITO] Se localizó calificación perfecta en Parcial 1:\n"
                  << "        Dirección de memoria: " << ptr_parcial1 << '\n'
                  << "        Valor en la casilla:  " << *ptr_parcial1 << '\n';
    } else {
        std::cout << "[INFO] Nadie obtuvo calificación perfecta en Parcial 1.\n";
    }

    // Búsqueda en Parcial 2 (nadie tiene 10.0)
    const double* ptr_parcial2 = buscar_calificacion_perfecta(notas, NUM_ALUMNOS, 1);
    if (ptr_parcial2 != nullptr) {
        std::cout << "[ÉXITO] Se localizó calificación perfecta en Parcial 2: " 
                  << *ptr_parcial2 << '\n';
    } else {
        std::cout << "[INFO] Nadie obtuvo calificación perfecta en Parcial 2 (puntero nullptr seguro).\n";
    }

    // 7. Imprimir sábana final actualizada
    imprimir_sabana_notas(notas, NUM_ALUMNOS, "SÁBANA FINAL CON CORRECCIONES APLICADAS");

    return 0;
}
