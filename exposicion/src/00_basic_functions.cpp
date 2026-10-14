//definiciones de funciones basicas de C++20

#include <iostream>

//funciones que retornan int

int suma(int a, int b){
    return a + b;
}

//funciones que retornan float

float suma(float a, float b){
    return a + b;
}

void main(){
    int x=1, y=2;
    float a=1.5, b=2.5;
    std::cout << "Funciones basicas de C++20" << std::endl;
    std::cout << "Suma de enteros: " << suma(x, y) << std::endl;
    std::cout << "Suma de floats: " << suma(a, b) << std::endl;
}
