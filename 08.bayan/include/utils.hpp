#pragma once 


#include <boost/program_options.hpp>
#include <boost/tokenizer.hpp>

#include <iostream>
#include <string>
#include <set>
#include <vector>


namespace po = boost::program_options;

namespace utils {

    void print_args(po::variables_map &vm) {
        
        if (vm.count("scan")){
            std::cout << "Directories for scan: ";
            for (auto &val : vm["scan"].as<std::vector<std::string>>()){
                std::cout << val << " ";
            }
            std::cout << std::endl;
        }
        if (vm.count("exclude")) {
            std::cout << "Directories excluded from scan: ";
            for (auto &val : vm["exclude"].as<std::vector<std::string>>()){
                std::cout << val << " ";
            }
            std::cout << std::endl;
        }
        if (vm.count("depth")) {
            std::cout << "Depth of scan: " << vm["depth"].as<bool>();
            std::cout << std::endl;
        }
        if (vm.count("size")) {
            std::cout << "Minimal size of scanned files (bytes): " << vm["size"].as<size_t>();
            std::cout << std::endl;
        }
        if (vm.count("block")) {
            std::cout << "Size of block: " << vm["block"].as<size_t>();
            std::cout << std::endl;
        }
        if (vm.count("hash")) {
            std::cout << "Type of hashing: " << vm["hash"].as<std::string>();
            std::cout << std::endl;
        }

    }


    void print_dirs(const std::vector<std::string> &scan_dirs) {
        for (auto &d : scan_dirs) {
            std::cout << d << " ";
        }
        std::cout << std::endl;    
    }


    auto split_string(const std::string &str) {

        const char *PathSeparator = "\\/";
        boost::tokenizer<boost::char_separator<char>> tokenizer{
            str, 
            boost::char_separator<char>{PathSeparator}
        };

        std::vector<std::string> res;
        for (const auto &x : tokenizer) {
            res.emplace_back(x);
        }
        return res;

        // return tokenizer;

    }

} // utils

