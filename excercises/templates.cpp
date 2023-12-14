#include <iostream>

// templates as function alternative:
// computes in compile-time
template <int x>
struct compute_pow {

    static const int value = x * x;

};

// factorial
template <int x>
struct factorial {
    static const int value = x * factorial<x - 1>::value;
};
template <>
struct factorial<0> {
    static const int value = 1;
};



int main() {

    constexpr int x = compute_pow<2>::value;
    constexpr int y = compute_pow<x>::value;

    std::cout << x << " " << y << std::endl;

    constexpr int fact = factorial<4>::value;
    std::cout << fact << std::endl;

}