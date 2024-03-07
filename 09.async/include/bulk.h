#pragma once 

#include <utils.h>
#include <abstract_logger.h>
#include <loggers.h>
#include <lockfree_queue.h>

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
            process_line();
        }
        // after loop
        finish_processing();
    }


    // get new char
    void update_line(char ch) {
        if (ch == '\n') {
            process_line();
            m_line = "";
        }
        else m_line += ch;
    }


    void finish_processing() {    
        if (m_braces == 0 && m_lines.size() > 0){    
            notify();
        }
        stop();
    }


    void process_line() {

        if (m_line == "{") {
            m_braces++;
        } else if (m_line == "}") {
            m_braces--;
            if (m_braces < 0) return;
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


    void stop() {
        for (auto l : m_loggers) {
            l->flag_stop();
            // std::cout << "STOP\n";
        }
    }


    // attaching loggers to bulk exemplar
    void attach(iLogger *logger) {
        // logger->subscribe(this);
        m_loggers.push_back(logger);
    }

    // attaching loggers to bulk exemplar
    void attach_queue(LockFreeQueue<Utils::pair_Lines_and_Name> *queue) {
        m_queues.push_back(queue);
    }


private:
    size_t m_n;
    int m_braces = 0;
    std::string m_filename;

    std::string m_line;
    std::vector<std::string> m_lines;

    std::vector<iLogger*> m_loggers;
    std::vector<LockFreeQueue<Utils::pair_Lines_and_Name>*> m_queues;


    // notification for loggers
    void notify() {

        for (auto queue : m_queues) {
            queue->push(std::make_pair(m_lines, get_current_filename()));
        }
        m_lines.clear();

    }


    // functions for sharing data with loggers
    std::string get_current_filename() {
        // in case of bulk_size == 1 - return current moment.
        // else - return moment of start sequence
        return m_filename != "" ? m_filename : Utils::get_filename();
    }

};
