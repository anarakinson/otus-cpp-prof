#pragma once 

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

