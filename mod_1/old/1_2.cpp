#include<iostream>

int main() {
    size_t n = 0;
    std::cin >> n;
    int * x = new int[n];
    int * y = new int[n];
    for (size_t i = 0; i < n; i++) {
        std::cin >> x[i] >> y[i];
    }
    double S = 0;
    for (size_t i = 0; i < n; i++) {
        S += (x[i] + x[(i + 1) % n]) * (y[(i + 1) % n] - y[i]);
    }
    S /= 2;
    if (S < 0) {
        S *= -1;
    }
    std::cout << S << std::endl;






}
