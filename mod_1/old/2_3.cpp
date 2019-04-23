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
            return mass[center];
        }
    }
    for(int64_t i = left; i <= right; i++) {
        if(mass[i] == x) {
            return mass[i];
        }
    }
    return -1;
}

int main() {
    int64_t n = 0;
    int64_t m = 0;
    std::cin >> n >> m;
    int64_t * A = new int64_t[n];
    int64_t * B = new int64_t[m];
    for (int64_t i = 0; i < n; i++) {
        std::cin >> A[i];
    }
    for (int64_t i = 0; i < m; i++) {
        std::cin >> B[i];
    }
    int64_t res = -1;
    for (int64_t i = 0; i < m; i++) {
        res = binary_search(A, n, B[i]);
        if (res != -1) {
            std::cout << res << ' ';
        }
    }
    std::cout << std::endl;
}
