#include<iostream>
#include<vector>
#include<string> 

template<typename T>
void swap(T * a, T * b) {
    if (a != b) {
        T swa = *a;
        *a = *b;
        *b = swa;
    }
}

void read(std::vector<std::string> & array) {
    std::string str;
    std::cin >> str;
    str.shrink_to_fit();
    while(!feof(stdin)) {
        array.push_back(str);
        std::cin >> str;
        str.shrink_to_fit();
    }
    array.shrink_to_fit();
}

bool end_cmp(const std::string & str, size_t bit) {
    if (str.length() * 8 < bit + 1) {
        return false;
    } else {
        return true;
    }
}

bool bit_cmp(const std::string & str, size_t bit) {
    if (str[(bit) / 8] & (128 >> (bit % 8))) {
        return true;
    } else {
        return false;
    }
}

size_t partition(std::vector<std::string> & array, size_t left, size_t right, size_t bit, bool(* cmp) (const std::string & str, size_t bit)) {
    size_t border = left;
    for (size_t i = left; i < right; i++) {
        if (!cmp(array[i], bit)) {
            swap(&array[border], &array[i]);
            border++;
        }
    }
    return border;
}

void msd_sort(std::vector<std::string> & array, size_t left, size_t right, size_t bit) {
    if (left + 1 >= right) {
        return;
    }
    size_t end_border = 0, bit_border = 0;
    end_border = partition(array, left, right, bit, end_cmp); 
    bit_border = partition(array, end_border, right, bit, bit_cmp);
    msd_sort(array, end_border, bit_border, bit + 1);
    msd_sort(array, bit_border, right, bit + 1);
}

void print(std::vector<std::string> & array) {
    for (size_t i = 0; i < array.size(); i++) {
        std::cout << array[i] << std::endl;
    }
}

int main() {
    std::vector<std::string> array;
    read(array);
    msd_sort(array, 0, array.size(), 0);
    print(array);
}


