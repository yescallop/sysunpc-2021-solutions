#include <algorithm>
#include <iostream>
#include <string>

typedef unsigned int u32;

void go();

int main() {
    u32 cnt;
    std::cin >> cnt;
    for (u32 i = 0; i < cnt; i++) {
        go();
    }
}

void go() {
    std::string s;
    std::cin >> s;

    if (std::any_of(s.begin(), s.end(), [](char ch) {
        return ch < '0' || ch > '9';
    })) {
        std::reverse(s.begin(), s.end());
        std::cout << s << '\n';
        return;
    }

    u32 carry = 0;
    std::for_each(s.rbegin(), s.rend(), [&](char &ch) {
        u32 n = (ch - '0') * 2 + carry;
        if (n >= 10) {
            n -= 10;
            carry = 1;
        } else {
            carry = 0;
        }
        ch = char(n + '0');
    });

    if (carry != 0) {
        std::cout << '1' << s << '\n';
    } else {
        auto it = std::find_if(s.begin(), s.end(), [](char ch) {
            return ch != '0';
        });
        u32 cnt = s.end() - it;
        if (cnt == 0) {
            std::cout << "0\n";
        } else {
            std::cout.write(&*it, cnt) << '\n';
        }
    }
}
