
#pragma once

#include <utils.hpp>

#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <set>



struct Node {
    int id;
    std::string name;
};


class Table {
public:

    // push new node, 
    // update longest name size 
    // update id's list
    void push(int id, std::string &name) {
        // update size of longest string in table
        auto size = name.size();
        m_max_len = m_max_len < size ? size : m_max_len;

        m_data.push_back( Node{id, name} );
        m_keys.insert(id);
    }

    // push new node
    void operator () (int id, std::string name) {
        push(id, name);
    }

    // Get id and return name if exists else return ""
    std::string operator [] (int id) {
        if (!m_keys.count(id)) { return ""; }

        for (auto &node : m_data) {
            if (node.id == id) { return node.name; }
        }
        return "";
    }

    // return internal data
    std::vector<Node> data() { return m_data; }
    // return all ids 
    std::set<int> keys() { return m_keys; }
    void clear() {
        m_data.clear();
        m_keys.clear();
    }

    // return longest string size
    size_t max_len() { return m_max_len; }

private:
    // internal data
    std::vector<Node> m_data;
    // all indexes contained in table
    std::set<int> m_keys;
    // longest string in table size
    size_t m_max_len = 0;

};

