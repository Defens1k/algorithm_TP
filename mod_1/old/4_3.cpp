#include<iostream>
#include<algorithm>

int64_t n = 0;
int64_t sum = 0;

class Time {
 public:
    unsigned long int time;
    bool arrival;
};

bool compare (Time a, Time b) {
    return a.time < b.time;

}

int main() {
    std::cin >> n;
    Time * mass = new Time[2 * n];
    unsigned long int arrival, deperture;
    for (int64_t i = 0; i < n; i++) {       
        std::cin >> arrival >> deperture;
        mass[2 * i].time = arrival;
        mass[2 * i].arrival = true;
        mass[2 * i + 1].time = deperture + 1;
        mass[2 * i + 1].arrival = false;
    }
    std::sort(&mass[0], &mass[2 * n], compare);
    int64_t max = 0;
    int64_t current_trains = 0;
    for (int64_t i = 0; i < 2 * n; i++) {
        if (mass[i].arrival) {
            current_trains++;
        }
        else {
            current_trains--;
        }
        if (current_trains > max) {
            max = current_trains;
        }
    }
    std::cout << max << std::endl;
}
