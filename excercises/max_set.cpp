#include <iostream>
#include <set>


int main() {

    std::set<int> set = {1, 3, 4, 35, 26, 12, 19};

    auto it = set.begin();
    std::advance(it, set.size() - 1);

    std::cout << set.size() << " <<< " << *it << std::endl;

}


