#include <iostream> 


template <typename T>
class Test {
public:
    Test(T a) {
        std::cout << "basic ctr" << std::endl;
        std::cout << a << std::endl;
    }
    Test(std::initializer_list<T> lst) {
        std::cout << "list ctr" << std::endl;
        for (auto e = lst.begin(); e != lst.end(); e++) {
            std::cout << *e << std::endl;
        }
    }
    ~Test() = default;

};



int main() {

    Test t0{1};  
    Test t1(1); 
    Test t2{1, 2, 3};

}
