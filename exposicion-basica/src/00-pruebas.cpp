#include <cstring>
#include <iostream>

using namespace std;

struct Clientes {
    char nombre[100];
    char telefono[30];
    double saldo;
    bool moroso;
};

struct Punto {
    double x;
    double y;
};

struct LineaRecta {
    Punto inicio;
    Punto fin;
};

struct numeroComplejo {
    int real;
    int imaginario;
};

double CalculoPendiente(LineaRecta lr) {
    double pendiente = (lr.fin.y - lr.inicio.y) / (lr.fin.x - lr.inicio.x);
    return pendiente;
};


numeroComplejo sumaNumerosReales(numeroComplejo n1, numeroComplejo n2) {
    numeroComplejo resultado;
    resultado.real = n1.real + n2.real;
    resultado.imaginario = n1.imaginario + n2.imaginario;
    return resultado;
}

numeroComplejo conjugadoNumeroComplejo(numeroComplejo n1) {
    numeroComplejo resultado;
    resultado.real = n1.real;
    resultado.imaginario = -n1.imaginario;
    return resultado;
}

void imprimirNumeroComplejo(numeroComplejo n1) {
    cout << n1.real << " + " << n1.imaginario << "i" << endl;
}

int main() {

    cout <<"======PARTE DE LINEA RECTA========"<<endl<<endl;
    LineaRecta lr;
    cout << "dame el valor de x1: " << endl;
    cin >> lr.inicio.x;
    cout << "dame el valor de y1: " << endl;
    cin >> lr.inicio.y;
    cout << "dame el valor de x2: " << endl;
    cin >> lr.fin.x;
    cout << "dame el valor de y2: " << endl;
    cin >> lr.fin.y;
    cout << "la pendiente es: " << CalculoPendiente(lr) << endl;

    cout <<"======PARTE DE NUMEROS IMAGINARIOS=========="<<endl<<endl;
    numeroComplejo n1, n2, resultadoSuma, resultadoConjugado;
    cout << "dame el valor de la parte real del primer numero: " << endl;
    cin >> n1.real;
    cout << "dame el valor de la parte imaginaria del primer numero: " << endl;
    cin >> n1.imaginario;
    cout << "dame el valor de la parte real del segundo numero: " << endl;
    cin >> n2.real;
    cout << "dame el valor de la parte imaginaria del segundo numero: " << endl;
    cin >> n2.imaginario;
    resultadoSuma = sumaNumerosReales(n1, n2);
    resultadoConjugado = conjugadoNumeroComplejo(n1);

    cout << "El numero complejo 1 es: ";
    imprimirNumeroComplejo(n1);
    cout << "El numero complejo 2 es: ";
    imprimirNumeroComplejo(n2);
    cout << "La suma de los numeros complejos es: ";
    imprimirNumeroComplejo(resultadoSuma);
    cout << "El conjugado del numero complejo 1 es: ";
    imprimirNumeroComplejo(resultadoConjugado);

    return 0;
}
