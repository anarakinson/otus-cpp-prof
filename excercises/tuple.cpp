/*

Для закрепления материала по std::tuple выполните следующее задание.
Задание 1. Реализуйте свой вариант std::tie.
в tie передается ряд переменных, которые уже инициализированы, и в них записывается содержимое tuple

Следующий код должен быть валидным:

*/

#include <iostream>
#include <string>
#include <tuple>
#include <cassert>

#define UNUSED(X) (void)(X)

auto getPerson() {

    const std::string name = "Petia";
    const std::string secondName = "Ivanoff";
    const std::size_t age = 23;
    const std::string department = "Sale";

    return std::make_tuple(
        name, secondName, age, department
    );

}

template <typename... Args>
constexpr std::tuple<Args&...> custom_tie(Args &...args) noexcept {

    return std::tuple<Args&...>{args...};

}


int main(int argc, char * argv[]) {
    UNUSED(argc); UNUSED(argv);

    std::string name, secondName, department;
    std::size_t age;
    
    custom_tie(name, secondName, age, department) = getPerson();
    
    std::cout << name << ' ' << age << std::endl;

    assert(name == "Petia");
    assert(secondName == "Ivanoff");
    assert(age == 23);
    assert(department == "Sale");
    
    return 0;

}
