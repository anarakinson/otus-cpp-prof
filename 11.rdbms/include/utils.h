
#pragma once 


#include <iostream>
#include <string>
#include <vector>
#include <locale>         // std::locale, std::tolower



namespace Utils {

    inline std::string to_lower(std::string &str) {
        std::locale loc;
        for (size_t i = 0; i < str.size(); ++i){
            str[i] = std::tolower(str[i], loc);
        }
        return str;
    }


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

    inline std::string space(int len) {
        std::string out{};
        for (int i = 0; i < len; ++i) {
            out += " ";
        }
        return out;
    }

} // Utils