
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <regex>



namespace fs = std::filesystem;


std::string read_block(const std::string path, size_t block_size, size_t block_number) {
    
    std::ifstream file{path};

    // if file didn't open - return empty string;
    if (!file.is_open()) {
        return {};
    }
    /* ---------------------- */
    
    block_number *= block_size;
    char ch;
    std::string block{};  // empty string represents block
    size_t counter = 0;

    // iterate on file char by char
    while (file.get(ch)) {
        // if number of block is not reached - do nothing
        if (counter >= block_number) {
            block += ch;
            // when block size is sufficient - return block
            if (block.size() == block_size) {
                return block;
            }
        }
        counter++;
    }
    // if file is ended - return empty string
    if (block.size() == 0) {
        return {};
    }
    // if size of block is not sufficient - fill it with \0
    for (int i = block.size(); i < block_size; ++i) {
        block += "\\0";
    }
    return block;

}



bool compare_files(const std::string path1, const std::string path2, size_t block_size) {
    
    // if (fs::file_size(path1) != fs::file_size(path2)) {
    //     return false;
    // } 

    size_t block_num = 0;

    while (true) {
        std::string block1 = read_block(path1, block_size, block_num);
        std::string block2 = read_block(path2, block_size, block_num);
        std::cout << block1 << " " << block2 << std::endl;
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


int main() {

    size_t N = 5;
    size_t block_num = 7;
    // auto vec = read_block("./test3/test.txt", N, block_num);

    // std::cout << vec.size() << std::endl;

    // for (auto block : vec) {
    //     std::cout << block << " ";
    // }


    bool out = false;
    out = compare_files("./test3/test.txt", "./test3/test.txt", N);

    std::cout << " >>> " << out;

}