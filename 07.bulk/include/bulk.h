#pragma once 

#include <abstract_logger.h>


#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <string>



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
            if (m_lines.size() == 1) { m_filename = Utils::get_filename(); }

        }
        // after loop
        if (m_braces == 0 && m_lines.size() > 0){
            notify();
        }

    }

    // attaching loggers to bulk exemplar
    void attach(iLogger *logger) {
        logger->subscribe(this);
        m_loggers.push_back(logger);
    }


private:
    size_t m_n;
    int m_braces = 0;
    std::string m_filename;

    std::string m_line;
    std::vector<std::string> m_lines;

    std::vector<iLogger*> m_loggers;


    // notification for loggers
    void notify() {

        for (auto logger : m_loggers) {
            logger->print_lines();
        }
        m_lines.clear();

    }


    // functions for sharing data with loggers
    std::string get_current_filename() {
        return m_filename;
    }
    std::vector<std::string> get_current_lines() {
        return m_lines;
    }

    // get friends to acces private data
    friend class ConsoleLogger;
    friend class FileLogger;

};
