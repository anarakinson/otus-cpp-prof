#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <cassert>



template <typename T, T DefaultVal>
class Matrix {
public:
    Matrix() {

    }

    ~Matrix() {

    }

    T get(size_t col, size_t row) {
        if (dummy.m_data.count(std::make_pair(col, row))) {
            return dummy.m_data[std::make_pair(col, row)];
        }
        else {
            return DefaultVal;
        }
    
    }

    void set(size_t col, size_t row, T data) {        
        dummy.m_data[std::make_pair(col, row)] = data;
    }


    struct Dummy {
        size_t m_col{};
        std::map<std::pair<size_t, size_t>, T> m_data{};

        std::set<size_t> m_rows{};
        std::set<size_t> m_cols{};

        // getter
        T operator [] (size_t row) {
            // std::cout << m_col << " " << row << std::endl;

            if (m_data.count(std::make_pair(m_col, row))) {
            // if (m_rows.count(row) && m_cols.count(m_col)) {
                return m_data[std::make_pair(m_col, row)];
            }
            else {
                return DefaultVal;
            }
        }

        // setter
        // Proxy operator [] (size_t row) {
        //     return m_data[std::make_pair(m_col, row)];
        // } 


    };


    Dummy operator [] (size_t col) {
        dummy.m_col = col;
        return dummy;
    }

    // T operator [] (size_t col, size_t row) {
    //     if (dummy.m_data.count(std::make_pair(col, row))) {
    //         return dummy.m_data[std::make_pair(col, row)];
    //     }
    //     else {
    //         return DefaultVal;
    //     }
    
    // }


    size_t size() { return dummy.m_data.size(); }


private:
    // std::map<std::pair<size_t, size_t>, T> m_data{};

    Dummy dummy{};

    size_t m_size = 0;

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

    auto x1 = mat[2][2];
    std::cout << x1 << std::endl;
    std::cout << mat.size() << std::endl;


    mat.set(3, 2, 3);
    mat.set(4, 2, 3);
    mat.set(5, 2, 3);
    std::cout << mat.size() << std::endl;

    // mat[2][2] = 999;
    // auto x2 = mat[2][2];
    // std::cout << x2 << std::endl;
    

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