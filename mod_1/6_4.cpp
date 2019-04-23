//Реализуйте стратегию выбора опорного элемента “случайный элемент”. Функцию Partition реализуйте методом прохода двумя итераторами от конца массива к началу.
#include<iostream>
#include<ctime>
#include<cstdlib> 

template<typename T>
void swap(T * a, T * b) {
    if (a != b) {
        T swa = *a;
        *a = *b;
        *b = swa;
    }
}

template<typename T>
int64_t partition(T * array, int64_t left, int64_t right) {
    if (left == right) {
        return left;
    }
    int64_t pivot = left + std::rand() % (right - left + 1);
    swap(&array[pivot], &array[right]);
    int64_t border = right;
    for (int64_t i = right - 1; i >= left; i--) {
        if (array[i] > array[right]) {
            swap(&array[border - 1], &array[i]);
            border--;
        }
    }
    swap(&array[right], &array[border]);
    return border;
}

template<typename T>
T k_statistic(T * array, int64_t lenght, int64_t k) {
    std::srand(unsigned(std::time(0)));
    int64_t left = 0;
    int64_t right = lenght - 1;
    while (true) {
        int64_t pivot = partition(array, left, right);
        if (pivot > k) {
            right = pivot - 1;
        } 
        else if (pivot < k) {
            left = pivot + 1;
        } 
        else {
            return array[pivot];
        }
    }
    return -1;
}


int main() {
    int64_t n = 0, k = 0;
    std::cin >> n >> k;
    int64_t * array = new int64_t[n];
    if (array == nullptr) {
        std::cerr << "error";
        return 0;
    }
    for (int64_t i = 0; i < n; i++) {
        std::cin >> array[i];
    }
    std::cout << k_statistic(array, n, k);
    
    delete [] array;
}
