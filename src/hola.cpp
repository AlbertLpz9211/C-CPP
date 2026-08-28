#include <iostream>
#include <string>
#include <vector>

int main() {
    std::vector<std::string> partes{"Hola", "desde", "C++20"};
    for (const auto& p : partes) std::cout << p << ' ';
    std::cout << '\n';
    return 0;
}
