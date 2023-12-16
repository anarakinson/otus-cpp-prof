#include <internal_data.h>

#include <iostream>
#include <memory>
#include <string>
#include <map>
#include <cassert>



template <typename T, T DefaultVal>
class Matrix {
    
    using InternalData_t = InternalData<T, DefaultVal>;

public:
    Matrix() {}
    ~Matrix() {}

    T get(size_t col, size_t row) {
        if (m_indata.m_data.count(std::make_pair(col, row))) {
            return m_indata.m_data[std::make_pair(col, row)];
        }
        else {
            return DefaultVal;
        }
    
    }

    void set(size_t col, size_t row, T data) {        
        m_indata.m_data[std::make_pair(col, row)] = data;
    }


    InternalData_t operator [] (size_t col) {
        m_indata.m_col = col;
        return m_indata;
    }

    size_t size() { return m_indata.m_data.size(); }


private:
    InternalData_t m_indata{};

};



int main() {

    Matrix<int, -123> mat{};

    // int x = mat.get(1, 2);
    // std::cout << x << std::endl;

    mat.set(1, 2, 3);
    int y = mat.get(1, 2);
    std::cout << y << std::endl;


    auto x = mat[1][2];
    std::cout << x << std::endl;

    auto x0 = mat[1][1];
    std::cout << x0 << std::endl;
    auto x1 = mat[2][2];
    std::cout << x1 << std::endl;
    std::cout << mat.size() << std::endl;


    mat.set(3, 2, 3);
    mat.set(4, 2, 3);
    mat.set(5, 2, 3);
    std::cout << mat.size() << std::endl;

    mat[2][2] = 999;
    auto x2 = mat[2][2];
    std::cout << x2 << std::endl;
    

    // mat[2] = 1;
    // auto y = mat[2];
    // std::cout << y << std::endl;

    /*-------------------------------------------------------------*/
    // Matrix<int, -1> matrix;
    // assert(matrix.size() == 0); // все ячейки свободны
    // auto a = matrix[0][0];
    // assert(a == -1);
    // assert(matrix.size() == 0);
    // matrix[100][100] = 314;
    // assert(matrix[100][100] == 314);
    // assert(matrix.size() == 1);

    // // выведется одна строка
    // // 100100314
    // for(auto c: matrix)
    // {
    //     int x;
    //     int y;
    //     int v;
    //     std::tie(x, y, v) = c;
    //     std::cout << x << y << v << std::endl;
    // }



}