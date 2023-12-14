#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <memory>



struct deleter {
    void operator () (void* ptr) {
        ::operator delete(ptr);
    }
};


int main() {

    // make void memory allocation size of 10 {TYPENAME}
    std::shared_ptr<void> pool(::operator new (sizeof(int) * 10), deleter());

    pool.reset(::operator new (sizeof(int) * 20), deleter());

    { // take ptr to start of allocated memory and interpret it as {TYPENAME}
        auto ptr = static_cast<int *>(pool.get());
        for (int i = 0; i < sizeof(int) * 10; i += sizeof(int)) {
            ptr += i;
            std::cout << i << " ";
            *ptr = i * i;
        }
        std::cout << std::endl;
    }
    
    { // take ptr to start of allocated memory and interpret it as {TYPENAME}
        auto ptr = static_cast<int *>(pool.get());
        for (int i = 0; i < sizeof(int) * 10; i += sizeof(int)) {
            ptr += i;
            std::cout << *ptr << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "end" << std::endl;

}

