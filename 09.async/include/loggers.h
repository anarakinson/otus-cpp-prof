#pragma once 

#include <abstract_logger.h>
// #include <bulk.h>
// #include <lockfree_queue.h>

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
// #include <pair>

#define UNUSED(var) (void)(var)



class ConsoleLogger : public iLogger {
public:

    // display to console
    void print_lines(Bulk *m_owner) override {
        
        // std::vector<std::string> lines = m_owner->get_current_lines();
        if (m_queue->size() == 0) return;

        std::pair<std::vector<std::string>, std::string> el = m_queue->pop();
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
    void print_lines(Bulk *m_owner) override {

        // std::vector<std::string> lines = m_owner->get_current_lines();
        if (m_queue->size() == 0) return;

        std::pair<std::vector<std::string>, std::string> el = m_queue->pop();
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
        // std::cout << "FILE LOG" << std::endl;

    }

private: 
    inline static int m_counter = 0;

};


