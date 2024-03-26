#include <regex>
#include <iostream>
#include <string>



int main() {

    std::string str = "hello world!";

    std::cout << str << std::endl;

    // str = std::regex_replace(str, std::regex("hello"), "fuck you");

    std::string replaced{"hello"};
    str.replace(str.find(replaced), replaced.length(), "fuck you");

    std::cout << str << std::endl;

}
