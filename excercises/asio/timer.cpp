

// #define BOOST_ASIO_ENABLE_HANDLER_TRACKING 


// #include <boost/asio/io_service.hpp>
// #include <boost/asio/steady_timer.hpp>
#include <boost/asio.hpp> 

#include <iostream>
#include <chrono>
#include <thread>


#include <ctime>

void print_time() {
    using clock = std::chrono::system_clock;

    auto time_point = clock::now();
    std::time_t time = clock::to_time_t(time_point);
    std::cout << std::ctime(&time) << std::endl;
}



int main() {

    std::cout << "Hello!" << std::endl;

    boost::asio::io_context io_context;

    boost::asio::steady_timer timer1{
        io_context,
        std::chrono::seconds(1)
    };

    boost::asio::steady_timer timer2{
        io_context,
        std::chrono::seconds(2)
    };

    int timer_num = 1;
    auto timer_lambda = [&timer_num](const boost::system::error_code &err) {
        if (errno) {
            std::cout << err.message() << std::endl;
        } else {
            std::cout << "thread - " << std::this_thread::get_id() << std::endl;
            std::cout << "timer-" << timer_num << " BZZZ-BZZZ" << std::endl;
            timer_num++;
        }
    };

    timer1.async_wait(
        timer_lambda
    );

    timer2.async_wait(
        timer_lambda
    );

    std::cout << "run context" << std::endl;
    print_time();

    //* ------ multithread ------ *//
    std::thread thread1{
        [&io_context](){ io_context.run(); }
    };
    std::thread thread2{
        [&io_context](){ io_context.run(); }
    };

    thread1.join();
    thread2.join();
    /*----------------------------*/

    //* ------ one thread ------ *//
    // io_context.run();
    /*----------------------------*/
    
    std::cout << "end context" << std::endl;
    print_time();


}


