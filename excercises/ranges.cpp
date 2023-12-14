#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <ranges>
#include <memory>


bool is_even(int x) { return x % 2 == 0; }

int main() {

    std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};

    for (auto x : vec | std::ranges::views::reverse | std::ranges::views::filter(is_even) | std::ranges::views::take(5)) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
    for (auto x : vec | std::ranges::views::take(10) | std::ranges::views::reverse | std::ranges::views::filter(is_even)) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    // // std=23
    // std::vector<std::string> v2 {"a", "b", "c"};
    // for (auto [i, x] : std::ranges::views::enumerate(v2)) {
    //     std::cout << i << ": " << x << " ";
    // }
    // std::cout << std::endl;

}


