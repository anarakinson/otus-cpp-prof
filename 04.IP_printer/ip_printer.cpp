/*

1. функция печати должна быть одной шаблонной функцией, 
разные варианты входов должны быть реализованы через механизм SFINAE

2. вариант для целочисленного представления должен представлять собой одну функцию

3. вариант для контейнеров std::list и std::vector должен представлять собой одну функцию

4. не должно быть реализации типа "если не совпало с иными - значит это контейнер"

5. найдите самый простой способ для печати `std::string` (но функция всё ещё должна быть шаблонной)

6. опциональная реализация для `std::tuple` должна приводить к ошибке в случае отличающихся типов

7. не должно быть ограничений на размер целочисленных типов (в байтах), 
на размер контейнеров и кортежа (количество элементов)

8. бинарный файл и пакет должны называться `print_ip`   


*/


#include <iostream> 
#include <cstdint>
#include <algorithm> 
#include <string> 
#include <vector> 
#include <list>  
#include <tuple> 
#include <type_traits>



/*------ numeric types ------*/ 
template <typename T>
typename std::enable_if<std::is_integral<T>::value, void>::type print_ip(T &&input) {
    
    std::vector<int> output{};
    
    // get every byte of T
    unsigned char *byte_pointer = (unsigned char *)&input;
    for (int j = 0; j < static_cast<int>(sizeof(T)); ++j) {
        output.emplace_back((int)*byte_pointer);
        ++byte_pointer;
    }
    std::reverse(output.begin(), output.end());
    // print_ip(output);
    size_t counter = 0;
    for (auto x : output) {
        std::cout << x;
        if (counter++ != output.size() - 1) std::cout << ".";        
    }
    std::cout << std::endl;

}


/*------ containers list && vector ------*/ 
template <typename T>
struct is_container: std::false_type {};
template <typename T>
struct is_container<std::vector<T>>: std::true_type {};
template <typename T>
struct is_container<std::list<T>>: std::true_type {};

template <typename T>
typename std::enable_if<is_container<T>::value, void>::type print_ip(T &&container) {

    size_t counter = 0;
    for (auto x : container) {
        std::cout << x;
        if (counter++ != container.size() - 1) std::cout << ".";        
    }
    std::cout << std::endl;

}


/*------ string ------*/ 
template <typename T>
typename std::enable_if<std::is_same<T, std::string>::value, void>::type print_ip(T &&str) {
    std::cout << str << std::endl;
}


/*------ tuple ------*/ 
/* check, if all elements the same type */
template <typename First, typename... T>
struct all_same_type {
    constexpr static bool value = std::is_same< 
        std::tuple<First, T...>,   // check that if first element is same as the last
        std::tuple<T..., First>    // and the last elements the same as first
    >::value;                      // than return true
};

template <typename... T>
struct all_same_type<std::tuple<T...>> : all_same_type<T...> {};


/* display elements */
template <size_t I = 0, typename... Args>
typename std::enable_if<I == sizeof...(Args) - 1, void>::type print_tuple(std::tuple<Args...> tup) {
    // print the last element
    std::cout << std::get<I>(tup) << std::endl;
}

template <size_t I = 0, typename... Args>
typename std::enable_if<(I < sizeof...(Args) - 1), void>::type print_tuple(std::tuple<Args...> tup) {
    // Print element of tuple
    std::cout << std::get<I>(tup) << "."; 
    // Go to next element
    print_tuple<I + 1>(tup);
}


template <typename... Args>
constexpr typename std::enable_if<all_same_type<Args...>::value, void>::type print_ip(std::tuple<Args...> &&tuple) {
   print_tuple(tuple);
}



int main() {

    print_ip( int8_t{-1} );                           // 255
    print_ip( int16_t{0} );                           // 0.0
    print_ip( int32_t{2130706433} );                  // 127.0.0.1
    print_ip( int64_t{8875824491850138409} );         // 123.45.67.89.101.112.131.41
    print_ip( std::string{"Hello, World!"} );         // Hello, World!
    print_ip( std::vector<int>{100, 200, 300, 400} ); // 100.200.300.400
    print_ip( std::list<short>{400, 300, 200, 100} ); // 400.300.200.100
    print_ip( std::make_tuple(123, 456, 789, 0) );    // 123.456.789.0

}
