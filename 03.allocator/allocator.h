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
        std::cout << "CONSTRUCTOR: " << typeid(T).name() 
                  << " <<< POOL: " << sizeof(T) * pool.size 
                  << " <<< object size: " << sizeof(*static_cast<T*>(pool.own_pool.get())) 
                  << std::endl; 
    }

    template <typename U>
    CustomAllocator(const CustomAllocator<U> &) noexcept
    {
        std::cout << "COPY CONSTRUCTOR FROM: " << typeid(U).name() 
                  << " <<< POOL: " << sizeof(U) * pool.size 
                  << " <<< object size: " << sizeof(*static_cast<U*>(pool.own_pool.get())) 
                  << std::endl; 
        std::cout << "COPY CONSTRUCTOR TO: " << typeid(T).name() 
                  <<  " <<< POOL: " << sizeof(T) * pool.size 
                  << " <<< object size: " << sizeof(*static_cast<T*>(pool.own_pool.get())) 
                  << std::endl; 
    }

    ~CustomAllocator() {
        std::cout << "DESTRUCTOR: " << typeid(T).name() 
                  << " <<< POOL: " << sizeof(T) * pool.size << std::endl;
    }

    CustomAllocator select_on_container_copy_construction() const {
        return CustomAllocator{};
    }

    T *allocate(size_t size) {
        if (pool.start == nullptr) {
            // std::cout << "start: " << size << std::endl;
            pool.start = static_cast<T*>(pool.own_pool.get());
        }
        else {
            // std::cout << "update: " << size << " <<< " << sizeof(*pool.end) << std::endl;
            pool.start = pool.end;
        }
        pool.end = pool.start + size;

        std::cout << "allocated: " << size * sizeof(T) 
                  << " at: " << pool.start << std::endl;
                  
        return reinterpret_cast<T*>(pool.start); 
    }

    void deallocate(T *ptr, size_t size) {
        UNUSED(size); 
        UNUSED(ptr);
        // ...
    }

    template <typename U>
    struct rebind {
        typedef CustomAllocator<U> other;
    };

    using propagate_on_container_copy_assignment = std::true_type;
    using propagate_on_container_move_assignment = std::true_type;
    using propagate_on_container_swap = std::true_type; //UB if std::false_type and a1 != a2;


private:

    struct Pool {
        Pool() 
            : own_pool(::operator new (sizeof(T) * size), deleter())
        {}
        Pool(const Pool&) 
            : own_pool(::operator new (sizeof(T) * size), deleter())
        {}
        ~Pool() {
            // std::cout << ">>>Deleted<<<" << sizeof(T) << std::endl;
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



// template<class T>
// struct Mallocator
// {
//     typedef T value_type;
 
//     Mallocator() {
//         std::cout << sizeof(T) << std::endl;
//     }
 
//     template<class U>
//     constexpr Mallocator(const Mallocator <U>&) noexcept {
//         std::cout << sizeof(U) << std::endl;
//         std::cout << sizeof(T) << std::endl;
//     }
 
//     [[nodiscard]] T* allocate(std::size_t n)
//     {
//         if (n > std::numeric_limits<std::size_t>::max() / sizeof(T))
//             throw std::bad_array_new_length();
 
//         if (auto p = static_cast<T*>(std::malloc(n * sizeof(T))))
//         {
//             report(p, n);
//             return p;
//         }
 
//         throw std::bad_alloc();
//     }
 
//     void deallocate(T* p, std::size_t n) noexcept
//     {
//         report(p, n, 0);
//         std::free(p);
//     }
// private:
//     void report(T* p, std::size_t n, bool alloc = true) const
//     {
//         std::cout << (alloc ? "Alloc: " : "Dealloc: ") << sizeof(T) * n
//                   << " bytes at " << std::hex << std::showbase
//                   << reinterpret_cast<void*>(p) << std::dec << '\n';
//     }
// };
 
// template<class T, class U>
// bool operator==(const Mallocator <T>&, const Mallocator <U>&) { return true; }
 
// template<class T, class U>
// bool operator!=(const Mallocator <T>&, const Mallocator <U>&) { return false; }
 

