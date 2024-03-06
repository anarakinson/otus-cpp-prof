#pragma once 

#include <lockfree_queue.h>

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
    virtual void print_lines(Bulk*) = 0;
    // attach logger to some bulk exemplar
    void subscribe(Bulk *bulk) { m_owner = bulk; }

    void attach_queue(LockFreeQueue<std::pair<std::vector<std::string>, std::string>> *queue) {
        m_queue = queue;
    }

protected:
    Bulk *m_owner;

    bool m_flag = true;
    inline static std::condition_variable_any m_cv{};
    inline static std::mutex m_mutex{};

    LockFreeQueue<std::pair<std::vector<std::string>, std::string>> *m_queue;

};
