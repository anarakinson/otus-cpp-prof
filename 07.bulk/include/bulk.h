#pragma once 

#include <logger.h>

#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>


class Bulk {
public:
    Bulk(size_t N): m_n{N} {}

    // main loop - get lines from std::cin and store in inner vector
    // if vector full - print lines and clear vector
    void loop() {
        while (
            // condition
            std::getline(std::cin, m_line) && 
            m_line != "eof" && 
            m_line != "EOF"
        ) {

            // body of loop
            if (m_line == "{") {
                m_braces++;
            } else if (m_line == "}") {
                m_braces--;
                if (m_braces < 0) break;
            } else {
                m_lines.push_back(m_line);
            }
            // if braces closed and vector full:
            if (
                m_lines.size() > 0 && (
                (m_braces == 0 && (m_lines.size() >= m_n || m_line == "}")) || 
                (m_braces == 1 && m_line == "{"))
            ) {
                notify();
            }
            // get current time on first command of block
            if (m_lines.size() == 1) { m_filename = get_filename(); }

        }
        // after loop
        if (m_braces == 0 && m_lines.size() > 0){
            notify();
        }

    }

    void attach(Logger *logger) {
        m_loggers.push_back(logger);
    }


private:
    size_t m_n;
    int m_braces = 0;
    std::string m_filename;

    std::string m_line;
    std::vector<std::string> m_lines;
    std::vector<Logger*> m_loggers;

    void notify() {

        for (auto logger : m_loggers) {
            logger->print_lines(m_lines, m_filename);
        }
        m_lines.clear();

    }

    
    // create new filename - current timestamp
    std::string get_filename() {
        auto now = std::chrono::system_clock::now();
        auto x = std::chrono::duration_cast<std::chrono::seconds>(
            now.time_since_epoch()
        ).count();
        return std::to_string(x);
    }

};
