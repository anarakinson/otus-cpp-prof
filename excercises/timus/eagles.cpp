#include <iostream>


int main() {

    int x;
    std::cin >> x;

    int out = 1;
    int temp = 1;
    for (int i = 1; i < x; ++i) {
        std::cout << i << " -> ";
        for (int j = 1; j < i; ++j) {
            temp = (x - j) * j;
            out = out > temp ? out : temp;
            temp = 1;
        }
        
        std::cout << " -> ";
        std::cout << temp << std::endl;
    }

    std::cout << out << std::endl;

}
