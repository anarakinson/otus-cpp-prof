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

    static void update_queue(const std::vector<std::string> &lines) {
        m_queue.push(lines);
    }

protected:
    Bulk *m_owner;

    bool m_flag = true;
    inline static std::condition_variable_any m_cv{};
    inline static std::mutex m_mutex{};

    inline static LockFreeQueue<std::vector<std::string>> m_queue{};

};
