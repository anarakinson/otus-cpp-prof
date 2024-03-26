

#include <iostream>
#include <string>



int main() {

    std::string s1 = "0.0.0.0:5555";

    auto delim = s1.find(":");

    std::string s2 = s1.substr(delim+1, s1.size());
    s1 = s1.substr(0, delim);

    std::cout << s1 << " port: " << s2 << std::endl;

}
