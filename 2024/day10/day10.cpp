#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <set>
#include <string>

using namespace std;

typedef pair<int, int> Position;

vector<vector<int>> parseMap(const string &filename) {
    ifstream file(filename);
    vector<vector<int>> grid;
    string line;

    while (getline(file, line)) {
        vector<int> row;
        for (char c : line) {
            row.push_back(c - '0');
        }
        grid.push_back(row);
    }

    return grid;
}

vector<Position> findTrailheads(const vector<vector<int>> &grid) {
    vector<Position> trailheads;
    for (int r = 0; r < grid.size(); ++r) {
        for (int c = 0; c < grid[0].size(); ++c) {
            if (grid[r][c] == 0) {
                trailheads.emplace_back(r, c);
            }
        }
    }
    return trailheads;
}

int findScore(const vector<vector<int>> &grid, const Position &trailhead) {
    int rows = grid.size();
    int cols = grid[0].size();
    queue<Position> q;
    set<Position> visited;
    set<Position> reachableNines;

    q.push(trailhead);
    visited.insert(trailhead);

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        int currentHeight = grid[r][c];

        // Check neighbors (up, down, left, right)
        vector<Position> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (auto [dr, dc] : directions) {
            int nr = r + dr;
            int nc = c + dc;

            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) { // Stay within bounds
                int neighborHeight = grid[nr][nc];
                if (visited.find({nr, nc}) == visited.end() && neighborHeight == currentHeight + 1) {
                    visited.insert({nr, nc});
                    q.push({nr, nc});

                    if (neighborHeight == 9) {
                        reachableNines.insert({nr, nc});
                    }
                }
            }
        }
    }

    return reachableNines.size();
}

int sumTrailheadScores(const string &filename) {
    vector<vector<int>> grid = parseMap(filename);
    vector<Position> trailheads = findTrailheads(grid);
    int totalScore = 0;

    for (const auto &trailhead : trailheads) {
        totalScore += findScore(grid, trailhead);
    }

    return totalScore;
}

int countDistinctTrails(const vector<vector<int>> &grid, const Position &trailhead) {
    int rows = grid.size();
    int cols = grid[0].size();
    queue<pair<Position, vector<Position>>> q;
    set<vector<Position>> distinctTrails;

    q.push({trailhead, {trailhead}});

    while (!q.empty()) {
        auto [current, path] = q.front();
        q.pop();

        int r = current.first;
        int c = current.second;
        int currentHeight = grid[r][c];

        vector<Position> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (auto [dr, dc] : directions) {
            int nr = r + dr;
            int nc = c + dc;

            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
                int neighborHeight = grid[nr][nc];
                if (neighborHeight == currentHeight + 1) {
                    vector<Position> newPath = path;
                    newPath.emplace_back(nr, nc);

                    if (neighborHeight == 9) {
                        distinctTrails.insert(newPath);
                    } else {
                        q.push({{nr, nc}, newPath});
                    }
                }
            }
        }
    }

    return distinctTrails.size();
}


int sumTrailheadRatings(const string &filename) {
    vector<vector<int>> grid = parseMap(filename);
    vector<Position> trailheads = findTrailheads(grid);
    int totalRating = 0;

    for (const auto &trailhead : trailheads) {
        totalRating += countDistinctTrails(grid, trailhead);
    }

    return totalRating;
}


int main() {
    string filename = "input.txt";
    cout << "Sum of trailhead scores: " << sumTrailheadScores(filename) << endl;
    cout << "Sum of trailhead ratings: " << sumTrailheadRatings(filename) << endl;
    return 0;
}
