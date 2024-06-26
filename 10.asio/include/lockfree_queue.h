#pragma once 

#include <iostream> 
#include <queue> 
#include <mutex> 


template<typename T>
class LockFreeQueue {
public:
    void push( const T& value ) {
        // std::cout << "PUSH" << m_queue.size() << std::endl;
        std::lock_guard<std::mutex> lock(m_mutex);
        m_queue.push(value);
    }

    T pop() {
        // std::cout << "POP\n" << m_queue.size() << std::endl;
        std::lock_guard<std::mutex> lock(m_mutex);
        T val = m_queue.front();
        m_queue.pop();
        return val;
    }

    T front() {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_queue.front();
    }

    std::atomic<size_t> size() { return m_queue.size(); }

private:
    std::queue<T> m_queue;
    mutable std::mutex m_mutex;

};

