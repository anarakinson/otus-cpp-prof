#include <iostream>
#include <memory>
#include <map>
#include <vector>
#include <string>


#define UNUSED(X) (void *)X


template <typename T>
void print_map(const char *name, T &map) {
    
    std::cout << name << ": ";
    for (int i = 0; i < 10; ++i) {
        std::cout << map[i] << " ";
    }
    std::cout << std::endl;

}



template <typename T>
class Allocator {
public:

    using value_type = T;

    std::shared_ptr<void> pool;
    T* pool_start = nullptr;
    T* pool_end = nullptr;
    static constexpr size_t pool_size = 10;
    struct deleter {
        void operator()(void* ptr) {
            ::operator delete(ptr);
        }
    };

    Allocator() noexcept : 
        pool(::operator new (sizeof(T) * pool_size), deleter()) {}

    template <typename U>
    Allocator(const Allocator<U> &other) noexcept {
        pool = other.pool;
    }

    Allocator select_on_container_copy_construction() const {
        std::cout << "select_on_container_copy_construction" << std::endl;
        return Allocator{};
    }

    T *allocate(size_t size) {
        if (pool_start == nullptr) {
            pool_start = static_cast<T*>(pool.get());
        }
        else {
            pool_start = pool_end;
        }
        auto output = pool_start;
        pool_end = pool_start + size * sizeof(T);
        return output; 
    }

    void deallocate(T *ptr, size_t size) {
        UNUSED(size); 
        UNUSED(ptr);
        // ...
    }

    template <typename U>
    struct rebind {
        typedef Allocator<U> other;
    };

    using propagate_on_container_copy_assignment = std::true_type;
    using propagate_on_container_move_assignment = std::true_type;
    using propagate_on_container_swap = std::true_type; //UB if std::false_type and a1 != a2;

};


template <class T, class U>
constexpr bool operator == (const Allocator<T>& a1, const Allocator<U>& a2) noexcept {
    return a1.pool == a2.pool;
}

template <class T, class U>
constexpr bool operator != (const Allocator<T>& a1, const Allocator<U>& a2) noexcept {
    return a1.pool != a2.pool;
}



int main() {

    std::map<int, int> map{};
    std::map<int, int, std::less<int>, Allocator<std::pair<const int, int>>> map_a{};


    for (int i = 0; i < 10; ++i) {
        map[i] = i * i;
        map_a[i] = i * i;
    }


    print_map("basic allocator", map);
    print_map("custom allocator", map_a);

}
