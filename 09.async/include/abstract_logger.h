#pragma once 

#include <lockfree_queue.h>

#include <string>
#include <vector>
#include <condition_variable>
#include <thread>
#include <atomic>


using pair_Lines_and_Name = std::pair<std::vector<std::string>, std::string>;

class Bulk;

class iLogger {
public:
    virtual ~iLogger() = default;
    // print received lines (to output or to file)
    virtual void print_lines() = 0;

    /*--------------------- thread ---------------------*/
    // virtual void print_lines_thread(Bulk *owner);

    // std::thread activate() {
    //     return std::thread([&](){ print_lines_thread(); });
    // }

    // static void notify_all() {
    //     m_cv.notify_all();
    // }

    // void flag_down() { m_flag = false; }
    // void flag_up() { m_flag = true; }
    /*------------------------------------------------*/

    // attach logger to some bulk exemplar
    void subscribe(Bulk *bulk) { m_owner = bulk; }

    void attach_queue(LockFreeQueue<pair_Lines_and_Name> *queue) {
        m_queue = queue;
    }

protected:
    Bulk *m_owner;

    bool m_flag = true;
    inline static std::condition_variable_any m_cv{};
    inline static std::mutex m_mutex{};

    LockFreeQueue<pair_Lines_and_Name> *m_queue;

};
