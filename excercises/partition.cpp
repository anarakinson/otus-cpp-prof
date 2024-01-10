#include <iostream>
#include <algorithm>
#include <vector>



int main() {

    std::vector<int> v = {1, 11, 111, 2, 21, 22, 213, 123, 4321, 12, 9, 8}; 


    auto it = std::partition(v.begin(), v.end(), [](int x){ return x > 100; });

    v.erase(it, v.end());

    for (auto x : v) {
        std::cout << x << " ";
    }

}