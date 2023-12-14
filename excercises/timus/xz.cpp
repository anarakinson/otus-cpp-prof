#include <iostream>
#include <string>
#include <vector>

// try bruteforce

std::vector<int> get_sums(std::vector<int> &vec, std::vector<int> &sums, int x) {
    
    int i1, i2;
    for (int i = 0; i < x; ++i) {
        i1 = i + 1;
        if (i1 >= x) i1 -= x;
        i2 = i - 1;
        if (i2 < 0) i2 = x - 1;

        sums[i] = vec[i] + vec[i1] + vec[i2];
    }
    return sums;

}

void get_max_sum(std::vector<int> &sums, int &max_sum, int &idx, int x) {
    for (int i = 0; i < x; ++i) {
        int sum = sums[i];
        if (sum > max_sum) {
            max_sum = sum;
            idx = i;
        }
    }
}


int main() {

    int x, y;
    std::cin >> x;

    std::vector<int> vec{};
    std::vector<int> sums{};
    vec.reserve(x);
    sums.reserve(x);
    

    for (int i = 0; i < x; ++i) {
        std::cin >> y;
        vec.push_back(y);
    }

    int max_sum = 0;
    int damage = 0;

    for (int i = 0; i < x; i++) {
        for (int j = 0; j < x; j++) {
            
        }
    }

    std::cout << damage << std::endl;

}

/* 
7
3 4 2 2 1 4 1
*/

/*
8
4 5 6 5 4 5 6 5
*/