#include <ip_filter.h>

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <exception>
#include <vector>



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
        std::vector<std::array<uint8_t, 4>> ip_pool;

        for (std::string line; std::getline(input, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            std::array<uint8_t, 4> row = convert_row(split(v.at(0), '.'));
            ip_pool.push_back(row);
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


// 24e7a7b2270daee89c64d3ca5fb3da1a  -
// 24e7a7b2270daee89c64d3ca5fb3da1a  -