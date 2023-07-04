#include <iostream>
#include <vector>
#include <utility>
#include <queue>

int find_way(const int &in_vertex, const int &out_vertex,
             const std::vector<std::vector<std::pair<int, int>>> &vertexes, const int &num_vertex) {
    int weights = 3;
    std::queue<int> the_way[weights];
    std::vector<bool> used(num_vertex, false);
    std::vector<int> distance(num_vertex, 20000);

    the_way[0].push(in_vertex);
    int index = 0;
    used[in_vertex] = true;
    distance[in_vertex] = 0;

    while (!(the_way[0].empty() & the_way[1].empty() & the_way[2].empty())) {
        while (!(the_way[index].empty())) {
            int now = the_way[index].front();
            the_way[index].pop();

            if (now == out_vertex) {
                return distance[out_vertex];
            }

            used[now] = true;

            for (auto &to: vertexes[now]) {
                if (!used[to.first]) {
                    if (distance[to.first] > distance[now] + to.second) {
                        distance[to.first] = distance[now] + to.second;
                        the_way[(to.second + index) % 3].push(to.first);
                    }
                }
            }
        }
        index = (index + 1) % 3;
    }

    return -1;
}

int main() {
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);

    int num_vertex = 0, num_edges = 0;
    std::cin >> num_vertex >> num_edges;

//    first - vertex, second - weight
    std::vector<std::vector<std::pair<int, int>>> vertexes(num_vertex);

    for (int i = 0; i < num_edges; ++i) {
        int first_ver = 0, second_ver = 0, weight = 0;
        std::cin >> first_ver >> second_ver >> weight;
        --first_ver;
        --second_ver;

        vertexes[first_ver].emplace_back(std::make_pair(second_ver, weight));
    }

    int request = 0;
    std::cin >> request;

    for (int i = 0; i < request; ++i) {
        int in_vertex = 0, out_vertex = 0;
        std::cin >> in_vertex >> out_vertex;
        --in_vertex;
        --out_vertex;

        std::cout << find_way(in_vertex, out_vertex, vertexes, num_vertex) << std::endl;
    }

    return 0;
}
