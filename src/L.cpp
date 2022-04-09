#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

typedef unsigned int u32;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int len, M;
    std::cin >> len >> M;
    std::string s = {};
    s.reserve(len);
    std::cin >> s;
    std::vector<u32> cnt_vec = {};
    s.reserve(len * 2 - 1);

    for (int i = 0; i < len * 2 - 1; i++) {
        int l = i >> 1;
        int r = l + (i & 1);

        u32 cnt = 0;
        while (l >= 0 && r < len && s[l] == s[r]) {
            cnt++;
            l--;
            r++;
        }
        cnt_vec.push_back(cnt);
    }

    for (u32 m = 0; m < M; m++) {
        u32 start, end;
        std::cin >> start >> end;
        start--;
        u32 sub_len = end - start;
        start *= 2;

        u32 cnt = 0;
        for (u32 i = 0; i < sub_len * 2 - 1; i++) {
            u32 l = i >> 1;
            u32 r = l + (i & 1);
            cnt += std::min({cnt_vec[start + i], l + 1, sub_len - r});
        }
        std::cout << cnt << '\n';
    }
}
