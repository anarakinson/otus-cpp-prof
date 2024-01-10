#include <iostream> 
#include <atomic> 
#include <future> 
#include <thread> 
#include <chrono> 
#include <cassert> 


int main() {

    std::atomic<int> x{10};

    x.store(110);
    int expected = 110; // what must be in x
    int desired = 123;  // what will be in x

    bool exchanged = x.compare_exchange_strong(expected, desired);

    std::cout << "x: " << x << std::endl;
    std::cout << std::boolalpha << "exchanged: " << exchanged << std::endl;

    int old_x = x.exchange(999);
    std::cout << "x: " << x << std::endl;
    std::cout << "old_x: " << old_x << std::endl;


}