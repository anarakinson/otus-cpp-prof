#pragma once 


#include <utils.h>
#include <abstract_logger.h>
#include <loggers.h>
#include <lockfree_queue.h>

#include <iostream>
#include <vector>
#include <string>


class ThreadManager {
public:
    ThreadManager() {
        
        std::cout << "thread\n";

        m_loggers.push_back(&c_logger);
        m_loggers.push_back(&f_logger1);
        m_loggers.push_back(&f_logger2);

        m_queues.push_back(&file_queue);
        m_queues.push_back(&console_queue);

        // attach queues
        c_logger.attach_queue(&console_queue);
        f_logger1.attach_queue(&file_queue);
        f_logger2.attach_queue(&file_queue);


        std::thread c_thread = c_logger.activate();
        std::thread f_thread1 = f_logger1.activate();
        std::thread f_thread2 = f_logger2.activate();

        m_threads.push_back(std::move(c_thread));
        m_threads.push_back(std::move(f_thread1));
        m_threads.push_back(std::move(f_thread2));

    }

    ~ThreadManager() {
        // start threads
        for (auto &thread : m_threads) {
            thread.join();
        }
    }

 
    std::vector<iLogger*> loggers() { return m_loggers; }
    std::vector<LockFreeQueue<Utils::pair_Lines_and_Name>*> queues() { return m_queues; }


private:

    std::vector<std::thread> m_threads; 
    std::vector<iLogger*> m_loggers; 
    std::vector<LockFreeQueue<Utils::pair_Lines_and_Name>*> m_queues;

    ConsoleLogger c_logger{};
    FileLogger f_logger1{};
    FileLogger f_logger2{};

    LockFreeQueue<Utils::pair_Lines_and_Name> file_queue{};
    LockFreeQueue<Utils::pair_Lines_and_Name> console_queue{};

};