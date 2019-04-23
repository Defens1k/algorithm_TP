#include<iostream>
#include<queue>

int main() {
    int64_t n = 0;
    int64_t k = 0;
    std::cin >> n;
    std::priority_queue <int64_t> q;

    int64_t x(0);
    for (int64_t i = 0; i < n; i++) {

        std::cin >> x;
        q.push(x);
    }

    std::cin >> k;
    int64_t * mass = new int64_t[n + 1];
    int64_t current_mass = 0;
    int hod = 0;
    int64_t i = 0;
    while (!q.empty()) {
        i = 0;
        current_mass = 0;
        while(!q.empty()) {
            if (current_mass + q.top() <= k) {
                mass[i] = q.top();
                current_mass += q.top();
                i++;
                q.pop();
            } else {
                break;
            }
        }
        for (int64_t j = 0; j <= i; j++) {
            if (mass[j] < 2) {
                continue;
            }
            q.push(mass[j] / 2);
        }
        hod++;
    }    
    std::cout << hod << std::endl;
}
