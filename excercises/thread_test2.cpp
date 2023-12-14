#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <string>
#include <chrono>



void print_data(int &data, std::mutex &mutex, bool mutex_on) {

    using namespace std::chrono_literals;

    for (int i = 0; i < 10000; ++i) {

        if (mutex_on) mutex.lock();
        data++;
        if (mutex_on) mutex.unlock();
        std::this_thread::sleep_for(1us);
    }

}


void print_data_v2(int &data, std::mutex &mutex) {

    using namespace std::chrono_literals;
    std::lock_guard<std::mutex> lock{mutex};
    // std::unique_lock<std::mutex> lock{mutex};
    // std::scoped_lock<std::mutex> lock{mutex};

    for (int i = 0; i < 10000; ++i) {
        data++;
        std::this_thread::sleep_for(1us);
    }

}



int main() {

    int data = 0;
    std::mutex mutex{};
    bool mutex_on = false;
    // bool mutex_on = true;

    // auto thread1 = std::thread(print_data, std::ref(data), std::ref(mutex), mutex_on);
    // auto thread2 = std::thread(print_data, std::ref(data), std::ref(mutex), mutex_on);

    auto thread1 = std::thread(print_data_v2, std::ref(data), std::ref(mutex));
    auto thread2 = std::thread(print_data_v2, std::ref(data), std::ref(mutex));

    thread1.join();
    thread2.join();

    std::cout << data << std::endl;
    std::cout << "Success!" << std::endl;

}