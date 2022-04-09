#include <iostream>
#include <array>
#include <vector>

typedef unsigned int u32;
typedef unsigned long long u64;

struct Node {
    Node *next = nullptr;
    Node *prev = nullptr;
    u32 digit = 0;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::array<std::vector<Node *>, 10> digit_nodes = {};
    std::vector<Node *> nodes = {};
    std::vector<u32> to = {};

    u32 T;
    std::cin >> T;

    for (u32 t = 0; t < T; t++) {
        int ch;
        while ((ch = std::cin.peek()) < '0' || ch > '9') {
            std::cin.ignore();
        }
        Node *head = new Node{nullptr, nullptr};
        while ((ch = std::cin.get()) >= '0' && ch <= '9') {
            u32 digit = ch - '0';
            Node *cur = new Node{head, nullptr, digit};
            digit_nodes[digit].emplace_back(cur);

            head->prev = cur;
            head = cur;
        }
        Node *dummy = new Node{head};
        head->prev = dummy;

        u32 cnt;
        std::cin >> cnt;

        for (u32 n = 0; n < cnt; n++) {
            while ((ch = std::cin.peek()) < '0' || ch > '9') {
                std::cin.ignore();
            }
            u32 from = std::cin.get() - '0';

            while (((ch = std::cin.peek()) < '0' || ch > '9') && ch != '\n' && ch != '\r') {
                std::cin.ignore();
            }

            while ((ch = std::cin.get()) >= '0' && ch <= '9') {
                u32 digit = ch - '0';
                to.emplace_back(digit);
            }

            nodes.swap(digit_nodes[from]);
            for (Node *node: nodes) {
                Node *prev = node->prev, *next = node->next;
                for (u32 digit: to) {
                    Node *cur = new Node{next, nullptr, digit};
                    digit_nodes[digit].emplace_back(cur);

                    next->prev = cur;
                    next = cur;
                }
                prev->next = next;
                next->prev = prev;
                delete node;
            }
            to.clear();
            nodes.clear();
        }
        head = dummy->next;

        u64 res = 0;
        u64 mod = 1;
        while (head->next != nullptr) {
            res = (res + u64(head->digit) * mod) % 1000000007;
            mod = (mod * 10) % 1000000007;
            head = head->next;
        }
        std::cout << res << '\n';

        for (auto &vec: digit_nodes) {
            for (Node *node: vec) {
                delete node;
            }
            vec.clear();
        }
    }
}
