#include <iostream>
#include <string>


long long process_data(long long x, std::string &type) {

    long long a, b, c;

    a = x % (256*256*256);
    b = a % (256*256);
    c = b % (256);

    return   x / (256*256*256) + 
            (a / (256*256)) * 256 + 
            (b / 256) * (256*256) + 
             c * (256*256*256);

}


int main() {

    std::string type;
    long long x;

    std::cin >> type;
    std::cin >> x;


    long long result = process_data(x, type);

    std::cout << result << std::endl;

}
