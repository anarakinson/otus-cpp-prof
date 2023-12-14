/*


### 2138. The Good, the Bad and the Ugly ###

Time limit: 0.5 second
Memory limit: 256 MB


Everyone knows that computer see integers not in the same way as humans do. 
Instead of digits from 0 to 9 they use digits from 0 to 255. For example, 
the integer 1 000 000 can by represented by a computer with three digits 15, 66, 64 (let’s denote it as 15;66;64), 
because 15· 2562 + 66· 256 + 64 = 1 000 000. On top of that, integers in computers have a fixed size. 
In this problem the size of an integer is always 4 digits, so the integer 1 000 000 will be represented as 0;15;66;64. 
Computers use this exact format to communicate with each other.

This system may seem strange, but it works. Or, it used to work, until an evil genius 
reversed the order of digits in half of the computers! These computers now interpret 0;15;66;64 not as 1 000 000 
but as 1 078 071 040 (64· 2563 + 66· 2562 + 15· 256 + 0 = 1 078 071 040). No one knows how to fix it, 
so the computers that are left untouched are now called “good”, and other computers are called “bad”. 
In order for “good” and “bad” computers to communicate, 
the integers that are read incorrectly must be translated into correct integers.

For example, let A and B be two computers of opposite types. 
Let’s say the computer A wants to send the computer B a non-negative integer not exceeding 4 294 967 295. 
The computer A writes this integer down with four digits from 0 to 255 and sends them to the computer B. 
Computer B reads the received digits as v, which doesn’t necessary match the integer the computer A was trying to send.
Write a program that would help a “good” or a “bad” computer B determine, 
what integer the computer A of the opposite type tried to send.


***Input***

The first line contains one word, denoting the type of the computer A, 
which sent the integer: “GOOD” (without quotes), if the computer is “good”, and “BAD” (without quotes), if the computer is “bad”.

The second line contains a non-negative integer v that the computer B received (0 ≤ v ≤ 4 294 967 295).

***Output***

In the only line output the non-negative integer that the computer A sent.


*/



#include <iostream>
#include <string>


unsigned int process_data(unsigned int x, std::string &) {

    unsigned char a[4];
    unsigned char *ptr = (unsigned char*)&x;
    a[0] = *(ptr + 3);
    a[1] = *(ptr + 2);
    a[2] = *(ptr + 1);
    a[3] = *(ptr + 0);

    // std::cout << (int)a[0] << " " << (int)a[1] << " " << (int)a[2] << " " << (int)a[3] << std::endl;

    return *reinterpret_cast<unsigned int*>(a);

}


int main() {

    std::string type;
    unsigned int x;

    std::cin >> type;
    std::cin >> x;

    unsigned int result = process_data(x, type);

    std::cout << result << std::endl;

}
