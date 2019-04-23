#include <vector>
#include <string>
#include <iostream>
#include <set>


#define MIN_SIZE 8

template <typename T>
class cell {
 public:
    cell();
    ~cell();
    void set(const T&);
    bool empty();
    const T& value();
    bool iteratable();
    void erase();
 private:
    T  data;
    bool deleted;
    bool clear;
};

template <typename T>
void cell<T>::erase() {
    deleted = true;
    clear = true;
}

template <typename T>
bool cell<T>::iteratable() {
    if (clear == true && deleted == false) {
        return false;
    } else {
        return true;
    }
}

template <typename T>
const T& cell<T>::value() {
    return data;
}

template <typename T>
bool cell<T>::empty() {
    return clear;
}

template <typename T>
void cell<T>::set(const T& value) {
    data = value;
    deleted = false;
    clear = false;
}

template <typename T>
cell<T>::cell() {
    deleted = false;
    clear = true;
}

template <typename T>
cell<T>::~cell() {;}

template <typename T>
class set {
 public:
    set();
    ~set();
    void insert(const T&);
    bool find(const T &);
    bool erase(const T &);
 private:
    std::vector<cell<T>> * data;
    size_t count;
    size_t size;
    
    size_t hash(const T&);
    size_t iter_prob(size_t, size_t);
    void resize(size_t);
};

template <typename T>
size_t set<T>::hash(const T& object) {
    size_t p = 23;
    size_t sum = 0;
    for (int i = 0; i < object.length(); i++) {
        sum = (sum + p * object[i]) % size;
    }
    return sum;
}


template <typename T>
size_t set<T>::iter_prob(size_t prev_probe, size_t i) {
    return (prev_probe + i) % size;
}

template <typename T>
void set<T>::resize(size_t new_size) {
    std::vector<cell<T>> * old_data = data;
    data = new std::vector<cell<T>>;
    data->reserve(new_size);
    for (size_t i = 0; i < new_size; i++) {
        data->push_back(cell<T>());
    }
    size_t old_size = size;
    size = new_size;
    count = 0;
    for (size_t i = 0; i < old_size; i++) {
        if ((*old_data)[i].empty() == false) {
            insert((*old_data)[i].value());
        }
    }
    delete old_data;
}

template <typename T>
set<T>::~set() {
    if (data) {
        delete data;
    }
}

template <typename T>
set<T>::set() {
    data = new std::vector<cell<T>>;
    data->reserve(MIN_SIZE);
    for (size_t i = 0; i < MIN_SIZE; i++) {
        data->push_back(cell<T>());
    }
    count = 0;
    size = MIN_SIZE;
}

template<typename T>
bool set<T>::erase(const T & erase_value) {
    size_t i = 0;
    size_t probe = hash(erase_value);
    while ((*data)[probe].iteratable() == true) {
        if ((*data)[probe].empty() == false && (*data)[probe].value() == erase_value) {
            (*data)[probe].erase();
            count--;
            return true;
        }
        probe = iter_prob(probe, i);
        if (i > size) {
            break;
        }
        i++;
    }
    return false;
}

template <typename T>
bool set<T>::find(const T & find_value) {
    size_t i = 0;
    size_t probe = hash(find_value);
    while ((*data)[probe].iteratable() == true) {
        if ((*data)[probe].empty() == false && (*data)[probe].value() == find_value) {
            return true;
        }
        probe = iter_prob(probe, i);
        if (i > size) {
            break;
        }
        i++;
    }
    return false;
}

template <typename T>
void set<T>::insert(const T& insert_value) {
    if (find(insert_value) == true) {
        return;
    }
    if (count * 4 >= size * 3) {
        resize(size * 8);
    }
    size_t i = 0;
    size_t probe = hash(insert_value);
    while ((*data)[probe].empty() == false) {
        probe = iter_prob(probe, i);
        if (i > size) {
            break;
        } 
        i++;
    }
    (*data)[probe].set(insert_value);
    count++;
}

int main() {
    set<std::string> hash_table;
    char a;
    std::string str;
    std::cin >> a >> str;
    while(!feof(stdin)) {
        if (a == '+') {
            if (hash_table.find(str) == true) {
                std::cout << "FAIL" << std::endl;
            } else {
                hash_table.insert(str);
                std::cout << "OK" << std::endl;
            }
        } else if (a == '-') {
            if (hash_table.erase(str)) {
                std::cout << "OK" << std::endl;
            } else {
                std::cout << "FAIL" <<std::endl;
            }
        } else if (a == '?') {
            if (hash_table.find(str) == true) {
                std::cout << "OK" << std::endl;
            } else {
                std::cout << "FAIL" <<std::endl;
            }
        } else {
            std::cout << "no such command : " << a << std::endl;
            return 0;
        }
        std::cin >> a >> str;
    }
}
