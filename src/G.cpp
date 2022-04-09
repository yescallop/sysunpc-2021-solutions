#include <iostream>
#include <vector>

struct Node {
    int parent;
    size_t num;
    size_t edge;
    size_t controls = 0;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    std::vector<Node> nodes = {};

    for (int t = 0; t < T; t++) {
        size_t n;
        std::cin >> n;
        nodes.clear();
        nodes.reserve(n);

        for (size_t i = 0; i < n; i++) {
            Node node = {};
            std::cin >> node.num;
            nodes.push_back(node);
        }

        nodes[0].parent = -1;
        for (size_t i = 1; i < n; i++) {
            int parent;
            size_t edge;
            std::cin >> parent >> edge;
            nodes[i].parent = parent - 1;
            nodes[i].edge = edge;
        }

        for (size_t i = 0; i < n; i++) {
            Node *node = &nodes[i];
            size_t num = node->num, dist = 0;
            while (node->parent >= 0) {
                dist += node->edge;
                if (dist > num) {
                    break;
                }
                node = &nodes[node->parent];
                node->controls++;
            }
        }

        for (size_t i = 0; i < n; i++) {
            if (i != 0) {
                std::cout << ' ';
            }
            std::cout << nodes[i].controls;
        }
        std::cout << '\n';
    }
}
