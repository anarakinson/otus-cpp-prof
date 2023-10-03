#include <cassert>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <exception>
#include <vector>

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


// vector comparison function
bool vector_cmp(const std::vector<std::string> &ip1, const std::vector<std::string> &ip2) {

    if (ip1 == ip2) {
        return false;
    }
 
    // Compare the octets and return the result
    for (int i = 0; i < 4; i++) {

        if (ip1[i] != ip2[i]) {
            
            size_t ip1_len = ip1[i].length();
            size_t ip2_len = ip2[i].length();
            if (ip1_len != ip2_len) {
                return ip1_len > ip2_len;
            }
            for (size_t j = 0; j < ip1_len; ++j) {
                char a = ip1[i][j] - 48;
                char b = ip2[i][j] - 48;
                if (a != b) {
                    return a > b;
                }
            }

        }

    }
    return false;

}


// function to sort all ip in vector
void sort_ips(std::vector<std::vector<std::string>> &ip_pool) {

    std::sort(ip_pool.begin(), ip_pool.end(), vector_cmp);

}


// function to filter specific byte by value
std::vector<std::vector<std::string>> filter(
    const std::vector<std::vector<std::string>> &ip_pool, 
    int filter_byte_0 = -1, 
    int filter_byte_1 = -1, 
    int filter_byte_2 = -1, 
    int filter_byte_3 = -1
) {

    std::vector<std::vector<std::string>> result{};
    std::vector<std::string> ip_vec{};

    int byte_counter = 0;    
    std::vector<int> filter_bytes{filter_byte_0, filter_byte_1, filter_byte_2, filter_byte_3};
    
    for (std::vector<std::vector<std::string>>::const_iterator ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
    {
        byte_counter = 0;
        ip_vec.clear();
        for (std::vector<std::string>::const_iterator ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
        {
            if (filter_bytes[byte_counter] == -1 || filter_bytes[byte_counter] == stoi(*ip_part)) {
                ip_vec.emplace_back(*ip_part);
            }
            byte_counter++;
        }
        if (ip_vec.size() == 4) {
            result.emplace_back(ip_vec);
        }
    }

    return result;

}


// function to filter any byte by value
std::vector<std::vector<std::string>> filter_any(
    const std::vector<std::vector<std::string>> &ip_pool, 
    int filter_byte = -1
) {

    std::vector<std::vector<std::string>> result{};
    
    for (std::vector<std::vector<std::string>>::const_iterator ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
    {
        if (std::any_of(ip->cbegin(), ip->cend(), [filter_byte](std::string val){ return std::stoi(val) == filter_byte; })) {
            result.emplace_back(*ip);
        }
    }

    return result;

}



void print_results(const std::vector<std::vector<std::string>> &ip_pool) {
    for (std::vector<std::vector<std::string>>::const_iterator ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
    {
        for (std::vector<std::string>::const_iterator ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
        {
            if (ip_part != ip->cbegin())
            {
                std::cout << ".";
            }
            std::cout << *ip_part;
        }
        std::cout << std::endl;
    }

}
