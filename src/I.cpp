#include <iostream>

typedef unsigned int u32;

u32 isqrt(u32 s) {
    u32 x0 = s / 2;
    if (x0 != 0) {
        u32 x1 = (x0 + s / x0) / 2;
        while (x1 < x0) {
            x0 = x1;
            x1 = (x0 + s / x0) / 2;
        }
        return x0;
    } else {
        return s;
    }
}

int main() {
    u32 cnt;
    std::cin >> cnt;

    for (u32 i = 0; i < cnt; i++) {
        u32 x;
        std::cin >> x;

        if (x == 0) {
            std::cout << "1 1\n";
            continue;
        }

        u32 n = isqrt(x) + 1;
        u32 n_sqr = n * n;
        while (true) {
            for (u32 m = 2; m <= n; m++) {
                u32 q = n / m;
                u32 res = n_sqr - q * q;
                if (res == x) {
                    std::cout << n << ' ' << m << '\n';
                    goto next;
                } else if (res > x) {
                    if (m == 2) {
                        goto nope;
                    }
                    break;
                }
            }
            n_sqr += (n << 1) | 1;
            n++;
        }
        nope:
        std::cout << "-1\n";
        next:;
    }
}
