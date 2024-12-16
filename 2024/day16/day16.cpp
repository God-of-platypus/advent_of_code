#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <tuple>
#include <algorithm>
#include <functional>

using Matrix = std::vector<std::string>;
using Position = std::pair<int, int>;
using Direction = std::pair<int, int>;
using PathMap = std::map<std::tuple<Position, Direction>, int>;
using PathSet = std::set<Position>;

const Direction UP = {-1, 0};
const Direction DOWN = {1, 0};
const Direction LEFT = {0, -1};
const Direction RIGHT = {0, 1};

Matrix parseInput(const std::string &input, Position &start) {
    std::istringstream stream(input);
    std::string line;
    Matrix maze;

    int row = 0;
    while (std::getline(stream, line)) {
        maze.push_back(line);
        for (int col = 0; col < line.size(); ++col) {
            if (line[col] == 'S') {
                start = {row + 1, col + 1};
            }
        }
        ++row;
    }
    return maze;
}

Position move(const Position &pos, const Direction &dir) {
    return {pos.first + dir.first, pos.second + dir.second};
}

std::vector<Direction> turn90(const Direction &dir) {
    if (dir == UP || dir == DOWN) {
        return {LEFT, RIGHT};
    } else {
        return {UP, DOWN};
    }
}

std::tuple<bool, PathMap, int, PathSet> pathFind(const Matrix &maze, PathMap seen, int score, const Direction &dir, const Position &pos) {
    // Avoid revisiting positions with a higher score
    if (seen.count({pos, dir}) && seen[{pos, dir}] < score) {
        return std::make_tuple(false, seen, -1, PathSet{});
    }

    // If the end is reached
    if (maze[pos.first - 1][pos.second - 1] == 'E') {
        return std::make_tuple(true, seen, score, PathSet{pos});
    }

    // If it's a wall
    if (maze[pos.first - 1][pos.second - 1] == '#') {
        return std::make_tuple(false, seen, -1, PathSet{});
    }

    // Mark the current position as visited
    seen[{pos, dir}] = score;

    // Attempt to move forward
    auto forwardResult = pathFind(maze, seen, score + 1, dir, move(pos, dir));
    auto [forwardSuccess, forwardSeen, forwardScore, forwardSeats] = forwardResult;

    // Attempt to turn 90 degrees
    auto dirs = turn90(dir);
    const auto &d1 = dirs[0];
    const auto &d2 = dirs[1];

    auto side1Result = pathFind(maze, forwardSeen, score + 1001, d1, move(pos, d1));
    auto [side1Success, side1Seen, side1Score, side1Seats] = side1Result;

    auto side2Result = pathFind(maze, side1Seen, score + 1001, d2, move(pos, d2));
    auto [side2Success, side2Seen, side2Score, side2Seats] = side2Result;

    // Collect all successful paths
    std::vector<std::tuple<int, PathSet>> solutions;
    if (forwardSuccess) solutions.emplace_back(forwardScore, forwardSeats);
    if (side1Success) solutions.emplace_back(side1Score, side1Seats);
    if (side2Success) solutions.emplace_back(side2Score, side2Seats);

    // If no solutions are found
    if (solutions.empty()) {
        return std::make_tuple(false, side2Seen, -1, PathSet{});
    }

    // Find the minimum score
    int minScore = std::get<0>(*std::min_element(solutions.begin(), solutions.end(), [](const auto &a, const auto &b) {
    return std::get<0>(a) < std::get<0>(b);
    }));

    // Collect all paths with the minimum score
    PathSet allBestSeats;
    for (const auto &[solScore, solSeats] : solutions) {
        if (solScore == minScore) {
            allBestSeats.insert(solSeats.begin(), solSeats.end());
        }
    }

    // Add the current position to all paths
    allBestSeats.insert(pos);

    return std::make_tuple(true, side2Seen, minScore, allBestSeats);
}



std::pair<int, int> solve(const Matrix &maze, const Position &start) {
    auto result = pathFind(maze, {}, 0, RIGHT, start);
    auto [_, __, part1, part2Set] = result;
    return {part1, static_cast<int>(part2Set.size())};
}

void printMaze(const Matrix &maze, const PathSet &path) {
    for (int y = 1; y <= maze.size(); ++y) {
        for (int x = 1; x <= maze[0].size(); ++x) {
            if (path.count({y, x})) {
                std::cout << 'O';
            } else {
                std::cout << maze[y - 1][x - 1];
            }
        }
        std::cout << '\n';
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: ./program <input_file>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "Error: Unable to open file " << argv[1] << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string input = buffer.str();

    Position start;
    auto maze = parseInput(input, start);

    auto [part1, part2] = solve(maze, start);

    std::cout << "Part 1: " << part1 << std::endl;
    std::cout << "Part 2: " << part2 << std::endl;

    auto result = pathFind(maze, {}, 0, RIGHT, start);
    auto [_, __, ___, pathSet] = result;
    printMaze(maze, pathSet);

    return 0;
}
