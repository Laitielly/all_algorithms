#include <iostream>
#include <vector>
#include <utility>
#include <stack>
#include <algorithm>

const int kMax = 50001;
int maximum = 1;

std::vector<int> adj[kMax];
std::vector<int> adj_inv[kMax];
bool visited[kMax];
bool visited_inv[kMax];
std::stack<int> stack;

int counter = 1;

void DfsFirst(const int index)
{
    visited[index] = 1;

    for (int i = 0; i < static_cast<int>(adj[index].size()); ++i) {
        if (!visited[adj[index][i]]) {
            DfsFirst(adj[index][i]);
        }
    }

    stack.push(index);
}

void DfsSecond(const int index, std::vector<int> &scc)
{
    visited_inv[index] = 1;
    scc.push_back(index);

    for (int i = 0; i < static_cast<int>(adj_inv[index].size()); ++i) {
        if (!visited_inv[adj_inv[index][i]]) {
            DfsSecond(adj_inv[index][i], scc);
        }
    }
}

void FindMaximum(std::vector<int> &scc, int participants) {

    if (scc.empty()) {
        return;
    }
    for (auto &vertex: scc) {
        for (auto &to: adj_inv[vertex]) {
            if (!(std::find(scc.begin(), scc.end(), static_cast<int>(to)) != scc.end())) {
                return;
            }
        }
    }

    int poss_max = participants - scc.size() + 1;
    maximum = (maximum < poss_max) ? poss_max:maximum;
}

void Answer(const int participants, const int judges) {
    for (int i = 0; i < participants; ++i) {
        if (!visited[i]) {
            DfsFirst(i);
        }
    }

    while (!stack.empty()) {
        int to = stack.top();
        stack.pop();

        if (!visited_inv[to]) {
            std::vector<int> scc;
            DfsSecond(to, scc);
            FindMaximum(scc, participants);
        }
    }

    std::cout << maximum;
}


int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int workers, games;
    std::cin >> workers >> games;

    for (int iteration = 0; iteration < games; ++iteration) {
        int first_ver = 0, second_ver = 0, weight = 0;
        std::cin >> first_ver >> second_ver >> weight;
        --first_ver;
        --second_ver;

        if (weight == 3) {
            continue;
        }

        if (weight == 1) {
            adj[first_ver].emplace_back(second_ver);
            adj_inv[second_ver].emplace_back(first_ver);
            continue;
        }

        adj[second_ver].emplace_back(first_ver);
        adj_inv[first_ver].emplace_back(second_ver);
    }


    Answer(workers, games);

    return 0;
}
