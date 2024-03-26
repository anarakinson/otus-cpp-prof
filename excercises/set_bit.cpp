#include <cstdint>
#include <iostream>


std::uint32_t set_bit(std::uint32_t number, std::uint32_t index, bool bit_value) {
    
    std::uint32_t mask = 1 << index;
    if (bit_value) 
        number |= mask;            // OR for make bit TRUE
    else 
        number ^= mask;            // XOR for make bit FALSE

    return number;
}


int main() {

    std::uint32_t number = 10; // original value
    std::uint32_t index = 8;   // what bit must be set
    
    std::cout << number << std::endl;

    number = set_bit(number, index, true);

    std::cout << number << std::endl;

    number = set_bit(number, index, false);

    std::cout << number << std::endl;

}
