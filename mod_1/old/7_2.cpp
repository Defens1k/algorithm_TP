#include <iostream>

void swap(long long int * a, long long int * b) {
    long long int sw(*a);
    *a = *b;
    *b = sw;
}

void lsd_sort(long long int * mass, long long int left, long long int right, long long int bit) {
    if (bit == 0) {
        return;
    }
    if (left >= right) {
        return;
    }
    bool big = false;
    long long int iter = left;
    for (long long int i = left; i <= right; i++) {
        if (mass[i] & bit) {
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
    if (!big || iter == left) {
        lsd_sort(mass, left, right, bit >> 1);
        return;
    }
    else {
        lsd_sort(mass, left, iter - 1, bit >> 1);
        lsd_sort(mass, iter, right   , bit >> 1);
        return;
    }
}   

int main() {
    long long int n = 0;
    std::cin >> n;
    long long int bit = 1;
    bit <<= 62;
    long long int * mass = new long long int[n];
    for (long long int i = 0; i < n; i++) {
        std::cin >> mass[i];
    }
    while(1) {
    lsd_sort(mass, 0, n - 1, bit);
    }
    for (long long int i = 0; i < n; i++) {
        std::cout << mass[i] << ' ';
    
    }
}
