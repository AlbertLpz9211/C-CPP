// crear una cuenta de 0 a 99 usando dos bucles for anidados
#include <iostream>

int main(){
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            std::cout << i << j << std::endl;
        }
    }
    return 0;
}
