#include <iostream>
#include <cassert>
//Реализовать очередь с динамическим зацикленным буфером.

//Обрабатывать команды push back и pop front.

#define MIN_SIZE 32
#define RESIZE_RATION 20  // when the number of occupied cells becomes equal to (1 / RESIZE_RATION) we halve the array

template <typename T>
class Queue {
 public:
    Queue();
    ~Queue();
    T pop_front();
    void push_back(const T& input_data);
    bool is_empty();  //is queue empty?
 private:
    bool resize(size_t new_size);  // if (new_size > free_cell) => size = new_size
    bool empty;
    T * data;  //pointer of data
    size_t data_size; 
    size_t front_index;  // index of oldest cell
    size_t back_index;  //index of newest cell
    size_t free_cell();
    size_t size();  //return lenght of queue

};

template <typename T>
Queue<T>::Queue() {
    empty = true; 
    data_size = MIN_SIZE;
    data = new T[MIN_SIZE];
    front_index = 0;
    back_index = 0;
}

template <typename T>
T Queue<T>::pop_front() {
    assert (!is_empty());
    T out_data = data[front_index];
    if (size() == 1 + free_cell()) {
        resize(MIN_SIZE);
        empty = true;
        return out_data;
     }
    front_index = (front_index + 1) % size();
    if ((free_cell() * RESIZE_RATION > (RESIZE_RATION - 1) * size()) && (size() > MIN_SIZE)) {
        resize(size() / 2);
    }
    return out_data;
}

template <typename T>
void Queue<T>::push_back(const T& input_data) {
    if (is_empty()) {
        data[0] = input_data;
        front_index = 0;
        back_index = 0;
        empty = false;
        return;
    }
    if (free_cell() == 0) {
        resize(size() * 2);
        push_back(input_data);
        return;
    }
    if (size() == (back_index + 1)) {
        data[0] = input_data;
        back_index = 0;
        empty = false;
        return;
    }
    else {
        data[back_index + 1] = input_data;
        back_index++;
        empty = false;
    }
}

template <typename T>
size_t Queue<T>::size() {
    return data_size;
}

template <typename T>
bool Queue<T>::is_empty() {
    return empty;
}

template <typename T>
bool Queue<T>::resize(size_t new_size) {
    if (new_size < size() - free_cell()) {
        return false;
    }
    if (new_size == size()) {
        return true;
    }
    if (new_size < MIN_SIZE) {
        return false;
    }
    if (is_empty()) {
        delete [] data;
        data = new T[new_size];
        data_size = new_size;
        empty = true;
    }
    T * new_data = new T[new_size];
    size_t new_data_iterator = 0;
    size_t old_data_iterator = front_index;
    while (old_data_iterator != back_index) {
        new_data[new_data_iterator] = data[old_data_iterator];
        new_data_iterator++;
        old_data_iterator = (old_data_iterator + 1) % size();
    }
    new_data[new_data_iterator] = data[old_data_iterator];
    delete []data;
    data = new_data;
    front_index = 0;
    back_index = new_data_iterator;
    data_size = new_size;
    return true;
}

template <typename T>
size_t Queue<T>::free_cell() {
    if (is_empty()) {
        return size();
    }
    else if (front_index > back_index) {
        return front_index - back_index - 1;
    } else {
        return size() + front_index - back_index - 1;
    }
}

template <typename T>
Queue<T>::~Queue() {
    if (data) {
        delete [] data;
    }
}

int main() {
    Queue <int64_t> q;
    int64_t n = 0;
    int64_t a , b;
    bool input_true = true;
    std::cin >> n;
    for (int64_t i = 0; i < n; i++) {
        std::cin >> a >> b;
        if (a == 3) {
               q.push_back(b);
        }
        if (a == 2) {
            if (q.is_empty()) {
                if (b != -1) {
                    input_true = false;
                }
            }
            else if (b != q.pop_front()) {
                input_true = false;
            }
        } 
    }
    if (input_true) {
        std::cout << "YES"; 
    }
    else {
        std::cout << "NO";
    }
}
