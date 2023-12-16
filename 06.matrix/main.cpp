
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <cassert>


template <typename T, T DefaultVal>
class Rows;

template <typename T, T DefaultVal>
class Matrix {
    
public:
    Matrix() {}
    ~Matrix() {}

//     T get(size_t col, size_t row) {
//         if ((col, row)) {
//             return {};
//         }
//         else {
//             return DefaultVal;
//         }
    
//     }

//     void set(size_t col, size_t row, T data) {        
        
//     }


    // size_t size() { return m_size; }


// private:
//     size_t m_size{};
//     std::map<size_t, std::map<size_t, T>> m_data{};

// };


// template <typename T, T DefaultVal>
// class Rows : std::map<size_t, T> {
// public:
//     T& operator [] (size_t row) const {
//         if (this->count(row)) {
//             return this[row];
//         }
//     }
private:

    std::map<size_t, Rows<T, DefaultVal>> m_data{};

};



template <typename T, T DefaultVal>
class Rows {
public:

    struct Result {
        Rows<T, DefaultVal> &map_;
        size_t key_;
        Result (Rows<T, DefaultVal> &m, size_t k) : map_(m), key_(k) {}
        operator const T & () const {
            return map_.get_item(key_);
        }
        T & operator = (T rhs) {
            return map_.set_item(key_, rhs);
        }
        operator T() {
            return map_[key_];
        }
    };

    // getter
    const T & get_item (size_t key) const {
        // std::cout << "get" << std::endl;
        if (m_data.count(key)) {
            return m_data.at(key);
        }
        else {
            return defaultVal;
        }
    }
    // setter
    T & set_item (size_t key, T v) {
        return m_data[key] = v;
    }

    // operator [] for setter
    Result operator [] (size_t key) { 
        return Result(*this, key); 
    }
    // operator [] for getter
    const T & operator [] (size_t key) const {
        return get_item(key);
    }


private:
    std::map<size_t, T> m_data;
    int defaultVal = DefaultVal;
};





int main() {

    // Matrix<int, -123> mat{};
    std::map<size_t, Rows<int, -19>> mat{};


    // // int x = mat.get(1, 2);
    // // std::cout << x << std::endl;

    // mat.set(1, 2, 3);
    // int y = mat.get(1, 2);
    // std::cout << y << std::endl;


    // std::map<size_t, std::map<size_t, int>> rows{};
    // rows[1][2] = 10;
    // auto x = rows[1][2];
    // std::cout << x << std::endl;

/* ------------------------------- */
    // Rows<int, -123> rows{};
    // rows[1] = 10;
    // auto x = rows[0];
    // // auto x = 1;
    // auto y = rows[1];
    // std::cout << x << " " << y << std::endl;
/* ------------------------------- */

    int x = mat[1][2];
    std::cout << x << std::endl;
    mat[1][2] = 1;
    int x3 = mat[1][2];
    std::cout << x3 << std::endl;

    auto x0 = mat[1][1];
    std::cout << x0 << std::endl;
    auto x1 = mat[2][2];
    std::cout << x1 << std::endl;
    // std::cout << mat.size() << std::endl;


    // mat.set(3, 2, 3);
    // mat.set(4, 2, 3);
    // mat.set(5, 2, 3);
    // std::cout << mat.size() << std::endl;

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