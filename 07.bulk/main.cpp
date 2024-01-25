
#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>



class Bulk {
public:
    Bulk(size_t N): m_n{N} {}

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
            if (m_line == "{") {
                m_braces++;
            } else if (m_line == "}") {
                m_braces--;
                if (m_braces < 0) break;
            } else {
                m_lines.push_back(m_line);
            }
            // if braces closed and vector full:
            if (
                m_lines.size() > 0 && (
                (m_braces == 0 && (m_lines.size() >= m_n || m_line == "}")) || 
                (m_braces == 1 && m_line == "{"))
            ) {
                print_lines();
            }
            // get current time on first command of block
            if (m_lines.size() == 1) { m_filename = get_filename(); }

        }
        // after loop
        if (m_braces == 0 && m_lines.size() > 0){
            print_lines();
        }

    }

private:
    size_t m_n;
    int m_braces = 0;
    std::string m_filename;

    std::string m_line;
    std::vector<std::string> m_lines;


    // print received lines (to output and to file) and clear inner vector 
    void print_lines() {
        display_to_console();
        write_to_file();

        m_lines.clear();
    }

    // display to console
    void display_to_console() {
        std::cout << "bulk: "; 
        for (auto l : m_lines) {
            std::cout << l << " ";
        }
        std::cout << std::endl;

    }

    // write to file
    void write_to_file() {
        std::ofstream new_file{};
        new_file.open("./logs/" + m_filename + ".log");
        new_file << "bulk: "; 
        for (auto l : m_lines) {
            new_file << l << " ";
        }
        new_file << std::endl;
        new_file.close();
    }

    // create new filename - current timestamp
    std::string get_filename() {
        auto now = std::chrono::system_clock::now();
        auto x = std::chrono::duration_cast<std::chrono::seconds>(
            now.time_since_epoch()
        ).count();
        return std::to_string(x);
    }

};


// parse args and return size of block
size_t get_args(int argc, char **argv) {

    std::string USAGE = "USAGE:\n"
    "bulk N\n"
    "Where N - size of block, integer" 
    "N must be between 0 and 10\n";

    if (argc > 2 || argc < 2) {
        std::cout << USAGE;
        return 0;
    }
    size_t N = std::stoull(argv[1]);
    std::cout << N << std::endl;
    if (N > 10 || N <= 0) {
        std::cout << USAGE;
        return 0;
    }
    return N;



}



int main(int argc, char **argv) {

    // create log directory
    std::filesystem::create_directory("./logs");

    // parse arguments
    size_t N = get_args(argc, argv);
    if (N == 0) return 1;

    Bulk bulk{N};

    // start program loop
    bulk.loop();

    return 0;

}
