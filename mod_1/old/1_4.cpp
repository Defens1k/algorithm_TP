#include <iostream>

int joseph (int n, int k) {
	if (n == 1) {
        return 0;
    }
	if (k == 1) {
        return n - 1;
    }
	if (k > n) {
        return (joseph (n-1, k) + k) % n;
    }
	int cnt = n / k;
	int res = joseph (n - cnt, k);
	res -= n % k;
	if (res < 0) {
        res += n;
    } else {
        res += res / (k - 1);
    }
	return res;
}

int main() {
    int n = 0;
    int k = 0;
    std::cin >> n >> k;
    std::cout << 1 + joseph(n, k) << std::endl;
}
