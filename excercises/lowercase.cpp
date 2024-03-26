
#include <iostream>       // std::cout
#include <string>         // std::string
#include <locale>         // std::locale, std::tolower
#include <vector>



std::string to_lower(std::string &str) {
    std::locale loc;
    for (size_t i = 0; i < str.size(); ++i){
        str[i] = std::tolower(str[i], loc);
    }
    return str;
}


// std::pair<std::string, std::string> split(std::string &string, std::string delimiter = " ") {

//     int point = static_cast<int>(string.find(delimiter));
//     std::string first;
//     std::string second;
    
//     if (point == -1) {
//         first = string;
//         second = "";
//     }
//     else {
//         first = string.substr(0, point);
//         second = string.substr(point + delimiter.size(), string.size());
//     }
    
//     return std::make_pair(first, second);

// }



std::vector<std::string> split(std::string &string, std::string delimiter = " ") {

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


int main () {
    
    std::string str="Test StRiNg.\n";    
    str = to_lower(str);

    // auto pair = split(str, " ");

    // std::string first = pair.first;
    // std::string second = pair.second;


    // std::string first;
    // std::string second;

    // // [first, second] = split(str, " ");
    // // std::tie(first, second) = split(str, " ");
    // std::tie(first, second) = split(str, "~");
    
    // std::cout << first << std::endl;
    // std::cout << second;

    auto vec = split(str, " ");
    for (auto x : vec) {
        std::cout << x << std::endl;
    }

}
