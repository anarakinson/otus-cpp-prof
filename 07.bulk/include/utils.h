#pragma once 


#include <iostream>
#include <string>
#include <chrono>

namespace Utils {

    
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


    // create new filename - current timestamp
    std::string get_filename() {
        auto now = std::chrono::system_clock::now();
        auto x = std::chrono::duration_cast<std::chrono::seconds>(
            now.time_since_epoch()
        ).count();
        return std::to_string(x);
    }


} // namespace Utils