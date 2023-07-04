#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <set>
#include <iomanip>
#include <algorithm>


double distance(int x_start, int y_start, int x_finish, int y_finish) {
    long long int first_dist = std::pow((x_start - x_finish), 2);
    long long int second_dist = std::pow((y_start - y_finish), 2);

    return std::sqrt((first_dist + second_dist));
}


int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int agents = 0;
    std::cin >> agents;

    std::vector<std::pair<int, int>> points;

    for (int i = 0; i < agents; ++i) {
        int x_start, y_start;
        std::cin >> x_start >> y_start;

        points.emplace_back(x_start, y_start);
    }

    const int kMax = 1002;
    std::vector<std::vector<std::pair<int, double>>> full_graph(kMax);

    for (int i = 0; i < agents; ++i) {
        auto first_point = points[i];

        for (int j = i + 1; j < agents; ++j) {
            auto second_point = points[j];
            auto weight = distance(first_point.first, first_point.second,
                                   second_point.first, second_point.second);

            full_graph[i].emplace_back(j, weight);
            full_graph[j].emplace_back(i, weight);
        }
    }

//    for (int i = 0; i < agents; ++i) {
//        std::cout << i << ':' << std::endl;
//        for (auto &x: full_graph[i]) {
//            std::cout << x.first << ' ' << x.second << std::endl;
//        }
//
//        std::cout << std::endl;
//    }


    const auto dist_max = static_cast<const double>(4e9 + 1);

    std::vector<double> mst_weights(agents, dist_max);
    mst_weights[0] = 0;
    std::vector<bool> used(agents, false);
    std::set<std::pair<double, int>> queue;
    queue.insert(std::make_pair(0, 0));

    while (!queue.empty()) {
        int vertex = queue.begin()->second;
        queue.erase(queue.begin());

        if (!used[vertex]) {
            used[vertex] = true;
            for (auto &to: full_graph[vertex]) {
                if (to.second < mst_weights[to.first] && !used[to.first]) {
                    mst_weights[to.first] = to.second;
                    queue.insert(std::make_pair(to.second, to.first));
                }
            }
        }
    }

    std::cout << std::setprecision(10) << std::fixed <<
    *std::max_element(mst_weights.begin(), mst_weights.end());

    return 0;
}
