#pragma once 

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>


template <typename T, T DefaultVal>
struct InternalData;

template <typename T, T DefaultVal>
class Proxy{
public:
    Proxy(InternalData<T, DefaultVal> data, size_t col, size_t row): 
    m_indata{data}, m_row{row}, m_col{col} {}
    Proxy &operator = (T val);
    operator T() const;

private:
    InternalData<T, DefaultVal> m_indata;
    size_t m_row{};
    size_t m_col{};
};

template <typename T, T DefaultVal>
struct InternalData {
    size_t m_col{};
    std::map<std::pair<size_t, size_t>, T> m_data{};

    std::set<size_t> m_rows{};
    std::set<size_t> m_cols{};

    // getter
    T operator [] (size_t row) const {
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
    Proxy<T, DefaultVal> operator [] (size_t row) {
        // return m_data[std::make_pair(m_col, row)];
        return Proxy<T, DefaultVal>{*this, m_col, row};
    } 

};


template <typename T, T DefaultVal>
Proxy<T, DefaultVal> &Proxy<T, DefaultVal>::operator = (T val) {
    m_indata.m_data[std::make_pair(m_col, m_row)] = val;
    return *this;
}

template <typename T, T DefaultVal>
Proxy<T, DefaultVal>::operator T() const {
    return m_indata.m_data[std::pair<size_t, size_t>(m_col, m_row)];
}

