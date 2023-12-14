#include <iostream>
#include <cmath>
#include <string>


int main() {

    int n;

    std::cin >> n;

    int sum = std::pow(1, n) + std::pow(2, n) + std::pow(3, n) + std::pow(4, n);
    
    int res = 0;
    
    if (n % 4 == 0) res = 0;
    else if ((n % 2 != 0 && n % 5 == 0) || (n % 4 == 3)) res = 2;
    else if ((n % 4 == 1) || (n % 4 == 2)) res = 1;
    
    std::cout << res << std::endl;

}
