#include <iostream>
#include <math.h>


double compute_tr(int x, double lim) {
    double res = 0;
    for (int i = 1; i < x; ++i){
        if (x % i == 0) {
            res += i;
            if (res / x >= lim / x) {
                return lim + 1;
            }
        }
    }
    return res;
}


int main() {

    int x, y;
    std::cin >> x >> y;

    double max_triv = 1000000;
    int res = 0;
    for (int i = x; i <= y; ++i) {

        double triv = compute_tr(i, max_triv);
        
        // std::cout << i << " " << triv << " " << triv / i << std::endl;
        if (triv / i <= max_triv / i) {
            res = i;
            max_triv = triv;
        }

    }

    std::cout << res << std::endl;

}

