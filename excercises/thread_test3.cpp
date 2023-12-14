#include <iostream>
#include <thread>
#include <future>
#include <mutex>
#include <vector>
#include <string>
#include <chrono>


void set_data(std::promise<int> promise) {

    std::cout << "Future started" <<  std::endl;

    using namespace std::chrono_literals;
    int data = 0;
    for (int i = 0; i < 1000; ++i) {
        std::this_thread::sleep_for(1ms);
        data++;
        if (i == 100) {
            promise.set_value(data);
        }
    }

    std::cout << "Future ended" <<  std::endl;

}


void print_data(int msec) {

    using namespace std::chrono_literals;
    
    std::cout << "Thread " <<  std::this_thread::get_id() <<  " started" << std::endl;
    for (int i = 0; i < 10; ++i) {
        std::this_thread::sleep_for(msec * 1ms);
        std::cout << "Thread " <<  std::this_thread::get_id() << " - " << i << std::endl;
    }
    std::cout << "Thread " <<  std::this_thread::get_id() <<  " ended" << std::endl;

}



int main() {

    std::cout << std::thread::hardware_concurrency() << std::endl;

    int data = 0;
    std::mutex mutex{};
    bool mutex_on = false;
    
    /*------------------------------*/
    std::promise<int> promise;
    std::future<int> future = promise.get_future();
    
    std::thread thread(set_data, std::move(promise));
    /*------------------------------*/


    /*-------------------------------*/
    std::thread thread2(print_data, 100);
    /*-------------------------------*/
    print_data(250);
    

    int val = future.get();
    std::cout << "Val: " << val << std::endl;


    thread.join();
    thread2.join();
    std::cout << "Success!" << std::endl;


}