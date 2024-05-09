#include <allocator.h>

#include <iostream>
#include <memory>
#include <map>
#include <vector>
#include <string>


#define UNUSED(X) (void *)X


int factorial(const int n) {
    int f = 1;
    for (int i = 1; i <= n; ++i)
        f *= i;
    return f;
}



template <typename T>
void print_map(const char *name, const T &map) {
    
    std::cout << name << ": ";
    for (int i = 0; i < 10; ++i) {
        std::cout << map.at(i) << " ";
    }
    std::cout << std::endl;

}



int main() {
    
    try {
        Pool a{sizeof(int)};
        Pool b = a;

        std::map<int, int> map{};
        // std::map<int, int, std::less<int>, Mallocator<std::pair<const int, int>>> map_a{};
        std::map<int, int, std::less<int>, CustomAllocator<std::pair<const int, int>>> map_a{};


        for (int i = 0; i < 10; ++i) {
            std::cout << i << " ";
            map[i] = factorial(i);
            map_a[i] = factorial(i);
        }
        std::cout << std::endl;

        std::cout << "output" << std::endl;

        print_map("basic allocator", map);
        print_map("custom allocator", map_a);

    } catch (std::exception &ex) {
        std::cout << ex.what() << std::endl;
    }

    std::cout << "END" << std::endl;

}
