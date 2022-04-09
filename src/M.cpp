#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <deque>

typedef unsigned int u32;
typedef unsigned long long u64;

class obs_map {
    std::unordered_map<u32, std::vector<u32>> inner = {};
public:
    void emplace(u32 k, u32 v) {
        auto const &pair = inner.try_emplace(k);
        auto &obs = pair.first->second;
        obs.emplace_back(v);
    }

    void clear() {
        inner.clear();
    }

    void sort() {
        for (auto &pair: inner) {
            auto &obs = pair.second;
            std::sort(obs.begin(), obs.end());
        }
    }

    std::pair<u32, u32> next(u32 k, u32 v, u32 v_bound) {
        auto const res = inner.find(k);
        if (res == inner.end()) {
            return {0, v_bound - 1};
        }
        auto const &obs = res->second;
        auto next = std::upper_bound(obs.begin(), obs.end(), v);
        u32 r = next != obs.end() ? (*next - 1) : (v_bound - 1);
        u32 l = next != obs.begin() ? (*(next - 1) + 1) : 0;
        return {l, r};
    }
};

struct State {
    u32 x;
    u32 y;
    int moves;

    State(u32 x, u32 y, int moves) {
        this->x = x;
        this->y = y;
        this->moves = moves;
    }
};

u64 zip(u32 x, u32 y) {
    return (u64(y) << 32) | u64(x);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    u32 T;
    std::cin >> T;

    obs_map obs_x2y = {}, obs_y2x = {};
    std::deque<State> open = {};
    std::unordered_set<u64> closed = {};

    for (u32 t = 0; t < T; t++) {
        obs_x2y.clear();
        obs_y2x.clear();
        open.clear();
        closed.clear();

        u32 N, M, K, X_S, Y_S, X_T, Y_T;
        std::cin >> N >> M >> K >> X_S >> Y_S >> X_T >> Y_T;
        X_S--;
        Y_S--;
        X_T--;
        Y_T--;

        for (u32 k = 0; k < K; k++) {
            u32 x, y;
            std::cin >> x >> y;
            x--;
            y--;
            obs_x2y.emplace(x, y);
            obs_y2x.emplace(y, x);
        }
        obs_x2y.sort();
        obs_y2x.sort();

        closed.emplace(zip(X_S, Y_S));
        open.emplace_back(X_S, Y_S, 0);

        int min_moves = -1;
        while (!open.empty()) {
            State s = open.front();
            open.pop_front();
            if (s.x == X_T && s.y == Y_T) {
                min_moves = s.moves;
                break;
            }
            int moves = s.moves + 1;
            auto nx = obs_y2x.next(s.y, s.x, N);
            if (closed.emplace(zip(nx.first, s.y)).second) {
                open.emplace_back(nx.first, s.y, moves);
            }
            if (closed.emplace(zip(nx.second, s.y)).second) {
                open.emplace_back(nx.second, s.y, moves);
            }
            auto ny = obs_x2y.next(s.x, s.y, M);
            if (closed.emplace(zip(s.x, ny.first)).second) {
                open.emplace_back(s.x, ny.first, moves);
            }
            if (closed.emplace(zip(s.x, ny.second)).second) {
                open.emplace_back(s.x, ny.second, moves);
            }
        }
        std::cout << min_moves << '\n';
    }
}
