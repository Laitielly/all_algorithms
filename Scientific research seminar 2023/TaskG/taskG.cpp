#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int col = 0, row = 0;
    std::cin >> col >> row;

    std::vector<std::vector<std::pair<int, int>>> points(col);

    for (int i = 0; i < row; ++i) {
        int x_start, y_start, weight;
        std::cin >> x_start >> y_start >> weight;
        --x_start;
        --y_start;

        points[x_start].emplace_back(y_start, weight);
        points[y_start].emplace_back(x_start, weight);
    }

    const auto dist_max = static_cast<const int>(1e9 + 1);

    std::vector<int> mst_weights(col, dist_max);
    mst_weights[0] = 0;
    std::vector<bool> used(col, false);
    std::set<std::pair<int, int>> queue;
    queue.insert(std::make_pair(0, 0));

    while (!queue.empty()) {
        int vertex = queue.begin()->second;
        queue.erase(queue.begin());

        if (!used[vertex]) {
            used[vertex] = true;
            for (auto &to: points[vertex]) {
                if (to.second < mst_weights[to.first] && !used[to.first]) {
                    mst_weights[to.first] = to.second;
                    queue.insert(std::make_pair(to.second, to.first));
                }
            }
        }
    }

    std::cout << *std::max_element(mst_weights.begin(), mst_weights.end());

    return 0;
}
