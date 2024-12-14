#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

vector<vector<string>> Map;
int w, h;

bool out_of_bounds(int x, int y) {
    return x < 0 || y < 0 || x >= w || y >= h;
}

string Id(int dx, int dy) {
    return to_string(dx + 1 + 2 * (dy + 1));
}

void Border(int x, int y, int dx, int dy, char c) {
    string iid = Id(dx, dy);
    int Dx = abs(dx) - 1;
    int Dy = abs(dy) - 1;

    int X = x + Dx, Y = y + Dy;
    while (!out_of_bounds(X, Y) && Map[Y][X].find(c) != string::npos) {
        if (!out_of_bounds(X + dx, Y + dy) &&
            (Map[Y + dy][X + dx].find(c) != string::npos || Map[Y + dy][X + dx] == "*")) {
            break;
        }
        Map[Y][X] += iid;
        X += Dx;
        Y += Dy;
    }

    X = x - Dx;
    Y = y - Dy;
    while (!out_of_bounds(X, Y) && Map[Y][X].find(c) != string::npos) {
        if (!out_of_bounds(X + dx, Y + dy) &&
            (Map[Y + dy][X + dx].find(c) != string::npos || Map[Y + dy][X + dx] == "*")) {
            break;
        }
        Map[Y][X] += iid;
        X -= Dx;
        Y -= Dy;
    }
}

pair<int, int> explore(int x, int y, char c) {
    string om = Map[y][x];
    Map[y][x] = "*";
    int a = 1, p = 0;

    vector<pair<int, int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    for (auto [dx, dy] : dirs) {
        int X = x + dx, Y = y + dy;
        if (out_of_bounds(X, Y)) {
            if (om.find(Id(dx, dy)) == string::npos) {
                Border(x, y, dx, dy, c);
                p++;
            }
        } else if (Map[Y][X].find(c) == string::npos && Map[Y][X] != "*") {
            if (om != "*" && om.find(Id(dx, dy)) == string::npos) {
                Border(x, y, dx, dy, c);
                p++;
            }
        }
    }

    for (auto [dx, dy] : dirs) {
        int X = x + dx, Y = y + dy;
        if (!out_of_bounds(X, Y) && Map[Y][X].find(c) != string::npos) {
            auto [da, dp] = explore(X, Y, c);
            a += da;
            p += dp;
        }
    }

    return {a, p};
}

int main() {
    ifstream file("./input.txt");
    vector<string> lines;
    string line;

    while (getline(file, line)) {
        lines.push_back(line);
    }

    file.close();

    for (const auto& l : lines) {
        vector<string> row;
        for (char c : l) {
            row.push_back(string(1, c));
        }
        Map.push_back(row);
    }

    w = Map[0].size();
    h = Map.size();

    int res = 0;

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            if (Map[y][x] != "#") {
                auto [a, p] = explore(x, y, Map[y][x][0]);
                res += a * p;

                for (auto& row : Map) {
                    for (auto& cell : row) {
                        if (cell == "*") {
                            cell = "#";
                        }
                    }
                }
            }
        }
    }

    cout << "fences cost: " << res << endl;

    return 0;
}
