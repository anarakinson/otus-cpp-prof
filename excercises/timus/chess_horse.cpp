/*
    
    https://acm.timus.ru

    ***1197. Lonesome Knight***
        Time limit: 1.0 second
        Memory limit: 64 MB
The statement of this problem is very simple: you are to determine how many squares
of the chessboard can be attacked by a knight standing alone on the board. 
Recall that a knight moves two squares forward (horizontally or vertically in any direction) 
and then one square sideways (perpedicularly to the first direction).
    ***Input***
The first line contains the number N of test cases, 1 ≤ N ≤ 64. 
Each of the following N lines contains a test: two characters. 
The first character is a lowercase English letter from 'a' to 'h' and the second character is an integer from 1 to 8; 
they specify the rank and file of the square at which the knight is standing.
    ***Output***
Output N lines. Each line should contain the number of the squares 
of the chessboard that are under attack by the knight.

*/



#include <iostream>
#include <string>
#include <vector>


int main() {


    int x;
    std::cin >> x;

    std::vector<int> output;

    for (int i = 0; i < x; ++i) {
        
        int res = 8;
        
        std::string input{};
        std::cin >> input;

        char a = input[0];
        char b = input[1];

        if (a == 'a' || a == 'h') {
            res /= 2;
        }
        if (a == 'b' || a == 'g') {
            res -= res / 3;
        }
        if (b == '1' || b == '8') {
            res /= 2;
        }
        if (b == '2' || b == '7') {
            res -= res / 3;
        }

        output.emplace_back(res);

    }


    for (auto res : output) {
        std::cout << res << std::endl;
    }

}
