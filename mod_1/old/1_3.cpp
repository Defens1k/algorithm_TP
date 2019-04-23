#include<iostream>

int main() {
    long int a = 0;
    std::cin >> a;
    long int * A = new long int[a];
    for (long int i = 0; i < a; i++) {
        std::cin >> A[i];
    }
    long int b = 0;
    std::cin >> b;
    long int * B = new long int[b];
    for (long int i = 0; i < b; i++) {
        std::cin >> B[i];
    }
    long int k = 0;
    std::cin >> k;
    long int iter_a = 0;
    long int iter_b = b - 1;
    long int count = 0;
    while ((iter_b >= 0) && (iter_a <= a - 1)) {
        if((A[iter_a] + B[iter_b]) == k) {
            iter_b--;
            iter_a++;
            count++;
            continue;
        }
        if((A[iter_a] + B[iter_b]) > k) {
            iter_b--;
            continue;
        }
        if((A[iter_a] + B[iter_b]) < k) {
            iter_a++;
            continue;
        }

    }
    std::cout << count << std::endl;


}




