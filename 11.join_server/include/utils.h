
#pragma once 


#include <iostream>
#include <string>
#include <vector>
#include <locale>         // std::locale, std::tolower



namespace Utils {

    // lower string
    inline std::string to_lower(std::string &str) {
        std::locale loc;
        for (size_t i = 0; i < str.size(); ++i){
            str[i] = std::tolower(str[i], loc);
        }
        return str;
    }

    // split string to vector of words
    inline std::vector<std::string> split(std::string &string, std::string delimiter = " ") {

        std::string word = "";
        std::vector<std::string> out;

        for (auto ch : string) {
            if (ch == ' ' || ch == '\n') {
                out.push_back(word);
                word = "";
            }
            else word += ch;
        }
        return out;

    }

    // make space filled with specific char (default - ' ')
    inline std::string space(size_t len, char ch = ' ') {
        return std::string( len, ch );
    }

} // Utils
