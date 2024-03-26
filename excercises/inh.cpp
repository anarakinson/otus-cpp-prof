#include <iostream>
#include <vector>
#include <algorithm>


class A {
public:
    A(){
        std::cout << "A" << std::endl;
    }
    virtual ~A(){
        std::cout << "~A" << std::endl;
    }
};

class B {
public:
    B() {
        std::cout << "B" << std::endl;
    }
    virtual ~B() {
        std::cout << "~B" << std::endl;
    }
};

class C : public A, B {
public:
    C() {
        std::cout << "C" << std::endl;
    }
    ~C() {
        std::cout << "~C" << std::endl;
    }

    B b;
    A a;
    int m_i = 0;

};


class Y;
class X final {
    Y *y;
    int x = 0;
public:
    X(int x) : x{x} {}

    // int get() const { return x; }

};


class Y {
    X *x;
};


void foo(X x) {
    return;
}

int main() {

    // std::vector<int> v = {1, -5, 4, 2, -3};
    // std::vector<int> v;
    // // foo();
    // auto res = std::max_element(v.begin(), v.end());
    // if (res == v.end()) {
    //     std::cout << "empty " << std::endl;
    //     return 1;
    // }

    // std::cout << *res << std::endl;
    // return 0;

    A *c = new C;

    X x{1};
    foo(1);
    foo(4);
    delete c;

}