#pragma once 

#include <hasher.h>

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>



// function for reading block from disk
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
    for (size_t i = block.size(); i < block_size; ++i) {
        block += "\\0";
    }

    // hash and return block
    return block;

}
