#include <iostream>

int min (int a, int b) {
    return a < b ? a : b;
}

int compare(int a, int b) {
    return a > b;
}

void merge(int * arr, int left, int mid, int right, int(*cmp) (int a, int b)) {
    int it1 = 0, it2 = 0;
    int* res = new int[right - left];

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
}

void mergeSort(int * arr, int left, int right, int(*cmp)(int a, int b)) {
    int n = right - left;
    for (int i = 1; i <= n; i *= 2) {
        for (int j = 0; j < n - i; j += 2 * i) {
            merge(arr, left + j, left + j + i, min(left + j + 2 * i, right), cmp);
        }
    }
}



int main() {
    int n = 0;
    std::cin >> n;
    int * l = new int[n];
    int * r = new int[n];
    for (int i = 0; i < n; i++) {
        std::cin >> l[i] >> r[i];
    }
    mergeSort(l, 0, n, compare);
    mergeSort(r, 0, n, compare);
     
    int iter_l = 0;  //  pointers to next positions
    int iter_r = 0;  //
    int prev_pos = 0;
    int current_pos = 0;
    size_t sum_len = 0;
    int current_layer = 0;
    int j = 0;

    while (1) {
        j++;
        if (iter_l >= n) {
            if (iter_r >= n) {
                std::cout << sum_len << std::endl;
                return 0;
            }
            if(current_layer == 1) {
                sum_len += r[iter_r] - current_pos;
            }
            current_pos = r[iter_r];
            iter_r++;
            current_layer--;
            continue;
        }
        
        if (current_layer == 1) {
            sum_len += min(l[iter_l], r[iter_r]) - current_pos;
        }

        if (l[iter_l] < r[iter_r]) {  // open
            current_pos = l[iter_l];
            iter_l++;
            current_layer++;
            continue;
        }
        if (l[iter_l] > r[iter_r]) {  // close
            current_pos = r[iter_r];
            iter_r++;
            current_layer--;
            continue;
        }
        if (l[iter_l] == r[iter_r]) {  // close
            current_pos = r[iter_r];
            iter_r++;
            iter_l++;
            continue;
        }
        std::cout << "lose\n";
    }
}



