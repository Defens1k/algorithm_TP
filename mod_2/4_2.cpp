#include <iostream>

class avl_node {
 public:
    avl_node(int _value);
    avl_node(const avl_node & old);
    ~avl_node();
    avl_node & operator=(const avl_node & old);
    avl_node * insert(int _value);
    avl_node * find(int);
    int get_value() {return value;};
    avl_node * remove(int k);
    int get_sum() {return sum;};
    int k_static(int);
 private:
    void fix_sum();
    avl_node * findmin();
    avl_node * removemin();
    avl_node * balance();
    short balance_factor();
    avl_node * add_all(avl_node * new_tree) const;
    void fix_height();
    avl_node * rotate_right();
    avl_node * rotate_left();
    int value;
    avl_node * left;
    avl_node * right;
    short height;
    int sum;
};

int avl_node::k_static(int pos) {
    if (pos == 1 && left == nullptr) {
        return value;
    }
    if (left != nullptr) {
        if (left->sum + 1 == pos) {
            return value;
        }
        if (right != nullptr) {
            if (left->sum >= pos) {
                return left->k_static(pos);
            } else {
                return right->k_static(pos - 1 - left->sum);
            }
        } else {
            return left->k_static(pos);
        }
    } else {
         if (right != nullptr) {
             return right->k_static(pos - 1);
        } else {
            return value;
        }       
    }
}

avl_node* avl_node::findmin() {
	return left?left->findmin():this;
}

avl_node* avl_node::removemin() {
	if (left == nullptr) {
		return right;
    }
	left = left->removemin();
	return balance();
}

avl_node * avl_node::remove(int k) {

	if (k < value) {
        if (left != nullptr) {
		    left = left->remove(k);
        }
    }
	else if( k > value ) {

        if (right != nullptr) {
		    right = right->remove(k);	
        }
    }
	else {
		avl_node* q = left;
		avl_node* r = right;
		delete this;
		if(r == nullptr) {
            return q;
        }
        avl_node * min = nullptr;
        min = r->findmin();
        min->right = r->removemin();
        min->left = q;
		return min->balance();
	}
	return balance();
}


avl_node * avl_node::find(int _value) {
    if (_value == value) {
        return this;
    }
    if (_value < value) {
        if (left != nullptr) {
            return left->find(_value);
        } else {
            return nullptr;
        }
    } else {
        if (right != nullptr) {
            return right->find(_value);
        } else {
            return nullptr;
        }
    }
}

avl_node::avl_node(int _value): value(_value), left(nullptr), right(nullptr), height(1), sum(1) {
}

avl_node * avl_node::add_all(avl_node * new_tree)const {
    if (left) {
        new_tree = left->add_all(new_tree);
    }
    if (right) {
        new_tree = right->add_all(new_tree);
    }
    new_tree = new_tree->insert(value);
    return new_tree;
}

avl_node::avl_node(const avl_node & old): value(0), left(nullptr), right(nullptr), height(1) {
    avl_node * new_tree = new avl_node(0);
    new_tree = old.add_all(new_tree);

    right = new_tree->right;
    left = new_tree->left;
    value = new_tree->value;
    height = new_tree->height;

    delete new_tree;
}

avl_node::~avl_node() {
}

avl_node & avl_node::operator=(const avl_node & old) {
    if (this == &old) {
        return *this;
    }
    delete this;
    avl_node * new_tree = new avl_node(0);
    new_tree = old.add_all(new_tree);

    right = new_tree->right;
    left = new_tree->left;
    value = new_tree->value;
    height = new_tree->height;

    delete new_tree;
    return *this;
}

short avl_node::balance_factor() {
    if (!left) {
        if (!right) {
            return 0;
        } else {
            return right->height;
        }
    } else {
        if (!right) {
            return (-1)*left->height;
        } else {
            return right->height - left->height;
        }
    }
}

void avl_node::fix_height() {
     if (!left) {
        if (!right) {
            height = 1;
        } else {
            height = 1 + right->height;
        }
    } else {
        if (!right) {
            height = 1 + left->height;
        } else {
            height = 1 + std::max(right->height, left->height);
        }
    }
}

avl_node * avl_node::rotate_right() {
    int a = 0;
    if (left != nullptr && left->left != nullptr) {
        a = left->left->get_sum();
    }
    int b = 0;
    if (left != nullptr && left->right != nullptr) {
        b = left->right->get_sum();
    }
    int c = 0;
    if (right != nullptr) {
        c = right->get_sum();
    }
    avl_node * q = left;
    left = q->right;
    q->right = this;
    q->fix_height();
    fix_height();
    q->right->sum = b + c + 1;
    q->sum = a + b + c + 2;
    return q;
}

avl_node * avl_node::rotate_left() {
    int c = 0;
    if (right != nullptr && right->right != nullptr) {
        c = right->right->get_sum();
    }
    int b = 0;
    if (right != nullptr && right->left != nullptr) {
        b = right->left->get_sum();
    }
    int a = 0;
    if (left != nullptr) {
        a = left->get_sum();
    }
    avl_node * p = right;
    right = p->left;
    p->left = this;
    fix_height();
    p->fix_height();
    p->left->sum = a + b + 1;
    p->sum = a + b + c + 2;
    return p;
}

void avl_node::fix_sum() {
    int new_sum = 1;
    if (left != nullptr) {
        new_sum += left->get_sum();
    }
    if (right != nullptr) {
        new_sum += right->get_sum();
    }
    sum = new_sum;
}

avl_node * avl_node::balance() {
    fix_height();
    if (balance_factor() == 2) {
        if (right->balance_factor() < 0) {
            right = right->rotate_right();
        }
        return rotate_left();
    }
    if (balance_factor() == -2) {
        if (left->balance_factor() > 0) {
            left = left->rotate_left();
        }
        return rotate_right();
    }
    this->fix_sum();
    return this;
}

avl_node * avl_node::insert(int  _value) {
    if (value > _value) {
        if (left) {
            left = left->insert(_value);
        } else {
            left = new avl_node(_value);
        }
    } else {
        if (right) {
            right = right->insert(_value);
        } else {
            right = new avl_node( _value);
        }
    }
    return balance();
}

int main() {
    int n = 0;
    std::cin >> n;
    int k = 0;
    int st = 0;
    avl_node * top = nullptr;
    for (int i = 0; i < n; i++) {
        std::cin >> k >> st;
        if (top != nullptr) {
            if (k > 0) {
                top = top->insert(k);
            } else {
                top = top->remove(-k);
            }
        } else if (k >=0){
            top = new avl_node(k);
        }
        std::cout << top->k_static(st + 1) << " ";
    }
}
