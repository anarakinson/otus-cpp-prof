
#include <iostream>
#include <string>
#include <tuple>
#include <cassert>

struct Sub {
    double b;
    int c;
};

struct Struct {
    int a;
    Sub sub;
};

int main() {

    std::pair<int, int> pair{1, 2};

    auto& [a, b] = pair;

    std::cout << a << " " << b << std::endl;
    std::cout << pair.first << " " << pair.second << std::endl;

    a = 10;
    b = 20;
    std::cout << a << " " << b << std::endl;
    std::cout << pair.first << " " << pair.second << std::endl;

    /* -------------------------------------------------------- */

    Struct ss = {1, 2, 3};

    auto& [sa, ssub] = ss;
    auto& [sb, sc] = ssub;


    std::cout << sa << " " << sb << " " << sc << std::endl;


}   
