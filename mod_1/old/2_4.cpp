#include <iostream>

int64_t binary_search(const int64_t * mass, const int64_t len, const int64_t x) {
    int64_t left = 0;
    int64_t right = len - 1;
    int64_t center = left / 2 + right / 2;
    while(right - left > 2) {
        center = left / 2 + right / 2;
        if(mass[center] < x) {
            left = center;
            continue;
        }

        if(mass[center] > x) {
            right = center;
            continue;
        }

        if(mass[center] == x) {
            return center;
        }
    }
    for(int64_t i = left; i <= right; i++) {
        if(mass[i] >= x) {
            if (i == 0) {
                return 0;
            }
            if (mass[i] - x >= x - mass[i - 1]) {
                return i - 1;
            } 
            else {
                return i;
            }
        }   
    }
    return right;
}

int main() {
    int64_t n = 0;
    int64_t m = 0;
    std::cin >> n;
    int64_t * A = new int64_t[n];
    for (int64_t i = 0; i < n; i++) {
        std::cin >> A[i];
    }
    std::cin >> m;
    int64_t * B = new int64_t[m];
    for (int64_t i = 0; i < m; i++) {
        std::cin >> B[i];
    }
    for (int64_t i = 0; i < m; i++) {
        std::cout << binary_search(A, n, B[i]) << ' ';
    }
    std::cout << std::endl;
}
