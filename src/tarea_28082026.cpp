//Tarea de clase 28/08/2026

//Dado 4 numeros enteros pedidos al usuario, mostrar en pantalla el menor de ellos.

#include <iostream>

int main(){
    int num1, num2, num3, num4;
    std::cout << "Ingrese cuatro numeros enteros: ";
    std::cin >> num1 >> num2 >> num3 >> num4;

    int menor = num1; // Asumimos que el primer número es el menor

    if (num2 < menor) {
        menor = num2;
    }
    if (num3 < menor) {
        menor = num3;
    }
    if (num4 < menor) {
        menor = num4;
    }

    std::cout << "El numero menor es: " << menor << std::endl;

    return 0; 
}