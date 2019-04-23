#include <iostream>

#define MIN_SIZE 32

class Queue {
 public:
    Queue();
    ~Queue();
    int64_t pop_front();
    void push_back(int64_t input_data);
    int64_t size();  //return lenght of queue
    bool is_empty();  //is queue empty?
    bool resize(int64_t new_size);  // if (new_size > free_cell) => size = new_size
    int64_t free_cell();
 private:
    bool empty;
    int64_t * data;  //pointer of data
    int64_t data_size; 
    int64_t front_index;  // index of oldest cell
    int64_t back_index;  //index of newest cell
};

Queue::Queue() {
    empty = true; 
    data_size = MIN_SIZE;
    data = new int64_t[MIN_SIZE];
    front_index = 0;
    back_index = 0;
}

int64_t Queue::pop_front() {
    if (is_empty()) {
        return -1;
    }
    else {
        int64_t out_data = data[front_index];
        if (size() == 1 + free_cell()) {
            resize(MIN_SIZE);
            empty = true;
            return out_data;
        }
        front_index = (front_index + 1) % size();
        if ((free_cell() * 20 > 19 * size()) && (size() > MIN_SIZE)) {
            resize(size() / 2);
        }
        return out_data;
    }
}

void Queue::push_back(int64_t input_data) {
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

int64_t Queue::size() {
    return data_size;
}

bool Queue::is_empty() {
    return empty;
}

bool Queue::resize(int64_t new_size) {
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
        data = new int64_t[new_size];
        data_size = new_size;
        empty = true;
    }
    int64_t * new_data = new int64_t[new_size];
    int64_t new_data_iterator = 0;
    int64_t old_data_iterator = front_index;
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

int64_t Queue::free_cell() {
    if (is_empty()) {
        return size();
    }
    if (front_index > back_index) {
        return front_index - back_index - 1;
    }
    if (front_index <= back_index) {
        return size() + front_index - back_index - 1;
    }
}

Queue::~Queue() {
    if (data) {
        delete [] data;
    }
}

int main() {
    Queue q;
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
            if (b != q.pop_front()) {
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
