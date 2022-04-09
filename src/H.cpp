#include <iostream>
#include <vector>

struct Tree {
    size_t pos;
    size_t height;
    size_t flags;
};

// flags
// 000: can't fell (0)
// 001: possibly fell left only (1)
// 010: possibly fell right only (2)
// 011: possibly fell both ways (3)
// 101: must fell right
// 110: must fell left
//
// starts with 2 or 0, ends with 1 or 0
//
// prev->cur (regarding cur)
// 0->0: can't fell
// 0->1: N/A
// 0->2: fell right
// 0->3: N/A
//
// 1->0: can't fell
// 1->1: N/A
// 1->2: fell right
// 1->3: N/A
//
// 2->0: N/A
// 2->1: can't fell
// 2->2: N/A
// 2->3: fell right
//
// 3->0: N/A
// 3->1: can't fell
// 3->2: N/A
// 3->3: fell right
//
// example: 0,0,0,2,3,3,3,1,0,2,1,2,3,1

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    std::vector<Tree> trees = {};

    for (int t = 0; t < T; t++) {
        size_t n;
        std::cin >> n;
        if (n <= 2) {
            std::cout << n << '\n';
            continue;
        }
        trees.clear();
        trees.reserve(n);

        Tree first, cur;
        std::cin >> first.pos >> first.height;
        first.flags = 0b110;
        trees.push_back(first);
        Tree *prev = &trees.back();

        for (size_t i = 1; i < n; i++) {
            std::cin >> cur.pos >> cur.height;
            auto gap = cur.pos - prev->pos;

            bool prev_fell_right = false;

            if (prev->flags & 0b100) {
                // prev must have felled left
                if (gap > cur.height) {
                    cur.flags = 0b110;
                } else {
                    cur.flags = 0b000;
                }
            } else if (gap > cur.height + prev->height) {
                // prev must fell right & cur must fell left
                cur.flags = 0b110;
                prev_fell_right = true;
            } else if (gap > cur.height && gap <= prev->height) {
                // cur must fell left
                cur.flags = 0b110;
            } else if (gap <= cur.height && gap > prev->height) {
                // prev must fell right
                cur.flags = 0b000;
                prev_fell_right = true;
            } else if (gap <= cur.height && gap <= prev->height) {
                cur.flags = 0b000;
            } else {
                // prev possibly fells right
                prev->flags |= 0b010;
                // cur possibly fells left
                cur.flags = 0b001;
            }

            trees.push_back(cur);

            if (i == n - 1) {
                i = n;
                prev = &trees.back();
                prev_fell_right = true;
            }

            if (prev_fell_right) {
                prev->flags = 0b101;
                size_t prev_i = i - 1;
                while (--prev_i) {
                    size_t pos = prev->pos;
                    size_t gap_back = pos - (--prev)->pos;
                    if (gap_back <= prev->height) {
                        break;
                    }
                    prev->flags = 0b101;
                }
            }

            prev = &trees.back();
        }

        size_t sum = 0;
        for (const Tree &tree: trees) {
            size_t flags = tree.flags;
            sum += (flags & 1) | (flags >> 2);
        }
        std::cout << sum << '\n';
    }
}
