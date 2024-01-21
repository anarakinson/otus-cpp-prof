
#include <iostream>
#include <vector>
#include <string>



class Bulk {
public:
    Bulk(int N): m_n{N} {}

    // main loop - get lines from std::cin and store in inner vector
    // if vector full - print lines and clear vector
    void loop() {
        while (
            // condition
            std::getline(std::cin, m_line) && 
            m_line != "eof" && 
            m_line != "EOF"
        ) {
            // body of loop
            m_lines.push_back(m_line);
            if (m_lines.size() >= m_n) {
                print_lines();
            }
        }
        // after loop
        if (m_lines.size() > 0){
            print_lines();
        }

    }

private:
    int m_n;
    std::string m_line;
    std::vector<std::string> m_lines;

    // print received lines and clear inner vector 
    void print_lines() {
        std::cout << "bulk: "; 
        for (auto l : m_lines) {
            std::cout << l << " ";
        }
        std::cout << std::endl;
        m_lines.clear();
    }

};


// parse args and return size of block
int get_args(int argc, char **argv) {

    std::string USAGE = "USAGE:\n"
    "bulk N\n"
    "Where N - size of block, integer" 
    "N must be between 0 and 10\n";

    if (argc > 2 || argc < 2) {
        std::cout << USAGE;
        return -1;
    }
    int N = std::stoi(argv[1]);
    std::cout << N << std::endl;
    if (N > 10 || N < 0) {
        std::cout << USAGE;
        return -1;
    }
    return N;

}



int main(int argc, char **argv) {

    int N = get_args(argc, argv);
    if (N == -1) return 1;

    Bulk bulk{N};

    bulk.loop();

    return 0;

}
