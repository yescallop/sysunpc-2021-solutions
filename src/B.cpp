#include <iostream>
#include <iomanip>

typedef unsigned int u32;
typedef unsigned long long u64;

int main() {
    u32 cnt;
    std::cin >> cnt;
    for (u32 i = 0; i < cnt; i++) {
        double a, b;
        std::cin >> a >> b;
        auto area = 3.1415926535897932384626 * (a * a + b * b) / 4.0 - a * b;
        std::cout << std::fixed << std::setprecision(6) << area << std::endl;
    }
    return 0;
}
