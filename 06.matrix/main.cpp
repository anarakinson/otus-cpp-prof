
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


    Rows<T, DefaultVal> &operator [] (size_t key) {
        return m_data[key];
    }


    size_t size() { 
        size_t size = 0;
        for (auto [key, row] : m_data) {
            size += row.size();
        }
        return size; 
    }


private:

    std::map<size_t, Rows<T, DefaultVal>> m_data{};

};



template <typename T, T DefaultVal>
class Rows {
public:

    // Rows() = delete;
    // Rows(Matrix &matrix): m_matrix{matrix} {
    // }
    // ~Rows() = default;
    

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
        // operator T() {
        //     return static_cast<T>(map_[key_]);
        // }
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
        // std::cout << "set" << std::endl;
        m_size++;
        return m_data[key] = v;
    }

    // operator [] for setter
    Result operator [] (size_t key) { 
        // std::cout << "set" << std::endl;
        return Result(*this, key); 
    }
    // // operator [] for getter
    // const T & operator [] (size_t key) const {
    //     // std::cout << "get" << std::endl;
    //     return get_item(key);
    // }

    size_t size() { return m_size; }


private:
    // Matrix &m_matrix;
    std::map<size_t, T> m_data;
    int defaultVal = DefaultVal;
    size_t m_size = 0;
};





int main() {

    // Matrix<int, -123> mat{};

/* ------------------------------- */
    // Rows<int, -123> rows{};
    // rows[1] = 10;
    // auto x = rows[0];
    // // auto x = 1;
    // auto y = rows[1];
    // std::cout << x << " " << y << std::endl;
/* ------------------------------- */

    // auto x = mat[1][2];
    // std::cout << x << std::endl;
    // mat[1][2] = 11;
    // mat[2][2] = 12;
    // mat[3][2] = 13;
    // mat[4][2] = 14;
    // auto x3 = mat[1][2];
    // std::cout << x3 << std::endl;

    // auto x0 = mat[1][1];
    // std::cout << x0 << std::endl;
    // auto x1 = mat[2][2];
    // std::cout << x1 << std::endl;
    // std::cout << mat.size() << std::endl;


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