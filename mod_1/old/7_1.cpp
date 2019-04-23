#include <iostream>
#include <cstring>
#include <algorithm>

#define N 1000005
#define STR_MAX_LEN 280


int symbol_number = 0;

int cmp(char * a, char * b) {
    return a[symbol_number] > b[symbol_number];
}

void merge(char ** arr, int left, int mid, int right, int(*cmp) (char * a, char * b)) {
    int it1 = 0, it2 = 0;
    char ** res = new char*[right - left];

    while ((left + it1 < mid) && (mid + it2 < right)) {
        if (cmp(arr[left + it1], arr[mid + it2])) {
            res[it1 + it2] = arr[mid + it2];
            it2++;
        }
        else {
            res[it1 + it2] = arr[left + it1];
            it1++;
        }
    }

    while (left + it1 < mid) {
        res[it1 + it2] = arr[left + it1];
        it1++;
    }

    while (mid + it2 < right) {
        res[it1 + it2] = arr[mid + it2];
        it2++;
    }

    for (int i = 0; i < it1 + it2; i++) {
        arr[left + i] = res[i];
    }
    delete [] res;
}

void mergeSort(char ** arr, int left, int right, int(*cmp)(char * a, char * b)) {
    int n = right - left;
    for (int i = 1; i <= n; i *= 2) {
        for (int j = 0; j < n - i; j += 2 * i) {
            merge(arr, left + j, left + j + i, std::min(left + j + 2 * i, right), cmp);
        }
    }
}

int main() {
    char ** mass = new char*[N];
    int count_strings = 0;
    int max_len = 0;
    while (!feof(stdin)) {
        mass[count_strings] = new char[STR_MAX_LEN];
        std::cin.getline(mass[count_strings], STR_MAX_LEN);
        for (int i = strlen(mass[count_strings]); i < STR_MAX_LEN; i++) {
            mass[count_strings][i] = char(0);
        }
        if (strlen(mass[count_strings]) > max_len) {
            max_len = strlen(mass[count_strings]);
        }
        count_strings++;
    }
    
   // for (int i = count_strings; i < N; i++) {
       // delete [] mass[i];
     //   mass[i] = nullptr;
    //}
    for (symbol_number = max_len - 1; symbol_number >= 0; symbol_number--) {
        mergeSort(mass, 0, count_strings - 1, cmp);
    }
    for (int i = 0; i < count_strings - 1; i++) {
        std::cout << mass[i] << std::endl;
 //       delete[] mass[i];
   //     mass[i] = nullptr;
    }
    delete[] mass;
}

