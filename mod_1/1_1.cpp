#include <iostream>
//Даны два массива целых чисел одинаковой длины A[0..n-1] и B[0..n-1]. Необходимо найти первую пару индексов i0 и j0, , такую что A[i0] + B[j0] = max {A[i] + B[j], где 0 <= i < n, 0 <= j < n, i <= j}. Время работы - O(n). n ≤ 100000.

int read(int ** a, int ** b) {
    int n = 0;
    std::cin >> n;
    *a = new int[n];
    *b = new int[n];
    for (int i = 0; i < n; i++) {
        std::cin >> (*a)[i];
    }

    for (int i = 0; i < n; i++) {
        std::cin >> (*b)[i];
    }
    return n;
}

void solve(int * a, int * b, int n, int * a_a, int * b_a) {
    int res = 0;
    int max = a[0] + b[0];
    for (int i = 0; i < n; i++) {
        if (a[i] > a[res]) {
            res = i;
        }
        if (a[res] + b[i] > max) {
            max = a[res] + b[i];
            *a_a = res;
            *b_a = i;
        }
    }
}

int main() {
    int n = 0;
    int *a = nullptr;
    int *b = nullptr;
    int a_a = 0;
    int b_a = 0;
    n = read(&a, &b);
    solve(a, b, n, &a_a, &b_a);
    std::cout << a_a << " " << b_a  << std::endl;
    delete[] a;
    delete[] b;
}
