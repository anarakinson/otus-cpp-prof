/*

Функцию нужно останавливать и возобновлять:
    - разрезаем её на несколько функций в точках останова,
    возобновление будет запускать следующую функцию.
Между вызовами нужно сохранять куда-то данные со стека:
    - сохраняем в кучу.
Нужно запоминать, где остановились:
    - сохраняем в кучу.
Как возобновлять?
    - возвращаем объект, который это умеет.
Как пользователь может управлять поведением корутины?
    - через специальный объект "promise".

*/


#include <chrono>
#include <coroutine>
#include <cstdint>
#include <functional>
#include <list>
#include <vector>
#include <iostream>
#include <system_error>


using Clock = std::chrono::steady_clock;
using namespace std::chrono_literals;

#define PRINT_FUNC std::cout << __func__ << std::endl;


struct coro_type {
    struct promise_type {
        void return_void() { PRINT_FUNC; }


        std::suspend_never initial_suspend() {
            PRINT_FUNC;
            return {};
        }

        std::suspend_never final_suspend() noexcept {
            PRINT_FUNC;
            return {};
        }

        void unhandled_exception() {}

        coro_type get_return_object() {
            PRINT_FUNC;
            return {};
        }
    };
};


// coro_type coo() {
//     std::cout << "Body\n";
//     co_return;
// }


coro_type coo() {
    std::coroutine_traits<coro_type>::promise_type promise{};
    coro_type _coro_ret = promise.get_return_object();
    co_await promise.initial_suspend();
    std::cout << "Body\n";
    co_return;
    promise.return_void();
    co_await promise.final_suspend();
}


int main() {
    
    coro_type handle = coo();
    return 0;

}

