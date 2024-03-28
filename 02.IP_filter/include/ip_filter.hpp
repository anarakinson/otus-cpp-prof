#include <cassert>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <exception>
#include <vector>
#include <array>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}


// convert string array to uint8 array
std::array<uint8_t, 4> convert_row(const std::vector<std::string> &row) {

    std::array<uint8_t, 4> output;
    for (int i = 0; i < 4; ++i) {
        output[i] = stoi(row[i]);
    }
    return output;

}


// vector comparison function
bool vector_cmp(const std::array<uint8_t, 4> &ip1, const std::array<uint8_t, 4> &ip2) {

    if (ip1 == ip2) {
        return false;
    }
 
    // Compare the octets and return the result
    for (int i = 0; i < 4; i++) {

        if (ip1[i] > ip2[i]) {
            return true;
        } 
        else if (ip1[i] < ip2[i]) {
            return false;
        }

    }
    return false;

}


// function to sort all ip in vector
void sort_ips(std::vector<std::array<uint8_t, 4>> &ip_pool) {

    std::sort(ip_pool.begin(), ip_pool.end(), vector_cmp);

}


// function to filter specific byte by value
std::vector<std::array<uint8_t, 4>> filter(
    const std::vector<std::array<uint8_t, 4>> &ip_pool, 
    int filter_byte_0 = -1, 
    int filter_byte_1 = -1, 
    int filter_byte_2 = -1, 
    int filter_byte_3 = -1
) {

    std::vector<std::array<uint8_t, 4>> result{}; 
    std::vector<int> filter_bytes{filter_byte_0, filter_byte_1, filter_byte_2, filter_byte_3};
    
    for (const auto &row : ip_pool) {
        if (
            (filter_bytes[0] == -1 || filter_bytes[0] == row[0]) &&
            (filter_bytes[1] == -1 || filter_bytes[1] == row[1]) &&
            (filter_bytes[2] == -1 || filter_bytes[2] == row[2]) &&
            (filter_bytes[3] == -1 || filter_bytes[3] == row[3])
        ) {
            result.emplace_back(row);
        }
    }

    return result;

}


// function to filter any byte by value
std::vector<std::array<uint8_t, 4>> filter_any(
    const std::vector<std::array<uint8_t, 4>> &ip_pool, 
    int filter_byte = -1
) {

    std::vector<std::array<uint8_t, 4>> result{};
    
    for (std::vector<std::array<uint8_t, 4>>::const_iterator ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
    {
        if (std::any_of(ip->cbegin(), ip->cend(), [filter_byte](int val){ return int(val) == filter_byte; })) {
            result.emplace_back(*ip);
        }
    }

    return result;

}



void print_results(const std::vector<std::array<uint8_t, 4>> &ip_pool) {
    for (std::vector<std::array<uint8_t, 4>>::const_iterator ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
    {
        for (std::array<uint8_t, 4>::const_iterator ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
        {
            if (ip_part != ip->cbegin())
            {
                std::cout << ".";
            }
            std::cout << int(*ip_part);
        }
        std::cout << std::endl;
    }

}
