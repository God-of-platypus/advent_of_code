#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <algorithm>
#include <stack>

using namespace std;

// Movement mappings
unordered_map<char, pair<int, int>> movs = {
    {'>', {1, 0}},
    {'v', {0, 1}},
    {'<', {-1, 0}},
    {'^', {0, -1}}
};

unordered_map<char, int> DD = {
    {'[', 1},
    {']', -1}
};

unordered_map<char, string> conv = {
    {'.', ".."},
    {'#', "##"},
    {'O', "[]"},
    {'@', "@."}
};

bool can_move(vector<tuple<int, int, char>> &s, vector<string> &grid, int x, int y, int dy) {
    char c = grid[y][x];
    if (c == '#') {
        return false;
    }

    if (c == '[' || c == ']') {
        s.emplace_back(x, y, c);
        return can_move(s, grid, x, y + dy, dy) && can_move(s, grid, x + DD[c], y + dy, dy);
    }

    return c == '.';
}

bool move_robot2(vector<string> &grid, int x, int y, pair<int, int> d) {
    int dx = d.first, dy = d.second;

    // Vertical movement
    if (dy != 0) {
        vector<tuple<int, int, char>> s;
        if (can_move(s, grid, x, y, dy)) {
            sort(s.begin(), s.end(), [&](auto &a, auto &b) { return get<1>(a) < get<1>(b); });
            if (dy == 1) reverse(s.begin(), s.end());

            for (auto &[sx, sy, c] : s) {
                grid[sy][sx] = '.';
                grid[sy][sx + DD[c]] = '.';

                if (c == '[') {
                    grid[sy + dy][sx] = '[';
                    grid[sy + dy][sx + 1] = ']';
                } else {
                    grid[sy + dy][sx - 1] = '[';
                    grid[sy + dy][sx] = ']';
                }
            }
            return true;
        }
        return false;
    }

    // Horizontal movement
    vector<pair<int, int>> s;
    while (grid[y][x] == '[' || grid[y][x] == ']') {
        if (grid[y][x] == '[') {
            s.emplace_back(x, y);
        }
        x += dx;
        y += dy;
    }
    sort(s.begin(), s.end(), [&](auto &a, auto &b) { return a.first < b.first; });
    if (dx == 1) reverse(s.begin(), s.end());

    if (grid[y][x] == '#') {
        return false;
    }

    for (auto &[sx, sy] : s) {
        grid[sy][sx] = '.';
        grid[sy][sx + 1] = '.';
        grid[sy][sx + dx + 1] = ']';
        grid[sy][sx + dx] = '[';
    }

    return true;
}

bool move_robot1(vector<string> &grid, int x, int y, pair<int, int> d) {
    int dx = d.first, dy = d.second;
    int sx = x, sy = y;

    while (grid[y][x] == 'O') {
        x += dx;
        y += dy;
    }

    if (grid[y][x] == '#') {
        return false;
    }

    grid[y][x] = 'O';
    grid[sy][sx] = '.';

    return true;
}

int solve(int x, int y, vector<string> grid, const string &order) {
    for (char c : order) {
        auto [dx, dy] = movs[c];
        int xx = x + dx, yy = y + dy;

        if (grid[yy][xx] == '#') {
            continue;
        }

        bool move = true;
        if (grid[yy][xx] == '[' || grid[yy][xx] == ']') {
            move = move_robot2(grid, xx, yy, {dx, dy});
        }

        if (grid[yy][xx] == 'O') {
            move = move_robot1(grid, xx, yy, {dx, dy});
        }

        if (move) {
            grid[y][x] = '.';
            x = xx;
            y = yy;
            grid[y][x] = '@';
        }
    }

    int acc = 0;
    for (size_t y = 1; y < grid.size() - 1; ++y) {
        for (size_t x = 1; x < grid[y].size() - 1; ++x) {
            if (grid[y][x] == '[' || grid[y][x] == 'O') {
                acc += 100 * y + x;
            }
        }
    }

    return acc;
}

pair<int, int> findGrid(const vector<string> &grid, char target) {
    for (size_t y = 0; y < grid.size(); ++y) {
        for (size_t x = 0; x < grid[y].size(); ++x) {
            if (grid[y][x] == target) {
                return {x, y};
            }
        }
    }
    return {-1, -1};
}

int main() {
    ifstream file("input.txt");
    if (!file) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    string lines((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    auto pos = lines.find("\n\n");
    string grids = lines.substr(0, pos);
    string order = lines.substr(pos + 2);
    order.erase(remove(order.begin(), order.end(), '\n'), order.end());

    vector<string> grid;
    istringstream gridStream(grids);
    string line;
    while (getline(gridStream, line)) {
        grid.push_back(line);
    }

    auto [x, y] = findGrid(grid, '@');
    cout << "Part1: " << solve(x, y, grid, order) << endl;

    vector<string> expandedGrid;
    for (const auto &row : grid) {
        string expandedRow;
        for (char c : row) {
            expandedRow += conv[c];
        }
        expandedGrid.push_back(expandedRow);
    }

    tie(x, y) = findGrid(expandedGrid, '@');
    cout << "Part2: " << solve(x, y, expandedGrid, order) << endl;

    return 0;
}
