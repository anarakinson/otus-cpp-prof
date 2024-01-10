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


struct Timer {
    Clock::time_point start;
    Clock::duration duration;
    std::function<void()> callback;    
};


struct Executor {
    void schedule(Clock::duration duration, std::function<void()> callback) {
        timers.emplace_back(Clock::now(), duration, std::move(callback));
    }

    void run() {
        while (!timers.empty()) {
            for (auto it = timers.begin(); it != timers.end(); ) {
                auto &timer = *it;
                if (timer.start + timer.duration < Clock::now()) {
                    timer.callback();
                    it = timers.erase(it);
                } else {
                    ++it;
                }
            }
        }
    }

    std::list<Timer> timers;
};


struct timer_awaitable {
    bool await_ready() {
        return false;
    }

    void await_suspend(std::coroutine_handle<> coro) {
        exec.schedule(
            duration, 
            [coro] () { coro.resume(); } 
        );
    }

    void await_resume() {}

    Executor &exec;
    Clock::duration duration;
};

timer_awaitable sleep_for(Clock::duration duration, Executor &exec) { return timer_awaitable{exec, duration}; }


struct simple_int_task {
    struct promise_type {
        void return_value(int v) {
            PRINT_FUNC;
            result = v;
        }

        std::suspend_never initial_suspend() { 
            PRINT_FUNC; 
            return {}; 
        }
        std::suspend_always final_suspend() noexcept { 
            PRINT_FUNC; 
            return {}; 
        }
        void unhandled_exception() {}

        simple_int_task get_return_object() {
            PRINT_FUNC;
            return {std::coroutine_handle<promise_type>::from_promise(*this)};
        }

        std::optional<int> result;
    };

    std::optional<int> get_result() {
        if (!handle) { return std::nullopt; }
        return handle.promise().result;
    }

    std::coroutine_handle<promise_type> handle;
};


simple_int_task io_heavy(Executor &exec) {
    std::cout << "io_heavy starts\n";
    co_await sleep_for(4s, exec);      // await for result
    std::cout << "1\n";
    co_await sleep_for(3s, exec);
    std::cout << "2\n";
    co_await sleep_for(2s, exec);
    std::cout << "3\n";
    co_await sleep_for(1s, exec);
    std::cout << "io_heavy ends\n";
    co_return 42;                      // return value after end
}


int cpu_heavy() {
    std::cout << "cpu_heavy start\n";
    int x = 0;
    for (int i = 0; i < 2'000'000'000; i++) {
    x += i;
    }
    std::cout << "cpu_heavy end\n";
    return x;
}



int main() {

    auto start = Clock::now();

    Executor exec;
    auto task = io_heavy(exec);
    cpu_heavy(); 
    exec.run();

    auto end = Clock::now();
    
    auto result = task.get_result().value();

    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " - " << result << std::endl;

    return 0;

}