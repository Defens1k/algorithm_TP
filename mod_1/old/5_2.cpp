#include <iostream>
#include <ctime>

int64_t min (int64_t a, int64_t b) {
    return a < b ? a : b;
}

int64_t compare(int64_t a, int64_t b) {
    return a > b;
}

void merge(int64_t * arr, int64_t left, int64_t mid, int64_t right, int64_t(*cmp) (int64_t a, int64_t b)) {
    int64_t it1 = 0, it2 = 0;
    int64_t* res = new int64_t[right - left];

    while ((left + it1 < mid) && (mid + it2 < right)) {
        if (cmp(arr[left + it1], arr[mid + it2])) {
            res[it1 + it2] = arr[mid + it2];
            it2++;
        }
        else {
            res[it1 + it2] = arr[left + it1];
            it1++;
        }
    }

    while (left + it1 < mid) {
        res[it1 + it2] = arr[left + it1];
        it1++;
    }

    while (mid + it2 < right) {
        res[it1 + it2] = arr[mid + it2];
        it2++;
    }

    for (int64_t i = 0; i < it1 + it2; i++) {
        arr[left + i] = res[i];
    }
}

void mergeSort(int64_t * arr, int64_t left, int64_t right, int64_t(*cmp)(int64_t a, int64_t b)) {
    int64_t n = right - left;
    for (int64_t i = 1; i <= n; i *= 2) {
        for (int64_t j = 0; j < n - i; j += 2 * i) {
            merge(arr, left + j, left + j + i, min(left + j + 2 * i, right), cmp);
        }
    }
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

int64_t to_day(int64_t day, int64_t month, int64_t year) {
    
    return day + 35 * month + 14 * 35 * (year - 1900);
}

int main() {
    int64_t n = 0;
    std::cin >> n;
    int64_t * l = new int64_t[n];
    int64_t * r = new int64_t[n];
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

        l[i] = to_day(day_born, month_born, year_born + 18);
        r[i] = to_day(day_die, month_die, year_die);
    }
    mergeSort(l, 0, n, compare);
    mergeSort(r, 0, n, compare);
     
    int64_t iter_l = 0;  //  pointers to next positions
    int64_t iter_r = 0;  //
    int64_t prev_pos = 0;
    int64_t current_pos = 0;
    size_t sum_len = 0;
    int64_t current_layer = 0;
    int64_t max = -1;
    while (1) {
        if (iter_l >= n) {
            if (iter_r >= n) {
                std::cout << max << std::endl;
                return 0;
            }
            current_pos = r[iter_r];
            iter_r++;
            current_layer--;
            continue;
        }
        if (l[iter_l] < r[iter_r]) {  // open
            current_pos = l[iter_l];
            iter_l++;
            current_layer++;
            if (current_layer > max) {
                max = current_layer;
            }
            continue;
        }
        if (l[iter_l] > r[iter_r]) {  // close
            current_pos = r[iter_r];
            iter_r++;
            current_layer--;
            continue;
        }
        if (l[iter_l] == r[iter_r]) {  // close
            current_pos = r[iter_r];
            iter_r++;
            iter_l++;
            continue;
        }
        std::cout << "lose\n";
    }
}



