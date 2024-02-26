#pragma once 

#include <read_block.h>
#include <utils.h>

#include <boost/program_options.hpp>
#include <boost/tokenizer.hpp>

#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <map>
#include <vector>



namespace po = boost::program_options;
namespace fs = std::filesystem;



class Comparator {
public:

    Comparator() = delete;
    Comparator(
        size_t block_size,
        const std::vector<std::string> &scan_dirs 
    ) : 
        block_size{block_size},
        scan_dirs{scan_dirs} 
        {}
    ~Comparator() = default;
    

    // if block is in inner cash - load, 
    // else - read from disk
    std::string read_or_load_block(const std::string path, size_t block_number) {
        std::string block;
        if (current_objects[path].size() <= block_number) {
            // std::cout << "READ" << std::endl;
            block = read_method(path, block_size, block_number);
            current_objects[path].push_back(block);
        } 
        else {
            // std::cout << "LOAD" << std::endl;
            block = current_objects[path][block_number];
        }
        return block;
    } 


    // compare two files
    bool compare(const std::string path1, const std::string path2) {
        
        if (fs::file_size(path1) != fs::file_size(path2)) {
            return false;
        } 

        size_t block_num = 0;

        while (true) {
            std::string block1 = read_or_load_block(path1, block_num);
            std::string block2 = read_or_load_block(path2, block_num);
            // std::cout << path1 << " " << path2 << " " << std::endl;
            // std::cout << " " << block1 << " " << block2 << std::endl;
            if (block1.size() == 0 || block2.size() == 0) {
                break;
            }

            if (block1 != block2) {
                return false;
            }

            ++block_num;
        }
        return true; 

    }


    void inner_loop(
        const std::filesystem::directory_entry &obj1,
        std::vector<std::vector<std::string>> &results
    ) 
    {
        // temporary result list
        std::vector<std::string> current_results;
        // clear cashed files
        // current_objects.clear();
    
        // if path is not file 
        // or path already checked - pass
        if (checked_obj.count(obj1) || obj1.is_directory()) {
            return;
        }
        current_results.emplace_back(obj1.path().string());

        for (const std::string &path2 : scan_dirs) {
            for (const auto &obj2 : fs::directory_iterator(path2)) {
                
                // if path is not file 
                // or path1 and path2 are the same 
                // or path already checked - pass
                if ( 
                    obj2.is_directory() ||
                    obj1.path() == obj2.path() ||
                    checked_obj.count(obj2)
                ) continue;

                // compare files
                bool same_files = compare(obj1.path().string(), obj2.path().string()); 
                // if files are the the same - store in results
                if (same_files) {
                    current_results.emplace_back(obj2.path().string());
                    checked_obj.emplace(obj2);
                }
            }
            // update list of already checked files
            checked_obj.emplace(obj1);
        }
        // store in results
        results.emplace_back(current_results);

    }


    void path_loop(
        std::vector<std::vector<std::string>> &results
    ) 
    {
        // set to contain already checked paths
        checked_obj.clear();
        
        for (const std::string &path : scan_dirs) {
            for (const auto &obj : fs::directory_iterator(path)) {
                
                inner_loop(obj, results);

            }
        }
    }


    void set_read_method(std::string (*new_method)(const std::string, size_t, size_t)) {
        read_method = new_method;
    }



private:

    std::set<fs::directory_entry> checked_obj;
    std::vector<std::string> scan_dirs; 
    size_t block_size;

    // cashed data
    std::map<std::string, std::vector<std::string>> current_objects{};

    // read data method
    std::string (*read_method)(const std::string, size_t, size_t) = read_block;

};

