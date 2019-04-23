#include <iostream>

void swap(int64_t * a, int64_t * b) {
    int64_t sw(*a);
    *a = *b;
    *b = sw;
}

int64_t k = 0;

int64_t k_static(int64_t * mass, int64_t left, int64_t right) {
    if (k < left || k > right) {
        return (-1);
    }
    if (left >= right) {
        return mass[left];
    }
    bool big = false;
    int64_t iter = 0;
    swap(&mass[(left + right) / 2], &mass[right]);
    for (int64_t i = left; i < right; i++) {
        if (mass[i] > mass[right]) {
            if (!big) {
                iter = i;
                big = true;
            }
            continue;
        }
        else {
            if (big) {
                swap(&mass[i], &mass[iter]);
                iter++;
            }
        }
    }
    
    if (big) {
        swap(&mass[iter], &mass[right]);
    }
    if (!big) {
        iter = right;
    }

    if (iter == k) {
        return mass[iter];
    }
    if (iter < k) {
        return k_static(mass, iter + 1, right);
    }
    if (iter > k) {
        return k_static(mass, left, iter - 1);
    }
}   

int main() {
    int64_t n = 0;
    std::cin >> n >> k;
    if (k >= n) {
        return -1;
    }
    int64_t * mass = new int64_t[n];
    for (int64_t i = 0; i < n; i++) {
        std::cin >> mass[i];
    }
    std::cout << k_static(mass, 0, n - 1);
}
