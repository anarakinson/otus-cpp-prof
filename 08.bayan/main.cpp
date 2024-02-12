
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

po::variables_map parse_args(int argc, char** argv) {

    try {
        
        po::options_description descr{"Options"};
        descr.add_options()
                ("help,h", "This screen")
                ("scan,s", po::value<std::vector<std::string>>()->multitoken()->default_value({"."}, "."), "Directories for scan")
                ("exclude,x", po::value<std::vector<std::string>>()->multitoken(), "Directories excluded from scan")
                ("depth,d", po::value<bool>()->default_value(0), "Depth of scan: 1-all subdirs, 0-only specified")
                ("size", po::value<size_t>()->default_value(1), "Minimal size of scanned files (bytes)")
                ("block", po::value<size_t>()->default_value(4), "Size of block")
                ("hash", po::value<std::string>()->default_value("md5"), "Type of hashing")
        ;

        po::variables_map vm;
        po::store(parse_command_line(argc, argv, descr), vm);
        po::notify(vm);


        if (vm.count("help")){
            std::cout << descr << std::endl;
            return {};
        }

        return vm;

    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        return {};
    }
    
}


void print_args(po::variables_map &vm) {
    
    if (vm.count("scan")){
        std::cout << "Directories for scan: ";
        for (auto &val : vm["scan"].as<std::vector<std::string>>()){
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
    if (vm.count("exclude")) {
        std::cout << "Directories excluded from scan: ";
        for (auto &val : vm["exclude"].as<std::vector<std::string>>()){
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
    if (vm.count("depth")) {
        std::cout << "Depth of scan: " << vm["depth"].as<bool>();
        std::cout << std::endl;
    }
    if (vm.count("size")) {
        std::cout << "Minimal size of scanned files (bytes): " << vm["size"].as<size_t>();
        std::cout << std::endl;
    }
    if (vm.count("block")) {
        std::cout << "Size of block: " << vm["block"].as<size_t>();
        std::cout << std::endl;
    }
    if (vm.count("hash")) {
        std::cout << "Type of hashing: " << vm["hash"].as<std::string>();
        std::cout << std::endl;
    }

}


void print_dirs(const std::vector<std::string> &scan_dirs) {
    for (auto &d : scan_dirs) {
        std::cout << d << " ";
    }
    std::cout << std::endl;    
}




void extend_dirs(std::vector<std::string> &dirs) {

    for (const std::string &path : dirs) {
        for (const auto &obj : fs::directory_iterator(path)) {
            if (obj.is_directory()) {
                dirs.emplace_back(obj.path().string());
            }
        }
    }

}


void exclude_dirs(std::vector<std::string> &dirs, const std::vector<std::string> &excluded) {

    auto ib = excluded.begin();
    auto iter = std::remove_if (
        std::begin(dirs), 
        std::end(dirs),
        [&](std::string x) -> bool {
                while  (ib != excluded.end()) ++ib;
                return (ib != excluded.end() && *ib == x);
            }
        );

}




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


    print_dirs(scan_dirs);
    // extending directories
    if (vm["depth"].as<bool>() == true) { extend_dirs(scan_dirs); } 
    print_dirs(scan_dirs);
    // excluding directories
    exclude_dirs(scan_dirs, vm["exclude"].as<std::vector<std::string>>());
    print_dirs(scan_dirs);

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
