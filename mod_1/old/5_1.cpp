#include <iostream>
#include <algorithm>

int64_t sum = 0; 

class guest {
 public:
    int to_show(int64_t time_show);
    
    int64_t arrival;
    int64_t departure;
    int count_see = 0;
};

guest * mass = nullptr;
int64_t n = 0;

int guest::to_show(int64_t time_show) {
    if (time_show > departure) {
        return 1;
    }
    if (time_show < arrival) {
        return 0;
    }
    count_see++;
    return 1;

}

bool cmp(guest a, guest b) {
    if (a.departure == b.departure) {
        return a.arrival > b.arrival;
    }
    return a.departure < b.departure;
}

void see(int64_t left, int64_t time) {
    for (int64_t i = left; i < n; i++) {
        if (!mass[i].to_show(time)) {
            return;
        }
    }
}

int main() {
    std::cin >> n;
    mass = new guest[n];
    int64_t arrival, departure;
    for (int i = 0; i < n; i++) {
        std::cin >> arrival >> departure;
        mass[i].arrival = arrival;
        mass[i].departure = departure;
    }
    std::sort(&mass[0], &mass[n], cmp);
    for (int64_t i = 0; i < n; i++) {
        if (mass[i].count_see >= 2) {
            continue;
        }
        if (mass[i].count_see == 0) {
            see(i, mass[i].departure - 1);
            sum++;
        }
        see(i, mass[i].departure);
        sum++;
    }
    std::cout << sum << std::endl;
}
