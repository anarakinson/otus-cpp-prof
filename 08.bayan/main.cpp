
#include <argparse.h>
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





void path_loop(const std::vector<std::string> &scan_dirs, std::function<void(fs::directory_entry, fs::directory_entry)> comparator) {

    // set to contain already checked paths
    std::set<fs::directory_entry> checked_obj;
    
    for (const std::string &path1 : scan_dirs) {
        for (const auto &obj1 : fs::directory_iterator(path1)) {
            
            for (const std::string &path2 : scan_dirs) {
                for (const auto &obj2 : fs::directory_iterator(path2)) {
                    if ( 
                        (obj1.is_directory() || 
                        obj2.is_directory()) ||
                        obj1.path() == obj2.path() ||
                        checked_obj.count(obj2)
                    ) continue;
                    comparator(obj1, obj2); 
                }
                checked_obj.emplace(obj1);
            }
        
        }
    }

}


int main(int argc, char** argv) {

    /*----- parse arguments -----*/
    po::variables_map vm = parse_args(argc, argv);
    if (vm.size() == 0){
        return 0;
    }

    print_args(vm);
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

    // go through directories and compare files
    path_loop(
        scan_dirs, 
        // comparator
        [](fs::directory_entry a, fs::directory_entry b){ 
            std::cout << a.path() << " " << b.path() << " " << std::endl; 
            return; 
        }
    );


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
