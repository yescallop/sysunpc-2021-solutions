#include <algorithm>
#include <iostream>
#include <vector>

typedef unsigned int u32;
typedef unsigned long long u64;

void go();

int main() {
    u32 cnt;
    std::cin >> cnt;

    std::vector<u64> vec = {1};
    int c2 = 0, c3 = 0, c5 = 0, c7 = 0, c11 = 0;

    for (u32 i = 0; i < cnt; i++) {
        u64 max;
        std::cin >> max;
        if (max < vec.back()) {
            auto it = std::upper_bound(vec.begin(), vec.end(), max) - 1;
            std::cout << *it << '\n';
            continue;
        }
        while (true) {
            u64 next = std::min({2 * vec[c2], 3 * vec[c3], 5 * vec[c5], 7 * vec[c7], 11 * vec[c11]});
            if (next > max) {
                break;
            }
            vec.push_back(next);
            if (next == 2 * vec[c2]) c2 += 1;
            if (next == 3 * vec[c3]) c3 += 1;
            if (next == 5 * vec[c5]) c5 += 1;
            if (next == 7 * vec[c7]) c7 += 1;
            if (next == 11 * vec[c11]) c11 += 1;
        }
        std::cout << vec.back() << '\n';
    }
}
