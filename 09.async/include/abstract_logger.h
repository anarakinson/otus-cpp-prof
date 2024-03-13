#pragma once 

#include <lockfree_queue.h>

#include <iostream>
#include <string>
#include <vector>
#include <condition_variable>
#include <thread>
#include <atomic>



class Bulk;

class iLogger {
public:    
    virtual ~iLogger() = default;
    // print received lines (to output or to file)
    virtual void print_lines() = 0;

    /*--------------------- thread ---------------------*/
    void print_lines_thread() {
        while(true) {

            std::unique_lock<std::mutex> guard{m_mutex};
            if (m_flag_stop && (m_queue->size() == 0)) break;
            m_cv.wait(guard, [&]() { return !(m_queue->size() == 0); });

            // loggers logic 
            print_lines();
            notify_one();

        }
    }

    std::thread activate() {
        // std::cout << "Start thread\n";
        return std::thread([&](){ print_lines_thread(); });
    }
    /*------------------------------------------------*/

    // attach logger to some queue
    void attach_queue(LockFreeQueue<Utils::pair_Lines_and_Name> *queue) {
        m_queue = queue;
    }

    void flag_stop() { m_flag_stop = true; }

    static void notify_one() {
        m_cv.notify_one();
    }

protected:
    LockFreeQueue<Utils::pair_Lines_and_Name> *m_queue;

    // for threading
    std::atomic<bool> m_flag_stop = false;
    inline static std::condition_variable_any m_cv{};
    std::mutex m_mutex{};

};
