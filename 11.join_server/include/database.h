
#pragma once

#include <table.h>
#include <utils.h>

#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <set>



class DataBase {
public:

    void add_table(std::string name, Table table);
    // query parsing - 
    // get string query and 
    // return string output
    std::string operator () (std::string &query);

private:
    
    // internal data
    std::map<std::string, Table> m_data;

    // --------------------------- //
    std::string query_show(std::string &table_name);
    std::string query_insert(std::vector<std::string> &words);
    std::string query_truncate(std::string &table_name);

    std::string query_intersection(
        const std::string &first_table = "A", 
        const std::string &second_table = "B"
    );
    std::string query_symm_diff(
        const std::string &first_table = "A", 
        const std::string &second_table = "B"
    );

    // utility function for beautiful printing table difference and intersection
    std::string print_table_comparison(
        std::set<int>,
        const std::string &first_table = "A", 
        const std::string &second_table = "B"
    );
    
};



// function for fill testing data
inline DataBase create_dummy_database() {

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

