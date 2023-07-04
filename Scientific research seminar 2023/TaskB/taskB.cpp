#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <string>

const int INF = 1e9 + 1;
int row, col;

struct vertex{
    short turn = -1;
    short dir = -1;
    short x = -1;
    short y = -1;
    int deep = INF;
};

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);

    int start_x, start_y, finish_x, finish_y;
    std::cin >> row >> col;
    std::vector<std::vector<char>> field(row, std::vector<char> (col));
    for (int i = 0; i < row; ++i) {
        std::string input_row;
        std::cin >> input_row;
        for (int j = 0; j < col; ++j) {
            field[i][j] = input_row[j];
        }
    }
    std::cin >> start_x >> start_y >> finish_x >> finish_y;
    start_x--;
    finish_x--;
    start_y--;
    finish_y--;

    std::vector<std::vector<std::vector<std::vector<vertex>>>> real_field(
        row, std::vector<std::vector<std::vector<vertex>>> (
            col, std::vector<std::vector<vertex>> (
                4, std::vector<vertex>(2))));

    std::queue<vertex> queue_of_vertexes;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 2; ++j) {
            vertex start_vertex;
            start_vertex.x = start_x;
            start_vertex.y = start_y;
            start_vertex.dir = i;
            start_vertex.turn = j;
            start_vertex.deep = 0;
            queue_of_vertexes.push(start_vertex);
        }
    }

    bool stop_flag = 0;
    vertex current_vertex;

    while (queue_of_vertexes.size() > 0) {
        current_vertex = queue_of_vertexes.front();
        if (current_vertex.x == finish_x && current_vertex.y == finish_y) {
            stop_flag = 1;
        }
        queue_of_vertexes.pop();
        int new_dir = current_vertex.dir;
        switch (new_dir%2) {
            case 0:
                if (current_vertex.x < row - 1 &&
                    real_field[current_vertex.x + 1][current_vertex.y]
                    [0][current_vertex.turn].deep > (current_vertex.deep + 1) &&
                    field[current_vertex.x + 1][current_vertex.y] != '#') {

                    vertex next_vert = current_vertex;
                    next_vert.x++;
                    next_vert.dir = 0;
                    next_vert.deep++;
                    real_field[next_vert.x][next_vert.y][0][next_vert.turn] = current_vertex;
                    real_field[next_vert.x][next_vert.y][0][next_vert.turn].deep += 1;
                    queue_of_vertexes.push(next_vert);
                }

                if (current_vertex.x > 0 &&
                    real_field[current_vertex.x - 1][current_vertex.y]
                    [2][current_vertex.turn].deep > (current_vertex.deep + 1) &&
                    field[current_vertex.x - 1][current_vertex.y] != '#') {

                    vertex next_vert = current_vertex;
                    next_vert.x--;
                    next_vert.dir = 2;
                    next_vert.deep++;
                    real_field[next_vert.x][next_vert.y][2][next_vert.turn] = current_vertex;
                    real_field[next_vert.x][next_vert.y][2][next_vert.turn].deep += 1;
                    queue_of_vertexes.push(next_vert);
                }

                break;

            case 1:
                if (current_vertex.y < col - 1 &&
                    real_field[current_vertex.x][current_vertex.y + 1][1]
                    [current_vertex.turn].deep > (current_vertex.deep + 1) &&
                    field[current_vertex.x][current_vertex.y + 1] != '#') {

                    vertex next_vert = current_vertex;
                    next_vert.y++;
                    next_vert.dir = 1;
                    next_vert.deep++;
                    real_field[next_vert.x][next_vert.y][1][next_vert.turn] = current_vertex;
                    real_field[next_vert.x][next_vert.y][1][next_vert.turn].deep += 1;
                    queue_of_vertexes.push(next_vert);
                }

                if (current_vertex.y > 0 &&
                    real_field[current_vertex.x][current_vertex.y - 1]
                    [3][current_vertex.turn].deep > (current_vertex.deep + 1) &&
                    field[current_vertex.x][current_vertex.y - 1] != '#') {

                    vertex next_vert = current_vertex;
                    next_vert.y--;
                    next_vert.dir = 3;
                    next_vert.deep++;
                    real_field[next_vert.x][next_vert.y][3][next_vert.turn] = current_vertex;
                    real_field[next_vert.x][next_vert.y][3][next_vert.turn].deep += 1;
                    queue_of_vertexes.push(next_vert);
                }
                break;
        }

        new_dir = (new_dir + (current_vertex.turn ? 1 : -1) + 4) % 4;
        vertex next_vert = current_vertex;
        switch (new_dir) {
            case 0: next_vert.x++; break;
            case 1: next_vert.y++; break;
            case 2: next_vert.x--; break;
            case 3: next_vert.y--; break;
        }
        next_vert.dir = new_dir;
        next_vert.turn = !current_vertex.turn;
        next_vert.deep++;
        if (next_vert.x >= 0 && next_vert.x < row && next_vert.y >= 0 && next_vert.y < col
            && real_field[next_vert.x][next_vert.y][next_vert.dir]
            [next_vert.turn].deep > next_vert.deep
            && field[next_vert.x][next_vert.y] != '#') {
            real_field[next_vert.x][next_vert.y][next_vert.dir][next_vert.turn] = current_vertex;
            real_field[next_vert.x][next_vert.y][next_vert.dir][next_vert.turn].deep += 1;
            queue_of_vertexes.push(next_vert);
        }
        if (stop_flag) {
            break;
        }
    }

    if (stop_flag) {
        vertex prev = current_vertex;
        std::vector<int> res (0);

        while (prev.x != start_x || prev.y != start_y) {
            prev = real_field[current_vertex.x][current_vertex.y]
            [current_vertex.dir][current_vertex.turn];
            res.push_back(prev.y);
            res.push_back(prev.x);
            current_vertex = prev;
        }
        std::cout << res.size()/2 << std::endl;
        for (int i = res.size()-1; i >= 0; i -= 2) {
            std::cout << res[i] + 1 << " " << res[i - 1] + 1 << std::endl;
        }
        std::cout << finish_x + 1 << " " << finish_y + 1;
    }
    else
        std::cout << -1;


    return 0;
}
