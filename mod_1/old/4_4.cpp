#include<iostream>
#include<queue>
#include<vector>

class N {
 public:
    int64_t value;
    int64_t index;
};

struct compare {
    bool operator()(const N & a, const N & b) {
        return a.value < b.value;
    }
};

int main() {
    int64_t n = 0;
    int64_t k = 0;
    std::cin >> n;
    int64_t * mass = new int64_t[n];
    std::priority_queue <N, std::vector<N>, compare> q;
    int64_t number = 0;
    for (int64_t i = 0; i < n; i++) {
        std::cin >> mass[i]; 
    }
    std::cin >> k;
    N num;
    for (int64_t i = 0; i < k; i++) {       //
        num.value = mass[i];                //  push first k elements in queue
        num.index = i;                      //
        q.push(num);                        //
    }                                       //
    std::cout << q.top().value << ' ';          // 

    for (int64_t i = 1; i <= n - k; i++) {
        num.value = mass[i + k - 1];
        num.index = i + k - 1;
        q.push(num);
        while(q.top().index < i) {
            q.pop();
        }
        std::cout << q.top().value << ' ';
    }
    std::cout << std::endl;
}
