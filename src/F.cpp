#include <iostream>

typedef unsigned int u32;

void manip(u32 &target, u32 n) {
    if (n != 0) {
        manip(target, n - 1);
    }
    target ^= 1 << n;
    std::cout << target << '\n';
    if (n != 0) {
        manip(target, n - 1);
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);

    u32 n;
    std::cin >> n;

    u32 target = 0;
    std::cout << target << '\n';
    manip(target, n - 1);
}
