#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <string>
#include <chrono>



void print_data(int x, int msec) {

    using namespace std::chrono_literals;

    for (int i = 0; i < 10; ++i) {
        std::cout << "Thread " <<  std::this_thread::get_id() << " - " << i << std::endl;
        std::this_thread::sleep_for(msec * 1ms);
    }
    std::cout << "Thread " <<  std::this_thread::get_id() <<  " ended" << std::endl;

}


int main() {

    // print_data(10, 1000);

    auto thread1 = std::thread(print_data, 1, 1000);
    auto thread2 = std::thread(print_data, 2, 2500);

    thread1.join();
    thread2.detach();

    std::cout << "Success!" << std::endl;

}