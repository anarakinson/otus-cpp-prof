#include <iostream>


int main() {

    int x;
    std::cin >> x;


    int min = 0;
    int max = 0;
    int left = 0;
    int right = 0;


    for (int i = 0; i < x; ++i) {
        int a;
        std::cin >> a;

        if (a > min) {
            min = a;
            max = a;
            left = i;
        }
        if (a < min && i != x - 1) {
            right = i;
        }

    }

    if (right == 0) right = x;
    // left++; right++;
    int middle = (left + right - 1) / 2;
    int lenght = (right - left);

    std::cout << "min " << min << " left: " << left << " right: " << right << " middle: " << middle  << " lenght: " << lenght << std::endl; 
    std::cout << (middle) * min << " " << middle + left << " " << std::endl; 

}
