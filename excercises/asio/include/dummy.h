#pragma once 


#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <vector>
#include <queue>


class Dummy {
public:
    // void update_line(const char *data, size_t length) {
    //     std::string str = "";

    //     for (size_t i = 0; i < length; ++i) {
    //         str += data[i];
    //     }
    //     m_lines.push_back(str);
    // }
    void update_line(const std::string &line) {
        m_lines.push_back(line);
        if (m_lines.size() >= 3) {
            notify();
        }
    }


    void notify() {
        for (auto &logger : m_loggers) {
            logger->print();
        }
    }

    void attach(DummyLogger)

private:

    std::vector<std::string> m_lines;

};





class DummyLogger {
public:
    void print() {
        lines = m_queue.get_lines();
        for (auto &x : lines) {
            std::cout << x << " ";
        }
        std::cout << std::endl;
        m_lines.clear();
    }

private:
    LineQueue<std::string> m_queue;

};