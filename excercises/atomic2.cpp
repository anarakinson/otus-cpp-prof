#include <iostream> 
#include <future> 
#include <thread> 
#include <chrono> 
#include <cassert> 
#include <atomic> 


using namespace std::chrono_literals;

int main() {

    std::atomic<int> x{0};
    std::atomic<int> y{8};
    std::cout << "x: " << x << std::endl;
    std::cout << "y: " << y << std::endl;

    // std::promise<int> promise;
    // std::future<int> future = promise.get_future();

    std::thread thread1( [&x](){ 
        while (x <= 10) {
            std::this_thread::sleep_for(100ms);
            x++; 
            std::cout << ".";
        } 
        std::cout << std::endl;
    } );
    thread1.detach();


    std::thread thread2( [&x, &y](){ 
        bool exchanged{};
        while (!exchanged) {
            int x2 = x.load();
            exchanged = y.compare_exchange_weak(x2, 123); 
        } 
        std::cout << std::boolalpha << "\nexchanged: " << exchanged << std::endl;
    } );
    thread2.detach();




    while(x <= 10);

    std::cout << "\nx: " << x << std::endl;
    std::cout << "y: " << y << std::endl;
    assert(x >= 10);

}