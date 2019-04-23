#include <iostream>


int main() {
    int n = 0;
    int *a = nullptr;
    int *b = nullptr;
    int res = 0;
    int a_a = 0;
    int b_a = 0;

    std::cin >> n;
    a = new int[n];
    b = new int[n];
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    for (int i = 0; i < n; i++) {
        std::cin >> b[i];
    }

    int max = a[0] + b[0];
    for (int i = 0; i < n; i++) {
        if (a[i] > a[res]) {
            res = i;
        }
        if (a[res] + b[i] > max) {
            max = a[res] + b[i];
            a_a = res;
            b_a = i;
        }
    }
    std::cout << a_a << " " << b_a  << '\n';
}
