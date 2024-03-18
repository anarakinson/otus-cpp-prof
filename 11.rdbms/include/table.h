
#pragma once

#include <utils.h>

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

    void push(int id, std::string &name) {
        m_max_len = name.size();
        m_data.push_back( Node{id, name} );
        m_keys.insert(id);
    }

    void operator () (int id, std::string name) {
        push(id, name);
    }

    std::string operator [] (int id) {
        if (!m_keys.count(id)) { return ""; }

        for (auto &node : m_data) {
            if (node.id == id) { return node.name; }
        }
        return "";
    }

    std::vector<Node> data() { return m_data; }
    std::set<int> keys() { return m_keys; }
    void clear() {
        m_data.clear();
        m_keys.clear();
    }

    int max_len() { return m_max_len; }

private:
    std::vector<Node> m_data;
    std::set<int> m_keys;
    int m_max_len = 0;

};



class DataBase {
public:

    void add_table(std::string name, Table table) {
        m_data[name] = table;
    }


    std::string operator () (std::string &query) {
        
        auto words = Utils::split(query);
        auto first_word = Utils::to_lower(words[0]);
        
        if (first_word == "help" && words.size() == 1) {
            return std::string(
                "\nCOMMANDS:\n"
                "INSERT table id name\n"
                "TRUNCATE table\n"
                "INTERSECTION\n"
                "SYMMETRIC_DIFFERENCE\n"
                "SHOW table\n"
            );
        } 
        
        else if (first_word == "show" && words.size() == 2) {
            return query_show(words[1]);
        } 

        else if (first_word == "insert" && words.size() == 4) {
            return query_insert(words);
        } 
        
        else if (first_word == "truncate" && words.size() == 2) {
            return query_truncate(words[1]);
        } 
        
        else if (first_word == "intersection" && words.size() == 1) {
            return query_intersection();
        } 
        
        else if (first_word == "symmetric_difference" && words.size() == 1) {
            return query_symm_diff();
        } 
        
        else {
            return std::string{"Unrecognized query!"};
        }

    }


private:
    
    std::map<std::string, Table> m_data;


    // --------------------------- //
    std::string query_show(std::string &table_name) {
        std::string out;
        if (!m_data.count(table_name)) {
            return "Table does not exist!";
        }

        out = "\n";
        out += "id | name \n";
        out += "---+----------\n";
        for (auto &node : m_data[table_name].data()) {
            out += node.id > 10 ? "" : " ";
            out += std::to_string(node.id) + " | " + node.name + "\n";
        }

        return out;
    }


    std::string query_insert(std::vector<std::string> &words) {
        auto table_name = words[1];
        if (!m_data.count(table_name)) {
            return "Table does not exist!";
        }
        auto &table = m_data[table_name];
        int id = std::stoi(words[2]);
        std::string name = words[3];

        if (table.keys().count(id)) {
            return "Id must be unique!";
        }

        table.push(id, name);

        return "OK!";
    }


    std::string query_truncate(std::string &table_name) {
        if (!m_data.count(table_name)) {
            return "Table does not exist!";
        }
        m_data[table_name].clear();
        return "OK!";
    }


    std::string query_intersection() {

        auto A_keys = m_data["A"].keys(); 
        auto B_keys = m_data["B"].keys();

        auto intersection = std::set<int>{};
        // get the intersection
        std::set_intersection(A_keys.begin(), A_keys.end(), B_keys.begin(), B_keys.end(), std::inserter(intersection, intersection.begin()));

        std::string out{
            "id |   A   |   B    \n"
            "---+-------+--------\n"
        };
        for (auto id : intersection) {
            out += " " + std::to_string(id) + " | " + m_data["A"][id] + " | " + m_data["B"][id] + "\n";
        }

        return out;
    }


    std::string query_symm_diff() {

        auto A_keys = m_data["A"].keys(); 
        auto B_keys = m_data["B"].keys();

        auto difference = std::set<int>{};
        // get the difference one from another and vice versa
        std::set_difference(
            A_keys.begin(), A_keys.end(), 
            B_keys.begin(), B_keys.end(), 
            std::inserter(difference, difference.begin())
        );
        std::set_difference(
            B_keys.begin(), B_keys.end(), 
            A_keys.begin(), A_keys.end(), 
            std::inserter(difference, difference.begin())
        );

        std::cout << difference.size() << "\n";
        for (auto x : difference) {
            std::cout << x << " ";
        }
        std::cout << "\n";

        std::string out{
            "id |   A   |   B    \n"
            "---+-------+--------\n"
        };
        for (auto id : difference) {
            out += " " + std::to_string(id) + " | " + m_data["A"][id] + " | " + m_data["B"][id] + "\n";
        }

        return out;
    }

};



DataBase create_dummy_database() {

    Table A;
    A(0, "lean");
    A(1, "sweater");
    A(2, "frank");
    A(3, "violation");
    A(4, "quality");
    A(5, "precision");

    Table B;
    B(3, "proposal");
    B(4, "example");
    B(5, "lake");
    B(6, "flour");
    B(7, "wonder");
    B(8, "selection");

    DataBase db;
    db.add_table("A", A);
    db.add_table("B", B);

    return db;

}

