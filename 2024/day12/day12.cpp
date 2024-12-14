#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <set>
#include <utility>
#include <string>

using namespace std;

typedef pair<int, int> Cell;

vector<Cell> get_neighbors(int x, int y, int rows, int cols) {
    vector<Cell> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    vector<Cell> neighbors;
    for (auto [dx, dy] : directions) {
        int nx = x + dx;
        int ny = y + dy;
        if (nx >= 0 && nx < rows && ny >= 0 && ny < cols) {
            neighbors.emplace_back(nx, ny);
        }
    }
    return neighbors;
}

pair<int, int> calculate_area_and_perimeter(
    const vector<string> &grid, int start_x, int start_y, char plant_type, set<Cell> &visited) {

    queue<Cell> q;
    q.push({start_x, start_y});
    visited.insert({start_x, start_y});

    int area = 0;
    int perimeter = 0;

    int rows = grid.size();
    int cols = grid[0].size();

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        area++;

        for (auto [nx, ny] : get_neighbors(x, y, rows, cols)) {
            if (grid[nx][ny] == plant_type) {
                if (!visited.count({nx, ny})) {
                    visited.insert({nx, ny});
                    q.push({nx, ny});
                }
            } else {
                perimeter++;
            }
        }

        for (auto [dx, dy] : vector<Cell>{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}) {
            if (!(x + dx >= 0 && x + dx < rows && y + dy >= 0 && y + dy < cols)) {
                perimeter++;
            }
        }
    }

    return {area, perimeter};
}

int calculate_total_price(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file." << endl;
        return -1;
    }

    vector<string> grid;
    string line;
    while (getline(file, line)) {
        grid.push_back(line);
    }
    file.close();

    int rows = grid.size();
    int cols = grid[0].size();

    set<Cell> visited;
    int total_price = 0;

    for (int x = 0; x < rows; ++x) {
        for (int y = 0; y < cols; ++y) {
            if (!visited.count({x, y})) {
                char plant_type = grid[x][y];
                auto [area, perimeter] = calculate_area_and_perimeter(grid, x, y, plant_type, visited);
                total_price += area * perimeter;
            }
        }
    }

    return total_price;
}

int main() {
    string filename = "garden_map.txt";
    int total_price = calculate_total_price(filename);

    if (total_price != -1) {
        cout << "Total price: " << total_price << endl;
    }

    return 0;
}
