/*
 * Найти k-ю порядковую статистику
 * Реализуйте стратегию выбора опорного элемента “медиана трёх”.
 * Функцию Partition реализуйте методом прохода двумя итераторами от конца массива к началу.
 */


#include <algorithm>
#include <iostream>

int64_t medianThree(const int64_t *arr, int64_t left, int64_t right) {
    int64_t a = arr[right];
    int64_t b = arr[left];
    int64_t c = arr[(right - left) / 2 + left];
    int64_t max = std::max(std::max(a, b), c);
    int64_t min = std::min(std::min(a, b), c);
    int64_t median = a + b + c - (min + max);
    if (median == a) {
        return right;
    }
    if (median == b) {
        return left;
    }
    return (right - left) / 2 + left;
}

void print64_t_arr(int64_t *arr, int64_t left, int64_t right) {
    for (int64_t i = left; i < right; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << '\n';
}


int64_t partition(int64_t *arr, int64_t left, int64_t right) {
    int64_t pivot_index = medianThree(arr, left, right);
    int64_t pivot = arr[pivot_index];
    std::swap(arr[right], arr[pivot_index]);
    int64_t i = left;
    int64_t j = left;
    while (j != right) {
        if (arr[j] > pivot) {
            j++;
        } else {
            std::swap(arr[i], arr[j]);
            i++;
            j++;
        }
    }
    std::swap(arr[i], arr[j]);
    return i;
}

int64_t findKStat(int64_t *arr, int64_t array_length, int64_t k) {
    int64_t left = 0;
    int64_t right = array_length - 1;
    while (true) {
        int64_t pivotPos = partition(arr, left, right);
        if (k == pivotPos) {
            return arr[k];
        }
        if (k < pivotPos) {
            right = pivotPos;
        } else {
            left = pivotPos + 1;
        }
    }
}

int main() {
    int64_t array_length = 0;
    int64_t k = 0;
    std::cin >> array_length >> k;
    int64_t *arr = new int64_t[array_length];
    for (int64_t i = 0; i < array_length; i++) {
        std::cin >> arr[i];
    }
    std::cout << findKStat(arr, array_length, k);
    delete [] arr;
    return 0;
}
