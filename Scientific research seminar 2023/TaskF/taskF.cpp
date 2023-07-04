#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <stack>

const int MAX = 2001;

std::vector<int> adj[MAX];
std::vector<int> adjInv[MAX];
bool visited[MAX];
bool visitedInv[MAX];
std::stack<int> stack;

int scc[MAX];

int counter = 1;

void dfsFirst(const int index)
{
    if (visited[index])
        return;

    visited[index] = 1;

    for (int i = 0; i < static_cast<int>(adj[index].size()); ++i) {
        dfsFirst(adj[index][i]);
    }

    stack.push(index);
}

void dfsSecond(const int index)
{
    if (visitedInv[index])
        return;

    visitedInv[index] = 1;

    for (int i = 0; i < static_cast<int>(adjInv[index].size()); ++i) {
        if (adjInv[index][i] > 0)
            dfsSecond(adjInv[index][i]);
    }

    scc[index] = counter;
}

void answer(const int participants, const int judges, std::vector<int> verdict_first,
            std::vector<int> verdict_second)
{
    for (int index = 0; index < judges; ++index) {

        if (verdict_first[index] > 0 && verdict_second[index] > 0) {
            adj[verdict_first[index] + participants].push_back(
                verdict_second[index]);
            adjInv[verdict_second[index]].push_back(
                verdict_first[index] + participants);
            adj[verdict_second[index] + participants].push_back(
                verdict_first[index]);
            adjInv[verdict_first[index]].push_back(
                verdict_second[index] + participants);
        }

        else if (verdict_first[index] > 0 && verdict_second[index] < 0) {
            adj[verdict_first[index] + participants].push_back(
                participants - verdict_second[index]);
            adjInv[participants - verdict_second[index]].push_back
            (verdict_first[index] + participants);
            adj[-verdict_second[index]].push_back(verdict_first[index]);
            adjInv[verdict_first[index]].push_back(-verdict_second[index]);
        }

        else if (verdict_first[index] < 0 && verdict_second[index] > 0) {
            adj[-verdict_first[index]].push_back(verdict_second[index]);
            adjInv[verdict_second[index]].push_back(-verdict_first[index]);
            adj[verdict_second[index] + participants].push_back(
                participants - verdict_first[index]);
            adjInv[participants - verdict_first[index]].push_back(
                verdict_second[index] + participants);
        }

        else
        {
            adj[-verdict_first[index]].push_back(
                participants - verdict_second[index]);
            adjInv[participants - verdict_second[index]].push_back(
                -verdict_first[index]);
            adj[-verdict_second[index]].push_back(
                participants - verdict_first[index]);
            adjInv[participants - verdict_first[index]].push_back(
                -verdict_second[index]);
        }
    }

    for (int i = 1; i <= 2 * participants; ++i) {
        if (!visited[i])
            dfsFirst(i);
    }

    while (!stack.empty())
    {
        int to = stack.top();
        stack.pop();

        if (!visitedInv[to])
        {
            dfsSecond(to);
            counter++;
        }
    }

    for (int i = 1; i <= participants; ++i) {
        if (scc[i] == scc[i + participants]) {
            std::cout << "no";
            return;
        }
    }

    std::cout << "yes";
    return;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);

    int participants, judges;
    std::cin >> participants >> judges;
    std::vector<int> verdict_first (judges + 1);
    std::vector<int> verdict_second (judges + 1);
    verdict_first[0] = 1;
    verdict_second[0] = 1;
    for (int i = 1; i <= judges; ++i) {
        std::cin >> verdict_first[i] >> verdict_second[i];
    }

    answer(participants, judges + 1, verdict_first, verdict_second);

    return 0;
}
