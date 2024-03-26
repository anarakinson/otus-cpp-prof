#include <iostream>
#include <tuple>



int main() {

    std::pair<int,double> x{42,2.4};
    auto [i,j] = x;
    std::tie(i,j) = std::pair{3,3.3};

    std::cout << i << " " << j << std::endl;

    auto [x0,x1] = x;

    std::cout << x0 << " " << x1 << std::endl;

}
