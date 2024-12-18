#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <tuple>
#include <fstream>

typedef std::pair<int, int> Coordinate;

std::vector<std::pair<int,int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int simulateAndFindShortestPath(int gridSize, const std::vector<Coordinate>& bytePositions, int maxBytes) {
    // Initialize the memory space
    std::vector<std::string> grid(gridSize, std::string(gridSize, '.'));

    // Simulate bytes falling
    for (int i = 0; i < maxBytes && i < bytePositions.size(); i++) {
        int x = bytePositions[i].first;
        int y = bytePositions[i].second;
        grid[y][x] = '#';  // Mark the cell as corrupted
    }

    // Breadth-First Search (BFS) to find the shortest path
    auto bfs = [&](Coordinate start, Coordinate goal) -> int {
        std::queue<std::tuple<int, int, int>> q; // (x, y, steps)
        std::set<Coordinate> visited;
        q.emplace(start.first, start.second, 0);
        visited.insert(start);

        while (!q.empty()) {
            auto [x, y, steps] = q.front();
            q.pop();

            // If we reach the goal, return the number of steps
            if (x == goal.first && y == goal.second) {
                return steps;
            }

            // Check all possible moves (up, down, left, right)
            for (auto [dx, dy] : directions) {
                int nx = x + dx;
                int ny = y + dy;

                if (nx >= 0 && nx < gridSize && ny >= 0 && ny < gridSize &&
                    visited.find({nx, ny}) == visited.end() && grid[ny][nx] == '.') {
                    q.emplace(nx, ny, steps + 1);
                    visited.insert({nx, ny});
                }
            }
        }

        return -1;  // If no path is found
    };

    // Start BFS from top-left corner to bottom-right corner
    Coordinate start = {0, 0};
    Coordinate goal = {gridSize - 1, gridSize - 1};
    return bfs(start, goal);
}

std::vector<Coordinate> readBytePositionsFromFile(const std::string& filename) {
    std::vector<Coordinate> bytePositions;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return bytePositions;
    }

    int x, y;
    char comma;
    while (file >> x >> comma >> y) {
        bytePositions.emplace_back(x, y);
    }

    file.close();
    return bytePositions;
}

int main() {
    // Example input file
    std::string filename = "input.txt";
    std::vector<Coordinate> bytePositions = readBytePositionsFromFile(filename);

    // For the full problem
    int gridSizeFull = 71;
    int res = 0;
    int i = 1024;
    std::cout << simulateAndFindShortestPath(gridSizeFull, bytePositions, i) << std::endl;
    while (res >= 0) {
        i++;
        res = simulateAndFindShortestPath(gridSizeFull, bytePositions, i);
    }
    std::cout << bytePositions[i - 1].first << "," << bytePositions[i - 1].second << std::endl;
    return 0;
}