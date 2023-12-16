#include <matrix.h>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <cassert>


int main() {

    /*-------------------------------------------------------------*/
    // Matrix<int, -1> matrix;
    // assert(matrix.size() == 0); // все ячейки свободны
    // auto a = matrix[0][0];
    // assert(a == -1);
    // assert(matrix.size() == 0);
    // matrix[100][100] = 314;
    // assert(matrix[100][100] == 314);
    // assert(matrix.size() == 1);

    // выведется одна строка
    // 100100314
    // for(auto c: matrix)
    // {
    //     int x;
    //     int y;
    //     int v;
    //     std::tie(x, y, v) = c;
    //     std::cout << x << y << v << std::endl;
    // }


    /*-------------------------------------------------------------*/
    Matrix<int, 0> matrix;

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (i == j || (i == 9 - j)) {
                matrix[i][j] = i;
            }
        }
    }

    std::cout << "size: " << matrix.size() << "\n" << std::endl;

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {    
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

}