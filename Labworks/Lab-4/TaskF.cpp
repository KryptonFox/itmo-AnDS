#include <iostream>
#include <algorithm> // для std::lower_bound

int main() {
    int n;
    std::cin >> n;

    int64_t* a = new int64_t[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    int* dp = new int[n];
    int length = 0;      

    for (int i = 0; i < n; ++i) {
        int* pos = std::lower_bound(dp, dp + length, a[i]);

        *pos = a[i];

        if (pos == dp + length) {
            length++;
        }
    }

    std::cout << length << std::endl;

    delete[] a;
    delete[] dp;
}
