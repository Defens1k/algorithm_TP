#include <iostream>

int64_t binary_search(const int64_t * mass, const int64_t len) {
    if (mass[0] > mass[1]) {
        return 0;
    }
    if (mass[len - 1] > mass[len - 2]) {
        return len - 1;
    }
    int64_t left = 0;
    int64_t right = len - 1;
    int64_t center = left / 2 + right / 2;
    while(right - left > 2) {
        center = left / 2 + right / 2;
        if(mass[center] < mass[center + 1]) {
            left = center;
            continue;
        }

        if(mass[center] > mass[center + 1]) {
            right = center + 1;
            continue;
        }
    }
    for(int64_t i = left; i <= right; i++) {
        if(mass[i] < mass[i + 1] && mass[i + 1] > mass[i + 2]) {
            return i + 1;
        }
    }
}

int main() {
    int64_t n = 0;
    std::cin >> n;
    int64_t * mass = new int64_t[n];
    for (int64_t i = 0; i < n; i++) {
        std::cin >> mass[i];
    }
        std::cout << binary_search(mass, n) << ' ';
}
