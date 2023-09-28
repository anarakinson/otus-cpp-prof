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
        if (stoi(ip1[i]) > stoi(ip2[i])) {
            return true;
        } else if (stoi(ip1[i]) < stoi(ip2[i])) {
            return false;
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


/*----------------------------------------------------------------------------*/
int main(int argc, const char *argv[])
{
    try
    {
        // check arguments
        if (argc <= 1) {
            std::cerr << "\n\tMissing argument: filepath\n" 
                      << "\tUsage: ip_filter /path/to/file.txt\n" << std::endl;
            return 1;
        }

        // open file
        std::ifstream input{argv[1]};
        if (!input.is_open()) { throw std::runtime_error("\n\tUnable to open file\n"); }

        // read file
        std::vector<std::vector<std::string> > ip_pool;

        for (std::string line; std::getline(input, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        // TODO reverse lexicographically sort
        sort_ips(ip_pool);

        //* ------ print results ------ *//
        // all ip
        print_results(ip_pool);
        // ip starts with '1.'
        { 
            auto ip_pool_filtered = filter(ip_pool, 1);
            print_results(ip_pool_filtered);
        }
        // ip starts with '46.70.'
        { 
            auto ip_pool_filtered = filter(ip_pool, 46, 70);
            print_results(ip_pool_filtered);
        }
        // ip contains 46
        { 
            auto ip_pool_filtered = filter_any(ip_pool, 46);
            print_results(ip_pool_filtered);
        }

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        // ip = filter(1)

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
