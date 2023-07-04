#include <iostream>
#include<vector>
#include <utility>
#include <algorithm>


void dfs(const int &vertex, int &timer, std::vector<int> &min_vertex_time,
         std::vector<int> &timer_in, const std::vector<std::pair<int, int>> *vertexes,
         int &min_count, const int parent)
{
    ++timer;
    timer_in[vertex] = timer;
    min_vertex_time[vertex] = timer;

    for (int index = 0; index < static_cast<int>(vertexes[vertex].size()); ++index)
    {
        int to = vertexes[vertex][index].first;
        if (to == parent)  continue;

        if (timer_in[to])
            min_vertex_time[vertex] = std::min(min_vertex_time[vertex], timer_in[to]);

        else
        {
            dfs(to, timer, min_vertex_time, timer_in, vertexes, min_count, vertex);
            min_vertex_time[vertex] = std::min(min_vertex_time[vertex], min_vertex_time[to]);
            if (min_vertex_time[to] > timer_in[vertex] &&
                min_count > vertexes[vertex][index].second)
            {
                min_count = vertexes[vertex][index].second;
            }
        }
    }
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);

    int num_vertex = 0, num_edges = 0;
    std::cin >> num_vertex >> num_edges;

//    first - vertex, second - weight
    std::vector<std::pair<int, int>> vertexes[num_vertex];

    for (int i = 0; i < num_edges; ++i)
    {
        int first_ver = 0, second_ver = 0, weight = 0;
        std::cin >> first_ver >> second_ver >> weight;
        --first_ver;
        --second_ver;

        vertexes[first_ver].emplace_back(std::make_pair(second_ver, weight));
        vertexes[second_ver].emplace_back(std::make_pair(first_ver, weight));
    }

    int min_count = 1000000001;

    int timer = 0;
    std::vector<int> timer_in(num_vertex, 0);
    std::vector<int> min_vertex_time(num_vertex, 0);

    dfs(0, timer, min_vertex_time, timer_in, vertexes, min_count, -1);

    if (min_count == 1000000001) min_count = -1;
    std::cout << min_count;

    return 0;
}
