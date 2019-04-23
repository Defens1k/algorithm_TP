#include <iostream>

#define STARTING_SEARCH_POSITION 4 // we start search in 4,8,16,32...
#define MIN_SIZE_TO_BINARY_SEARCH 4 
//Дан массив целых чисел А[0..n-1]. Известно, что на интервале [0, m] значения массива строго возрастают, а на интервале [m, n-1] строго убывают. Найти m за O( log m ).
//2 ≤ n ≤ 10000. 

int * read_array(int * array_size) {
    std::cin >> *array_size;
    int * array = new int[*array_size];
    if (array == NULL) {
        return NULL;
    }
    for (int i = 0; i < *array_size; i++) {
        std::cin >> array[i];
    }
    return array;
}

void find_scope(const int * array, int array_size, int * left_scope, int * right_scope) {
    *left_scope = 0;
    *right_scope = array_size - 1;
    int i = STARTING_SEARCH_POSITION;
    int prev_i = 0;
    while (1) {
        if (i >= array_size - 1) {
            *left_scope = prev_i;
            break;
        }
        if (array[i - 1] > array[i]) {
            *right_scope = i - 1;
            *left_scope = prev_i;
            break;
        }
        prev_i = i;
        i *= 2;
    }
    return;
}

int binary_search(int * array, int left_scope, int right_scope) {
    int median = left_scope + (right_scope - left_scope) / 2;
    while (left_scope + MIN_SIZE_TO_BINARY_SEARCH < right_scope) {
        if (array[median] > array[median + 1]) {
            right_scope = median;
        }
        else {
            left_scope = median;
        }
        median = left_scope + (right_scope - left_scope) / 2;
    }
    int i = left_scope;
    for (i = 0; i < right_scope; i++) {
        if (array[i] > array[i + 1]) {
            break;
        }
    }
    return i;
}

int find_position(int * array, int array_size) {
    int left_scope = 0, right_scope = 0;
    find_scope(array, array_size, &left_scope, &right_scope);
    return binary_search(array, left_scope, right_scope);
}

int main() {
    int array_size = 0;
    int * array = read_array(&array_size);
    if (array == NULL) {
        std::cerr << "error\n";
        return 0;
    }
    int position = find_position(array, array_size);
    delete [] array;
    if (position == -1) {
        std::cerr << "error\n";
        return 0;       
    }
    std::cout << position << std::endl;
}
