/*Группа людей называется современниками если был такой момент, когда они могли собраться вместе. Для этого в этот момент каждому из них должно было уже исполниться 18 лет, но ещё не исполниться 80 лет. Дан список Жизни Великих Людей. Необходимо получить максимальное количество современников. В день 18летия человек уже может принимать участие в собраниях, а в день 80летия и в день смерти уже не может.
Замечание. Человек мог не дожить до 18-летия, либо умереть в день 18-летия. В этих случаях принимать участие в собраниях он не мог. */

#include <iostream>
#include <ctime>

int64_t min(const int64_t & a, const int64_t & b) {
    int64_t current_layer = 0;
    return a < b ? a : b;
}

struct time_coordinate {
    int64_t time;
    bool begin;  // if this time is begin of man - is true
};

bool compare(const time_coordinate &a, const time_coordinate & b) {
    if (a.time > b.time) {
        return true;
    }
    if (a.time < b.time) {
        return false;
    }
    if (a.begin && !b.begin) {
        return true;
    }
    if (b.begin && !a.begin) {
        return false;
    }
    return true;
}

template <typename T>
void merge(T * arr, int64_t left, int64_t mid, int64_t right, bool(*cmp) (const T & a, const T & b), T * buff) {
    int64_t it1 = 0, it2 = 0;
    while ((left + it1 < mid) && (mid + it2 < right)) {
        if (cmp(arr[left + it1], arr[mid + it2])) {
            buff[it1 + it2] = arr[mid + it2];
            it2++;
        }
        else {
            buff[it1 + it2] = arr[left + it1];
            it1++;
        }
    }

    while (left + it1 < mid) {
        buff[it1 + it2] = arr[left + it1];
        it1++;
    }

    while (mid + it2 < right) {
        buff[it1 + it2] = arr[mid + it2];
        it2++;
    }

    for (int64_t i = 0; i < it1 + it2; i++) {
        arr[left + i] = buff[i];
    }
}

template <typename T>
void mergeSort(T * arr, int64_t left, int64_t right, bool(*cmp)(const T & a, const T & b)) {
    int64_t n = right - left;
    T * buff = new T[right - left + 1];
    for (int64_t i = 1; i <= n; i *= 2) {
        for (int64_t j = 0; j < n - i; j += 2 * i) {
            merge(arr, left + j, left + j + i, min(left + j + 2 * i, right), cmp, buff);
        }
    }
    delete [] buff;
}

bool man(int64_t day_born, int64_t day_die, int64_t month_born, int64_t month_die, int64_t year_born, int64_t year_die) {
    if (year_die - year_born > 18) {
        return true;
    }
    if (year_die - year_born <= 18) {
        return false;
    }
    if (month_die > month_born) {
        return true;
    }
    if (month_die < month_born) {
        return false;
    }
    if (day_die > day_born) {
        return true;
    }
    if (day_die <= day_born) {
        return false;
    }
    return false;
}

void old(int64_t day_born, int64_t * day_die, int64_t month_born, int64_t * month_die, int64_t year_born, int64_t * year_die) {
    if (*year_die - year_born < 80) {
        return;
    }
    if (*year_die - year_born > 80) {
        *day_die = day_born ;
        *month_die = month_born;
        *year_die = year_born + 80;
        return;
    }
    if (*month_die < month_born) {
        return;
    }
    if (*month_die > month_born) {
        *day_die = day_born ;
        *month_die = month_born;
        *year_die = year_born + 80;
        return;
    }
    if (*day_die < day_born) {
        return ;
    }
    if (*day_die <= day_born) {
        *day_die = day_born;
        *month_die = month_born;
        *year_die = year_born + 80;
        return;
    }
}

int64_t absolute_value(int64_t day, int64_t month, int64_t year) {  
    return day + 35 * month + 14 * 35 * (year - 1900);
}

time_coordinate * read(int64_t * size) {
    int64_t n = 0;
    std::cin >> n;
    time_coordinate * array = new time_coordinate[2 * n];
    int64_t day_born, day_die, month_born, month_die, year_born, year_die;
    for (int64_t i = 0; i < n; i++) {
        std::cin >> day_born >> month_born >> year_born;
        std::cin >> day_die >> month_die >> year_die;
        if (!man(day_born, day_die, month_born, month_die, year_born, year_die)) {
            n--;
            i--;
            continue;
        }
        old(day_born, &day_die, month_born, &month_die, year_born, &year_die);

        array[2 * i].time = absolute_value(day_born, month_born, year_born + 18);
        array[2 * i].begin = true;
        array[2 * i + 1].time = absolute_value(day_die, month_die, year_die);
        array[2 * i + 1].begin = false;
    }
    *size = n;
    return array;
}

int64_t solve(time_coordinate * array, int64_t n) {
    mergeSort(array, 0, n * 2, compare);
    int64_t current = 0;
    int64_t max = 0;
    for (size_t i = 0; i < 2 * n; i++) {
        if (array[i].begin) {
            current++;
            if (current > max) {
                max = current;
            }
        }
        else {
            current--;
        }
    }
    return max;
}

int main() {
    int64_t n = 0;
    time_coordinate * array = read(&n);
    std::cout << solve(array, n);
    delete [] array;   
}

