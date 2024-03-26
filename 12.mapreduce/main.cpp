

#include <iostream>
#include <fstream>
#include <vector>
#include <string>


std::vector<std::string> read_file(const std::string &path) {

    std::ifstream file{path};

    std::vector<std::string> out{};
    std::string line;
    
    while(std::getline(file, line)) {
        out.emplace_back(line);
    }

    return out;

}


int fooo() {
    std::ifstream is ("data.txt", std::ifstream::binary);
    if (is) {
        // get length of file:
        is.seekg (0, is.end);
        int length = is.tellg();
        is.seekg (0, is.beg);

        // allocate memory:
        char * buffer = new char [length];

        // read data as a block:
        is.read (buffer,length);

        is.close();

        // print content:
        std::cout.write (buffer,length);

        delete[] buffer;
    }

    return 0;
}


int main() {

    std::cout << "hello" << std::endl;

    auto addresses = read_file("./data.txt");

    for (auto &x : addresses) {
        std::cout << x << "\n";
    }

}