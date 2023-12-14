#include <iostream> 
#include <future> 
#include <thread> 
#include <chrono> 
#include <cassert> 


using namespace std::chrono_literals;

int main() {

    int x = 0;
    std::cout << "x: " << x << std::endl;

    // std::promise<int> promise;
    // std::future<int> future = promise.get_future();

    std::thread thread1( [&x](){ 
        while (x <= 10) {
            x++; 
            std::this_thread::sleep_for(100ms);
            std::cout << ".";
        } 
        std::cout << std::endl;
    } );
    thread1.detach();

    while(x <= 10);
    std::cout << "x: " << x << std::endl;
    assert(x >= 10);

}