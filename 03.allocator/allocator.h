#pragma once

#include <iostream>
#include <memory>
#include <limits>


#define UNUSED(X) (void *)X


struct Pool {
    Pool() = delete;
    Pool(size_t size_of_t) 
        : own_pool(::operator new (size_of_t * size), deleter())
    {}
    Pool(const Pool &other)  = default;
    // {
    //     own_pool = other.own_pool;
    //     start = other.start;
    //     end = other.end;
    // }
    Pool(Pool &&other) = default;
    // {
    //     std::swap(own_pool, other.own_pool);
    //     std::swap(start, other.start);
    //     std::swap(end, other.end);
    // }
    ~Pool() {
        std::cout << "  >>> Deleted <<<  " << std::endl;
        start = nullptr;
        end = nullptr;
    }

    void* get() { return own_pool.get(); }

    std::shared_ptr<void> own_pool;
    void* start = nullptr;
    void* end = nullptr;
    static constexpr size_t size = 10;

    struct deleter {
        void operator()(void* ptr) {
            ::operator delete(ptr);
        }
    };
};



template <typename T>
class CustomAllocator {
public:

    using value_type = T;

    CustomAllocator() noexcept
    {
        std::cout << "CONSTRUCTOR: " << typeid(T).name() 
                  << " <<< POOL: " << sizeof(T) * m_pool->size 
                  << " <<< object size: " << sizeof(*static_cast<T*>(m_pool->get())) 
                  << std::endl; 
    }

    template <typename U>
    CustomAllocator(const CustomAllocator<U> &other) noexcept
    // : m_pool{other.get_pool()}
    {
        std::cout << "COPY CONSTRUCTOR FROM: " << typeid(U).name() 
                  << " <<< POOL: " << sizeof(U) * m_pool->size 
                  << " <<< object size: " << sizeof(*static_cast<U*>(m_pool->get())) 
                  << std::endl; 
        std::cout << "COPY CONSTRUCTOR TO: " << typeid(T).name() 
                  <<  " <<< POOL: " << sizeof(T) * m_pool->size 
                  << " <<< object size: " << sizeof(*static_cast<T*>(m_pool->get())) 
                  << std::endl; 

        m_pool = other.get_pool();
    }

    // template <typename U>
    // CustomAllocator(CustomAllocator<U> &&other) noexcept 
    // {
    //     std::cout << "COPY CONSTRUCTOR FROM: " << typeid(U).name() 
    //               << " <<< POOL: " << sizeof(U) * m_pool->size 
    //               << " <<< object size: " << sizeof(*static_cast<U*>(m_pool->get())) 
    //               << std::endl; 
    //     std::cout << "COPY CONSTRUCTOR TO: " << typeid(T).name() 
    //               <<  " <<< POOL: " << sizeof(T) * m_pool->size 
    //               << " <<< object size: " << sizeof(*static_cast<T*>(m_pool->get())) 
    //               << std::endl; 
    //     // this->m_pool = m_pool;
    // }

    ~CustomAllocator() {
        std::cout << "DESTRUCTOR: " << typeid(T).name() 
                  << " <<< POOL: " << sizeof(T) * m_pool->size << std::endl;
    }

    CustomAllocator select_on_container_copy_construction() const {
        return CustomAllocator{};
    }

    T *allocate(size_t size) {
        if (m_pool->start == nullptr) {
            // std::cout << "start: " << size << std::endl;
            m_pool->start = static_cast<T*>(m_pool->get());
        }
        else {
            // std::cout << "update: " << size << " <<< " << sizeof(*pool->end) << std::endl;
            m_pool->start = m_pool->end;
        }
        m_pool->end = reinterpret_cast<T*>(m_pool->start) + size;

        std::cout << "allocated: " << size * sizeof(T) 
                  << " at: " << reinterpret_cast<T*>(m_pool->start) << std::endl;
                  
        return reinterpret_cast<T*>(m_pool->start); 
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
    
    std::shared_ptr<Pool> m_pool = std::make_shared<Pool>(Pool{sizeof(T)});
    // Pool* m_pool = new Pool{sizeof(T)};
    // inline static Pool m_pool{};

public:
    std::shared_ptr<Pool> get_pool() const { return m_pool; }


};


template <class T, class U>
constexpr bool operator == (const CustomAllocator<T>& a1, const CustomAllocator<U>& a2) noexcept {
    return a1.m_pool == a2.m_pool;
}

template <class T, class U>
constexpr bool operator != (const CustomAllocator<T>& a1, const CustomAllocator<U>& a2) noexcept {
    return a1.m_pool != a2.m_pool;
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
 

