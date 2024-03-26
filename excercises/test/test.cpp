
#include <iostream>
#include <thread>
#include <mutex>

class Car {
public:

    int speed = 0;

    void speed_up() {
        if (fuel > 0) {
            ++speed;
            --fuel;
        }
    }

private:

    int fuel = 10;

};


class Truck : public Car {
public:
    bool truck_method() { return truck_field; }
private:
    bool truck_field = true;
};



class Motorcicle : public Car {
public:
    bool motorcicle_method() { return motorcicle_field; }
private:
    bool motorcicle_field = true;
};





/*

Работа с указателями 
Задание: Напишите функцию, которая принимает указатель на массив целых чисел и его размер. 
Функция должна изменить каждый элемент массива, умножив его на 2. 
Расширьте задание, требуя от кандидатов осуществлять проверку на валидность 
входного указателя перед выполнением операции и обработку возможных ошибок.

*/

// void func(int *ptr, size_t size) {

//     try {

//         for (size_t i = 0; i < size; ++i) {
//             // проверка на наличие значения
//             if (ptr == nullptr) {
//                return;
//             }
//             *ptr *= 2;
//             ++ptr;
//         } 
//     // обработка ошибки
//     } catch(std::exception ex) {
//         std::cout << ex.what() << std::endl;
//     }

// }


// int main() {
//     std::cout << "hello" << std::endl;

//     int x[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//     for (size_t i = 0; i < 10; ++i) {
//         std::cout << x[i] << " ";
//     }
//     std::cout << "\n";
//     func(x, 10);
//     for (size_t i = 0; i < 10; ++i) {
//         std::cout << x[i] << " ";
//     }
//     std::cout << "\n";
// }


/*

Асинхронное программирование и многопоточность 
Задание: Напишите асинхронную функцию для вычисления факториала числа. 
Расширьте задание, добавив условие, что функция должна быть запущена в двух разных потоках, 
обращаясь к общей переменной для хранения результата. 
Обеспечьте потокобезопасный доступ к этой переменной, чтобы избежать гонки данных.

*/

// x - число, факториал которого нужно вычислить
// result - факториал числа
// temp - служебная переменная, счетчик посчитанных итераций
void get_factorial(const int x, int &result, int &temp, std::mutex &mutex) {

    if (x == 0 || x == 1) {
        result = 1;
    }

    std::lock_guard<std::mutex> guarg{mutex};
    while (temp <= x) {
        result *= temp;
        ++temp;
        std::cout << temp << " " << result << " \n";
    }

}

int factorial(const int x) {

    std::mutex mutex;
    int result = 1;
    int temp = 1;

    auto thread1 = std::thread(get_factorial, x, std::ref(result), std::ref(temp), std::ref(mutex));
    auto thread2 = std::thread(get_factorial, x, std::ref(result), std::ref(temp), std::ref(mutex));

    thread1.join();
    thread2.join();

    return result;
}


// int main(int argc, char **argv) {
//     std::cout << "hello" << std::endl;

//     // int x = atoi(argv[1]);
//     // int y = factorial(x);

// }



/*

Задание:  Найти минимум функции x^2-4+y^2+6x*y на диапазоне xE(-10;10) yE(-10,10)

*/

// double func(double x, double y) {

//     double res = (x * x) - 4 + (y * y) + 6 * (x * y); 
//     return res;

// }

// double get_min(double x1, double x2, double y1, double y2) {

//     double result = 0;
//     for (auto i = x1; i < x2; ++i) { 
//         for (auto j = y1; j < y2; ++j) {
//             double temp = func(i, j);
//             if (temp < result) {
//                 result = temp;
//             }
//         }   
//     }

//     return result;

// }


// int main() {
//     std::cout << "hello" << std::endl;

//     auto y = get_min(-10, 10, -10, 10);
//     std::cout << y << std::endl;

// }



/*

Задание: 
Напишите функцию, которая принимает на вход std::vector<int> и std::list<int>, 
оба отсортированные по возрастанию. Ваша задача — преобразовать вектор в список, 
а затем объединить два списка в один отсортированный список, 
содержащий только уникальные элементы из обоих исходных списков.

*/



#include <algorithm>
#include <list>
#include <vector>


// std::list<int> func(std::vector<int> vec, std::list<int> list1) {

//     std::list<int> list2{vec.begin(), vec.end()};
    
//     list1.splice(list1.end(), list2);
//     list1.sort();
//     list1.unique();

//     return list1;

// }


// int main() {

//     std::vector<int> vec = {1, 2, 3, 4, 5};
//     std::list<int> list = {5, 4, 3, -1, -2, -3};

//     auto out = func(vec, list);

//     for (auto &x : out) {
//         std::cout << x << " ";
//     }

// }





const uint32_t COMMON_HEADER_SIZE = 1;
const uint32_t SETUP_REQUEST_MSG_SIZE = 7;
const uint16_t SETUP_REQUEST_MSG_ID = 16;

void init_setup_request_msg(
    uint8_t *setup_request_mgs_p, 
    uint8_t role_id, 
    uint32_t session_id
) {

// сформируйте сообщение по данному шаблону в сетевом порядке:

// [header:1(SETUP_REQUEST_MSG_ID)][msg_size:2][role_id][seesion_id]

}

int main() {

    uint8_t setup_msg[COMMON_HEADER_SIZE+SETUP_REQUEST_MSG_SIZE];
    init_setup_request_msg(setup_msg, 10, 100);

}


