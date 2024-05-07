#pragma once 

#include <ilogger.h>
// #include <bulk.h>
// #include <multithread_queue.h>

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#define UNUSED(var) (void)(var)



class ConsoleLogger : public iLogger {
public:

    // display to console
    void print_lines() override {
        
        if (m_queue->size() == 0) return;

        Utils::pair_Lines_and_Name el = m_queue->pop();
        std::vector<std::string> lines = el.first;
        std::string filename = el.second;

        std::cout << "bulk: "; 
        for (auto l : lines) {
            std::cout << l << " ";
        }
        std::cout << std::endl;

    }

private: 

};


class FileLogger : public iLogger {
public:

    // write to file
    void print_lines() override {

        if (m_queue->size() == 0) return;

        Utils::pair_Lines_and_Name el = m_queue->pop();
        std::vector<std::string> lines = el.first;
        std::string filename = el.second;

        std::ofstream new_file{};
        new_file.open("./logs/" + filename + "-" + Utils::id_to_string() + "-" + std::to_string(m_counter++) + ".log");
        new_file << "bulk: "; 
        for (auto l : lines) {
            new_file << l << " ";
        }
        new_file << std::endl;
        new_file.close();

        // using namespace std::chrono_literals;
        // std::this_thread::sleep_for(1us);
        // std::cout << "FILE LOG " << std::this_thread::get_id() << std::endl;

    }

private: 
    inline static int m_counter = 0;

};


