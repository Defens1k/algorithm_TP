#include <iostream>
#include <vector>
#include <queue>

template<typename T>
class node;
template<typename T>
class tree;

template<typename T>
class level_order_iterator {
 public:
    level_order_iterator(node<T> *);
    bool operator != (const level_order_iterator &);
    void operator ++ ();
    node<T> * current;
 private:
    std::queue<node<T> *> q;
};

template<typename T>
void level_order_iterator<T>::operator ++ () {
    if (current == nullptr) {
        return;
    }
    if (current->get_left() != nullptr) {
        q.push(current->get_left());
    }
    if (current->get_right() != nullptr) {
        q.push(current->get_right());
    }
    q.pop();
    if (q.empty() == true) {
        current = nullptr;
        return;
    }
    current = q.front();
}

template<typename T>
bool level_order_iterator<T>::operator != (const level_order_iterator & right) {
    return current != right.current;
}

template<typename T>
level_order_iterator<T>::level_order_iterator(node<T> * tree) {
    current = tree;
    if (tree != nullptr) {
        q.push(tree);
    }
}

template<typename T>
class tree {
 public:
    tree();
    ~tree();
    void push(T);
    level_order_iterator<T> level_order_begin();
    level_order_iterator<T> level_order_end();
 private:
    node<T> * top;
};

template<typename T>
tree<T>::~tree() {
    if (top == nullptr) {
        return;
    }
    std::vector<node<T> *> nodes;
    nodes.push_back(top);
    size_t i = 0;
    while (i < nodes.size()) {
        if(nodes[i]->get_right() != nullptr) {
            nodes.push_back(nodes[i]->get_right());
        }
        if(nodes[i]->get_left() != nullptr) {
            nodes.push_back(nodes[i]->get_left());
        }
        i++;
    }
    for (auto iter = nodes.begin(); iter !=nodes.end(); iter++) {
        delete *iter;
    }
}

template<typename T>
level_order_iterator<T> tree<T>::level_order_begin() {
    return level_order_iterator<T>(top);
}

template<typename T>
level_order_iterator<T> tree<T>::level_order_end() {
    return level_order_iterator<T>(nullptr);
}

template<typename T>
tree<T>::tree() {
    top = nullptr;
}

template<typename T>
void tree<T>::push(T pushing_value) {
    if (top == nullptr) {
        top = new node<T>(pushing_value);
        return;
    }
    node<T> * ptr = top;
    while (1) {
         if (ptr->get_data() <= pushing_value) {
            if (ptr->get_right() == nullptr) {
                ptr->set_right(new node<T>(pushing_value));
                return;
            }
            ptr = ptr->get_right();
        } else {
            if (ptr->get_left() == nullptr) {
                ptr->set_left(new node<T>(pushing_value));
                return;
            }
            ptr = ptr->get_left();
        }       
    }
    return;
}
template<typename T>
class node {
 public:
    node();
    node(T);
    node<T> * get_right();
    void set_right(node<T> *);
    node<T> * get_left();
    void set_left(node<T> *);
    T& get_data();
 private:
    T data;
    node<T> * left;
    node<T> * right;
};

template<typename T>
void node<T>::set_left(node<T> * ptr) {
    left = ptr;
}

template<typename T>
void node<T>::set_right(node<T> * ptr) {
    right = ptr;
}

template<typename T>
node<T> * node<T>::get_left() {
    return left;
}

template<typename T>
node<T> * node<T>::get_right() {
    return right;
}

template<typename T>
T& node<T>::get_data() {
    return data;
}

template<typename T>
node<T>::node() {
    left = nullptr;
    right = nullptr;
}

template<typename T>
node<T>::node(T value) {
    data = value;
    left = nullptr;
    right = nullptr;
}

int main() {
    tree<int> t;
    int n = 0;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        int value = 0;
        std::cin >> value;
        t.push(value);
    }
    for (auto i = t.level_order_begin(); i != t.level_order_end(); ++i) {
        std::cout << i.current->get_data() << " ";
    }
}
