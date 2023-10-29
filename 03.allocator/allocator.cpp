#include <iostream>
#include <memory>
#include <map>
#include <vector>
#include <string>


#define UNUSED(X) (void *)X


int factorial(const int n) {
    int f = 1;
    for (int i = 1; i <= n; ++i)
        f *= i;
    return f;
}


template <typename T>
void print_map(const char *name, const T &map) {
    
    std::cout << name << ": ";
    for (int i = 0; i < 10; ++i) {
        std::cout << map.at(i) << " ";
    }
    std::cout << std::endl;

}



template <typename T>
class CustomAllocator {
public:

    using value_type = T;

    CustomAllocator() noexcept : 
        pool(::operator new (sizeof(T) * pool_size), deleter()) {
        std::cout << sizeof(T) * pool_size << " <<< " << sizeof(*static_cast<T*>(pool.get())) << std::endl; 
    }

    template <typename U>
    CustomAllocator(const CustomAllocator<U> &other) noexcept {
        pool = other.pool;
    }

    CustomAllocator select_on_container_copy_construction() const {
        return Allocator{};
    }

    T *allocate(size_t size) {
        if (pool_start == nullptr) {
            std::cout << "start: " << size << std::endl;
            pool_start = reinterpret_cast<T*>(pool.get());
        }
        else {
            std::cout << "update: " << size << " <<< " << sizeof(*pool_end) << std::endl;
            pool_start = pool_end;
        }
        pool_end = pool_start + size * sizeof(T);
        return static_cast<T*>(pool_start); 
    }

    void deallocate(T *ptr, size_t size) {
        UNUSED(size); 
        UNUSED(ptr);
        // ...
    }

    // template <typename U>
    // struct rebind {
    //     typedef Allocator<U> other;
    // };

    using propagate_on_container_copy_assignment = std::true_type;
    using propagate_on_container_move_assignment = std::true_type;
    using propagate_on_container_swap = std::true_type; //UB if std::false_type and a1 != a2;


    std::shared_ptr<void> pool;
    T* pool_start = nullptr;
    T* pool_end = nullptr;
    static constexpr size_t pool_size = 10;

    struct deleter {
        void operator()(void* ptr) {
            ::operator delete(ptr);
        }
    };

};


template <class T, class U>
constexpr bool operator == (const CustomAllocator<T>& a1, const CustomAllocator<U>& a2) noexcept {
    return a1.pool == a2.pool;
}

template <class T, class U>
constexpr bool operator != (const CustomAllocator<T>& a1, const CustomAllocator<U>& a2) noexcept {
    return a1.pool != a2.pool;
}



int main() {

    std::map<int, int> map{};
    std::map<int, int, std::less<int>, CustomAllocator<std::pair<const int, int>>> map_a{};


    for (int i = 0; i < 10; ++i) {
        std::cout << i << " ";
        map[i] = factorial(i);
        map_a[i] = factorial(i);
    }

    std::cout << "output" << std::endl;

    print_map("basic allocator", map);
    print_map("custom allocator", map_a);

}
