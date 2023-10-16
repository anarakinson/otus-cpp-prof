#include <iostream>
#include <memory>
#include <map>
#include <string>



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

    std::shared_ptr<T> pool = nullptr;
    static constexpr size_t pool_size = 10;

    Allocator() noexcept {
        pool.reset(new T[pool_size]);
    }

    template <typename U>
    Allocator(const Allocator<U> &other) noexcept {
        pool = other.pool;
    }

    Allocator select_on_container_copy_construction() const {
        std::cout << "select_on_container_copy_construction" << std::endl;
        return Allocator{};
    }

    T *allocate(size_t size) {
        return pool.get();
    }

    void deallocate(T *ptr, size_t size) {
        //...
    }

    template <typename U>
    struct rebind {
        typedef Allocator<U> other;
    };

    using propagate_on_container_copy_assignment = std::true_type;
    using propagate_on_container_move_assignment = std::true_type;
    using propagate_on_container_swap = std::true_type; //UB if std::false_type and a1 != a2;

    // template <typename U>
    // Allocator operator = (const Allocator<U> &other) noexcept {
    //     pool = other.pool;
    // }

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
    // std::allocator<std::pair<int, int>> allo{};
    std::map<int, int, std::less<int>, Allocator<std::pair<const int, int>>> map_a{};


    for (int i = 0; i < 10; ++i) {
        map[i] = i * i;
    }

    for (int i = 0; i < 10; ++i) {
        map_a[i] = i * i;
    }


    print_map("basic map", map);
    print_map("map with alloc", map_a);

    
}
