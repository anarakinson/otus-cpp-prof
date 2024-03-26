
#include <iostream> 
#include <fstream>
#include <string> 
#include <vector> 
#include <mutex> 
#include <atomic> 
#include <thread> 
#include <condition_variable> 



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
    bool m_flag = true;

};




class Bulk {

    inline static std::condition_variable_any m_cv{};
    inline static std::mutex m_mutex{};

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

            // std::cout << "m_lines: " << m_lines.size() << " finished: " << m_finished << " loggers: " << m_loggers.size() << std::endl;

            if (m_counter >= 3) {
                notify();
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
        
        for (auto &l : m_loggers) {
            l->flag_down();
            // l->print_lines();
        }

        m_cv.notify_all();

        // std::cout << "notify from thread " << std::this_thread::get_id()  << m_finished << " << " << m_loggers.size() << std::endl;

        // wait for loggers make work
        while(m_finished < m_loggers.size()) { 
            // std::cout << "-!"; 
        }        
        // reset queue
        reset_queue();
    }

    void reset_queue() {
        m_lines.clear();
        m_counter = 0;
        m_finished = 0;
    }

    void update_finished() { 
        m_finished++;
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

            std::unique_lock<std::mutex> guard{m_owner->m_mutex};
            // std::cout << "Logger waiting...\n";
            m_owner->m_cv.wait(guard, [&]() { return !m_flag; });
            // std::cout << "Logger work from thread " << std::this_thread::get_id() << std::endl;

            // work logic
            for (const auto &line : m_owner->get_lines()) {
                std::cout << line << " ";
            }
            std::cout << std::endl;

            flag_up();
            m_owner->update_finished();
        
        }
    }
    

};



class FileLogger : public iLogger {
public:

    // write to file
    void print_lines() override {
        while (true) {
            
            std::unique_lock<std::mutex> guard{m_owner->m_mutex};
            // std::cout << "FileLogger waiting...\n";
            m_owner->m_cv.wait(guard, [&]() { return !m_flag; });
            // std::cout << "FileLogger work from thread " << std::this_thread::get_id() << std::endl;

            // std::cout << "hello" << std::endl;
            
            // work logic
            std::vector<std::string> lines = m_owner->get_lines();
            std::ofstream new_file{};
            new_file.open("./logs/" + std::to_string(m_number++) + ".log");
            new_file << "bulk: "; 
            for (const auto &l : lines) {
                new_file << l << " ";
            }
            new_file << std::endl;
            new_file.close();
            
            flag_up();
            m_owner->update_finished();

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

