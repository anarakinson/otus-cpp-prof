#pragma once 

#include <utils.hpp>

#include <boost/program_options.hpp>
#include <boost/tokenizer.hpp>
#include <boost/format.hpp>

#include <iostream>
#include <filesystem>
#include <string>
#include <set>
#include <vector>



namespace po = boost::program_options;
namespace fs = std::filesystem;



// remove duplicated directories
void clean_dirs(std::vector<std::string> &dirs) {

    for (auto it = dirs.begin(); it != dirs.end();) {

        if (!fs::exists(*it)) {
            it = dirs.erase(it);
        }
        else {
            ++it;
        }

    }

}


// add specific directoris to list
void extend_dirs(std::vector<std::string> &dirs) {

    size_t counter = 0;
    while (true) {
        
        std::string path = dirs[counter];
        if (fs::exists(path)) { 
            for (const auto &obj : fs::directory_iterator(path)) {
                if (obj.is_directory()) {
                    dirs.emplace_back(obj.path().string());
                }
            }
        }
        ++counter;
        if (counter >= dirs.size()) {
            break;
        }

    }

}


// compare if two paths are the same
bool compare_paths(const std::string &path1, const std::string &path2) {

    auto path1_split = utils::split_string(path1);
    auto path2_split = utils::split_string(path2);

    if (path1_split.size() != path2_split.size()) {
        return false;
    }

    auto it2 = path2_split.begin();
    for (auto it1 = path1_split.begin(); it1 != path1_split.end(); it1++) {
        if (*it1 != *it2) {
            return false;
        }
        it2++;
    }
    return true;

}


// remove specific directoris from list
void exclude_dirs(std::vector<std::string> &dirs, const std::vector<std::string> &excluded) {
    
    for (const auto &str : excluded) {
        auto it = dirs.begin();
        while (it != dirs.end()) {
            if (compare_paths(*it, str)) {
                it = dirs.erase(it);
            } 
            else 
                ++it;
        }
    }

}
