
#include <database.h>



void DataBase::add_table(std::string name, Table table) {
    m_data[name] = table;
}


std::string DataBase::operator () (std::string &query) {
    
    // split query into vector of words and lower it
    auto words = Utils::split(query);
    auto first_word = Utils::to_lower(words[0]);
    
    // print HELP info
    if (first_word == "help" && words.size() == 1) {
        return std::string(
            "\nCOMMANDS:\n\n"
            "  INSERT table id name\n"
            "  TRUNCATE table\n"
            "  INTERSECTION\n"
            "  SYMMETRIC_DIFFERENCE\n"
            "  SHOW table\n"
            "  EXIT\n"
        );
    } 
    
    // print table
    else if (first_word == "show" && words.size() == 2) {
        return query_show(words[1]);
    } 

    // insert data iinto table
    else if (first_word == "insert" && words.size() == 4) {
        return query_insert(words);
    } 
    
    // clear table
    else if (first_word == "truncate" && words.size() == 2) {
        return query_truncate(words[1]);
    } 
    
    // show intersection between tables
    else if (first_word == "intersection" && words.size() == 1) {
        return query_intersection();
    } 
    
    // show difference between tables
    else if (first_word == "symmetric_difference" && words.size() == 1) {
        return query_symm_diff();
    } 
    
    else {
        return std::string{"Unrecognized query!"};
    }

}


//------------------------------------------------------------------------------------//
    

std::string DataBase::query_show(std::string &table_name) {
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


std::string DataBase::query_insert(std::vector<std::string> &words) {
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


std::string DataBase::query_truncate(std::string &table_name) {
    if (!m_data.count(table_name)) {
        return "Table does not exist!";
    }
    m_data[table_name].clear();
    return "OK!";
}


std::string DataBase::query_intersection(const std::string &first_table, const std::string &second_table) {

    auto A_keys = m_data[first_table].keys(); 
    auto B_keys = m_data[second_table].keys();

    auto intersection = std::set<int>{};
    // get the intersection
    std::set_intersection(A_keys.begin(), A_keys.end(), B_keys.begin(), B_keys.end(), std::inserter(intersection, intersection.begin()));

    std::string out = print_table_comparison(intersection);
    return out;
}


std::string DataBase::query_symm_diff(const std::string &first_table, const std::string &second_table) {

    auto A_keys = m_data[first_table].keys(); 
    auto B_keys = m_data[second_table].keys();

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

    std::string out = print_table_comparison(difference);
    return out;
}


std::string DataBase::print_table_comparison(
    std::set<int> idx, 
    const std::string &first_table, 
    const std::string &second_table
    ) {

    // get size fot table header
    size_t space_size = 0;
    if (m_data[first_table].max_len() > first_table.size()){
        space_size = m_data[first_table].max_len() - first_table.size();
    }

    // make output table 
    std::string out{
        "\n"
        "id | " + first_table + Utils::space(space_size) + " | " + second_table + " \n"
        "---+-" + Utils::space(m_data[first_table].max_len(), '-') + "-+-" + Utils::space(m_data[second_table].max_len(), '-') + "-\n"
    };

    for (auto id : idx) {    
        auto A_name = m_data[first_table][id];  
        A_name += Utils::space(m_data[first_table].max_len() - A_name.size());
        
        out += id > 10 ? "" : " ";
        out += std::to_string(id) + " | " + A_name + " | " + m_data[second_table][id] + "\n";
    }

    return out;

}
