#include <iostream>

#define TO_STR_1(x) #x 
#define TO_STR_2(x) TO_STR_1(x) 

#define VALUE 100


int main() {

    std::cout << TO_STR_1(text) << std::endl;
    std::cout << TO_STR_2(text) << std::endl;

    std::cout << TO_STR_1(VALUE) << std::endl;
    std::cout << TO_STR_2(VALUE) << std::endl;
    

}