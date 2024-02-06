#pragma once 

#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>

#define UNUSED(var) (void)(var)


class Logger {
public:
    virtual ~Logger() = default;
    // print received lines (to output and to file) and clear inner vector 
    virtual void print_lines(std::vector<std::string> lines, std::string filename) = 0;
private:

};


class ConsoleLogger : public Logger {
public:

    // display to console
    void print_lines(std::vector<std::string> lines, std::string filename) override {
        UNUSED(filename);
        std::cout << "bulk: "; 
        for (auto l : lines) {
            std::cout << l << " ";
        }
        std::cout << std::endl;

    }

};


class FileLogger : public Logger {
public:

    // write to file
    void print_lines(std::vector<std::string> lines, std::string filename) override {
        std::ofstream new_file{};
        new_file.open("./logs/" + filename + ".log");
        new_file << "bulk: "; 
        for (auto l : lines) {
            new_file << l << " ";
        }
        new_file << std::endl;
        new_file.close();
    }

};


