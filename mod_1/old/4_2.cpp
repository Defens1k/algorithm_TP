#include<iostream>
#include<queue>

int64_t n = 0;
int64_t sum = 0;

int main() {
    std::cin >> n;
    std::priority_queue <int64_t> q;
    for (int64_t i = 0; i < n; i++) {
        int64_t x(0);       
        std::cin >> x;
        q.push(-x);
    }
    int64_t sum = 0;
    while (1) {
        int64_t x(q.top());
        q.pop();
        int64_t y(q.top());
        q.pop();
        sum += x + y;
        if (q.empty()) {
            std::cout << -sum << std::endl;
            return 0;
        }
        q.push(x + y);
    }
    
    std::cout << sum << std::endl;
}
