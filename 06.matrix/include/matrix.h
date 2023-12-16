#pragma once 

#include <iostream>
#include <string>
#include <map>


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

    // helper struct
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

    // operator [] for getter and setter
    Result operator [] (size_t key) { 
        // std::cout << "set" << std::endl;
        return Result(*this, key); 
    }

    size_t size() { return m_size; }


private:

    std::map<size_t, T> m_data;
    int defaultVal = DefaultVal;
    size_t m_size = 0;

};
