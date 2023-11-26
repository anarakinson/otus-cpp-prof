#pragma once

#include <iostream>
#include <memory>


#define UNUSED(X) (void *)X


template <typename T>
class CustomAllocator {
public:

    using value_type = T;

    CustomAllocator() noexcept
    {
        std::cout << sizeof(T) * pool.size << " <<< " << sizeof(*static_cast<T*>(pool.own_pool.get())) << std::endl; 
    }

    template <typename U>
    CustomAllocator(const CustomAllocator<U> &) noexcept
    {}

    ~CustomAllocator() {
        std::cout << ">>DELETED<<";
    }

    CustomAllocator select_on_container_copy_construction() const {
        return CustomAllocator{};
    }

    T *allocate(size_t size) {
        if (pool.start == nullptr) {
            // std::cout << "start: " << size << std::endl;
            pool.start = reinterpret_cast<T*>(pool.own_pool.get());
        }
        else {
            // std::cout << "update: " << size << " <<< " << sizeof(*pool.end) << std::endl;
            pool.start = pool.end;
        }
        pool.end = pool.start + size;
        // std::cout << pool.start << " " << pool.end << std::endl;
        return static_cast<T*>(pool.start); 
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


private:

    struct Pool {
        Pool() 
            : own_pool(::operator new (sizeof(T) * size), deleter())
        {}
        ~Pool() {
            std::cout << ">>>Deleted<<<";
            // delete own_pool;
            start = nullptr;
            end = nullptr;
        }

        std::shared_ptr<void> own_pool;
        T* start = nullptr;
        T* end = nullptr;
        static constexpr size_t size = 10;
    };

    struct deleter {
        void operator()(void* ptr) {
            ::operator delete(ptr);
        }
    };
    
    Pool pool;

};


template <class T, class U>
constexpr bool operator == (const CustomAllocator<T>& a1, const CustomAllocator<U>& a2) noexcept {
    return a1.pool == a2.pool;
}

template <class T, class U>
constexpr bool operator != (const CustomAllocator<T>& a1, const CustomAllocator<U>& a2) noexcept {
    return a1.pool != a2.pool;
}

