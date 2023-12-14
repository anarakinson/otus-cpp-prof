#include <iostream> 



int main() {

    int a = 10;

    char b = 'q';

    long double c = 0;

    auto result = a + b + c;          // слабая статическая явная типизация

    std::cout << result << std::endl;
    
}