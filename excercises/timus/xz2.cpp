#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <memory>

//  3-5-4-2-6-1-8-7 - not a proof
//  1 2 3 4 5 6 7 8     

// int main() {

//     std::vector<int> balls{};

//     int x, y;
//     std::cin >> x;

//     for (int i = 0; i < x; ++i) {
//         std::cin >> y;
//         balls.emplace_back(y);
//     }

//     std::string output = "Not a proof";
//     int temp = balls.back();
    
//     for (int i = 0; i < balls.size(); ++i) {
//         int ball = balls[i];
//         std::cout << "(" << ball << " >= " << temp << ") "; 
//         if (ball >= temp - 1) {
//             temp = ball;
//         }
//         else {
//             output = "Cheater";
//             break;
//         }
//     }
//     std::cout << std::endl;

//     std::cout << output;

// }





int main() {

    int a = -1;
    double b = 1;
    int a2 = -1;
    double b2 = 1;


    auto res = std::tie(a, b) < std::tie(b2, a2);

    std::cout << res << std::endl;

}

