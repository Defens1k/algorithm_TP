/*Вовочка ест фрукты из бабушкиной корзины.
В корзине лежат фрукты разной массы. Вовочка может поднять не более K грамм. Каждый фрукт весит не более K грамм. За раз он выбирает несколько самых тяжелых фруктов, которые может поднять одновременно, откусывает от каждого половину и кладет огрызки обратно в корзину. Если фрукт весит нечетное число грамм, он откусывает большую половину. Фрукт массы 1гр он съедает полностью.
Определить за сколько подходов Вовочка съест все фрукты в корзине.
*/
#include<iostream>
#include<cassert>
#define MIN_CAPACITY 16

template<typename T>
void swap(T * x, T * y) {
    T swap = * x;
    *x = *y;
    *y = swap;
}

template<typename T>
class Heap { 
 public:
    Heap();
    Heap(T *, size_t);
    ~Heap() {delete [] data;};
    void push(const T&);
    bool empty();
    T pop();
    const T& top();
 private:
    void sift_up(size_t index);
    void sift_down(size_t index);
    void resize(size_t new_capacity);
    T * data;
    size_t capacity;
    size_t right_data_scope; //index of last elem + 1
};

template<typename T>
Heap<T>::Heap(): data(nullptr), capacity(MIN_CAPACITY), right_data_scope(0) {
    data = new T[MIN_CAPACITY];
}

template<typename T>
Heap<T>::Heap(T * array, size_t size): data(array), capacity(size), right_data_scope(size) {
    assert(size != 0);
    size_t i = size / 2;
    while (true) {
        sift_down(i);
        if (i == 0) {
            break;
        }
        i--;
    }
}

template<typename T>
void Heap<T>::push(const T& x) {
    if(right_data_scope >= capacity) {
        resize(MIN_CAPACITY + 2 * capacity);
    }
    data[right_data_scope] = x;
    right_data_scope++;
    sift_up(right_data_scope - 1);
}

template<typename T>
bool Heap<T>::empty() {
    return !right_data_scope;
}

template<typename T>
T Heap<T>::pop() {
    assert(right_data_scope != 0);
    T top_elem = data[0];
    data[0] = data[right_data_scope - 1];
    right_data_scope--;
    sift_down(0);
    return top_elem;
}

template<typename T>
const T& Heap<T>::top() {
    assert(right_data_scope != 0);
    return data[0];
}


template<typename T>
void Heap<T>::sift_up(size_t index) {
    if (index <= 0) {
        return;
    }
    if (data[(index - 1) / 2] < data[index]) {
        swap(&data[(index - 1) / 2], &data[index]);
        sift_up((index - 1) / 2);
    } else {
        return;
    }
}

template<typename T>
void Heap<T>::sift_down(size_t index) {
    if (index >= right_data_scope / 2) {
        return;
    }
    if (data[index * 2 + 1] > data[index] && data[index * 2 + 2] <= data[index * 2 + 1] ) {
        swap(&data[index * 2 + 1], &data[index]);
        sift_down(index * 2 + 1);
    }
    if (data[index * 2 + 2] > data[index] && data[index * 2 + 1] <= data[index * 2 + 2] ) {
        swap(&data[index * 2 + 2], &data[index]);
        sift_down(index * 2 + 2);       
    }
}

template<typename T>
void Heap<T>::resize(size_t new_capacity) {
    T * new_data = new T[new_capacity];
    for(size_t i = 0; i < right_data_scope; i++) {
        new_data[i] = data[i];
    }
    delete[] data;
    data = new_data;
    capacity = new_capacity;
}



int main() {
    int64_t n = 0;
    int64_t k = 0;
    std::cin >> n;

    int64_t apple_mass(0);
    int64_t * apple_array = new int64_t[n];

    for (int64_t i = 0; i < n; i++) {
        std::cin >> apple_array[i];
    }
    Heap<int64_t> grandmother(apple_array, n);
    std::cin >> k;
    int64_t mass_in_vovochka = 0;
    int hod = 0;
    int64_t * array = new int64_t[n + 1];
    size_t i = 0;
    while (!grandmother.empty()) {
        mass_in_vovochka = 0;
        i = 0;
        while(!grandmother.empty()) {
            if (mass_in_vovochka + grandmother.top() <= k) {
                array[i] = grandmother.top();
                mass_in_vovochka += grandmother.top();
                grandmother.pop();
                i++;
            } else {
                break;
            }
        }
        for (int64_t j = 0; j <= i; j++) {
            if (array[j] < 2) {
                continue;
            }
            grandmother.push(array[j] / 2);
        }
        hod++;
    }
    std::cout << hod << std::endl;
    delete [] array;
}
