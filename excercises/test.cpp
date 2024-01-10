#include <iostream>
#include <chrono>
#include <thread>


int main() {
    using namespace std::chrono_literals;

    for (int i = 0; i < 1000; ++i) {
        std::this_thread::sleep_for(10ms);
        if (i % 10 == 0) {
            std::cout << i << std::endl;
        }
        if (SIGINT) {
            std::cout << "STOP" << std::endl;
        }
    }

}