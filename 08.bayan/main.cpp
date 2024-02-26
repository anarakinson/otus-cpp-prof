
#include <argparse.h>
#include <comparator.h>
#include <paths.h>
#include <utils.h>

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



int main(int argc, char** argv) {

    /*----- parse arguments -----*/
    po::variables_map vm = parse_args(argc, argv);
    if (vm.size() == 0){
        return 0;
    }

    utils::print_args(vm);
    std::cout << std::endl;
    /*----- *** -----*/

    std::vector<std::string> scan_dirs = vm["scan"].as<std::vector<std::string>>(); 


    // extending directories
    if (vm["depth"].as<bool>() == true) { extend_dirs(scan_dirs); } 
    
    // delete not existed dirs
    clean_dirs(scan_dirs);
    
    // exclude directories
    if (vm.count("exclude")){
        exclude_dirs(scan_dirs, vm["exclude"].as<std::vector<std::string>>());
    } 


    // vector to store results
    std::vector<std::vector<std::string>> results{};

    // create comparator, 
    // stored directory list and size of block
    Comparator comparator{vm["block"].as<size_t>(), scan_dirs};
    // go through directories and compare files
    comparator.path_loop(results);


    // Display results
    std::cout << "Results:\n" << std::endl;

    for (auto res : results) {
        for (auto x : res) {
            std::cout << x << "\n";
        }
        std::cout << std::endl;
    }

    return 0;

}




/*


Утилита должна иметь возможность через параметры командной строки
указывать
• директории для сканирования (может быть несколько)
• директории для исключения из сканирования (может быть несколько)
• уровень сканирования (один на все директории, 0 - только указанная
директория без вложенных)
• минимальный размер файла, по умолчанию проверяются все файлы
больше 1 байта.
• маски имен файлов разрешенных для сравнения (не зависят от
регистра)
• размер блока, которым производится чтения файлов, в задании этот
размер упоминается как S
• один из имеющихся алгоритмов хэширования (crc32, md5 -
конкретные варианты определить самостоятельно), в задании
эта функция упоминается как H


*/