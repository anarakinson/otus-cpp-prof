
#include <iostream> 
#include <fstream>
#include <string> 
#include <vector> 
#include <mutex> 
#include <atomic> 
#include <thread> 
#include <condition_variable> 



class cMutex : std::mutex {
public:
    cMutex() {
        std::cout << "create mutex" << std::endl;
    }
  
    void lock() {
        m_mutex.lock();
        // std::cout << "mutex locked by thread_id: " << std::this_thread::get_id()
                    // << std::endl;
    }

    void unlock() {
        // std::cout << "mutex unlocked by thread_id: " 
        //             << std::this_thread::get_id()
        //             << std::endl;
        m_mutex.unlock();
    }
  
private:
    std::mutex m_mutex;

};


class Bulk;

class iLogger {
public:

    virtual ~iLogger() = default;

    virtual void print_lines() = 0; 
    
    std::thread activate() {
        return std::thread([&](){ print_lines(); });
    }
    
    void subscribe(Bulk *b) {
        m_owner = b;
    }

    void flag_down() { m_flag = false; }
    void flag_up() { m_flag = true; }

protected:
    Bulk *m_owner;
    bool m_flag = false;

};



class Bulk {

    inline static std::condition_variable_any m_cv{};
    inline static cMutex m_mutex{};

public:
    void loop() {
        reset_queue();
        while (
            // condition
            std::getline(std::cin, m_line) && 
            m_line != "eof" && 
            m_line != "EOF"
        )
        {

            m_counter++;
            m_lines.push_back(m_line);

            std::cout << "m_lines: " << m_lines.size() << " finished: " << m_finished << " loggers: " << m_loggers.size() << std::endl;

            if (m_counter >= 3) {
                notify();

                // std::unique_lock<cMutex> lock{m_mutex};
                // m_cv.wait(lock, [&](){ return (m_finished != m_loggers.size()); });
                while(m_finished != m_loggers.size()) { std::cout << "-"; }        
                reset_queue();
            }

        }
    }


    void attach(iLogger *logger) {
        logger->subscribe(this);
        m_loggers.push_back(logger);
    }


private:

    size_t m_counter = 0;
    std::string m_line;
    std::vector<std::string> m_lines;

    std::atomic<int> m_finished = 0;
    

    std::vector<iLogger*> m_loggers;

    void notify() {
    //     m_logger->print_lines();
        std::cout << "notify from thread " << std::this_thread::get_id()  << m_finished << " << " << m_loggers.size() << std::endl;
        m_cv.notify_all();
    }

    void reset_queue() {
        m_lines.clear();
        m_counter = 0;

        for (auto &l : m_loggers) {
            l->flag_down();
        }
        m_finished = 0;
        std::cout << "reset_queue << " << m_finished << " << " << m_loggers.size() << "\n";
    }

    void flag_down() { 
        m_finished++;
        std::cout << "OWNER flag down" << m_finished << " << " << m_loggers.size() << "\n";
    }

    std::vector<std::string> get_lines() {
        return m_lines;
    }

    friend class Logger;
    friend class FileLogger;

};




class Logger : public iLogger {

public:

    void print_lines() override {
        while (true) {

            // work logic
            for (auto line : m_owner->get_lines()) {
                std::cout << line << " ";
            }
            std::cout << std::endl;

            flag_up();
            m_owner->flag_down();
        
            std::unique_lock<cMutex> guard{m_owner->m_mutex};
            m_owner->m_cv.wait(guard, [&]() { return !m_flag; });
            std::cout << "Logger work from thread " << std::this_thread::get_id() << std::endl;

        }
    }
    

};



class FileLogger : public iLogger {
public:

    // write to file
    void print_lines() override {
        while (true) {
            
            // std::cout << "hello" << std::endl;
            
            // work logic
            std::vector<std::string> lines = m_owner->get_lines();
            std::ofstream new_file{};
            new_file.open("./logs/" + std::to_string(m_number++) + ".log");
            new_file << "bulk: "; 
            for (auto l : lines) {
                new_file << l << " ";
            }
            new_file << std::endl;
            new_file.close();
            
            flag_up();
            m_owner->flag_down();

            std::unique_lock<cMutex> guard{m_owner->m_mutex};
            m_owner->m_cv.wait(guard, [&]() { return !m_flag; });
            std::cout << "FileLogger work from thread " << std::this_thread::get_id() << std::endl;

        }
    }

private:
    inline static int m_number = 0;

};






int main() {

    Logger logger;
    FileLogger flogger;
    Logger logger3;
    Bulk bulk;
    bulk.attach(&logger);
    bulk.attach(&flogger);
    
    auto log_thread = logger.activate();
    log_thread.detach();

    auto flog_thread = flogger.activate();
    flog_thread.detach();


    try{
        bulk.loop();
    } catch (std::exception e) {
        std::cout << e.what();
    }


}

