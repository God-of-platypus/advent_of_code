#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <tuple>
#include <unordered_map>

using namespace std;

pair <int,int> simulatePatrol(const vector<string>& labMap) {
    // Directions: up, right, down, left (in clockwise order)
    unordered_map<char, pair<int, int>> directions = {
        {'^', {-1, 0}}, {'>', {0, 1}}, {'v', {1, 0}}, {'<', {0, -1}}
    };
    unordered_map<char, char> turnRight = {
        {'^', '>'}, {'>', 'v'}, {'v', '<'}, {'<', '^'}
    };

    int rows = labMap.size();
    int cols = labMap[0].size();

    pair<int, int> guardPos;
    char guardDir;

    // Parse the map to find guard's initial position and obstacles
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            char cell = labMap[r][c];
            if (directions.count(cell)) {
                guardPos = {r, c};
                guardDir = cell;
                break;
            }
        }
    }

    set<pair<int, int>> visitedPositions;
    visitedPositions.insert(guardPos);

    while (true) {
        // Calculate the position in front of the guard
        auto [dr, dc] = directions[guardDir];
        pair<int, int> nextPos = {guardPos.first + dr, guardPos.second + dc};

        if (nextPos.first < 0 || nextPos.second < 0 || nextPos.second >= cols || nextPos.first >= rows) {
            break;
        }

        if (labMap[nextPos.first][nextPos.second] != '#') {
            guardPos = nextPos;
            visitedPositions.insert(guardPos);
        } else {
            guardDir = turnRight[guardDir];
        }
    }

    return {visitedPositions.size(),0};
}

bool loop(const vector<string>& labMap) {
    unordered_map<char, pair<int, int>> directions = {
        {'^', {-1, 0}}, {'>', {0, 1}}, {'v', {1, 0}}, {'<', {0, -1}}
    };
    unordered_map<char, char> turnRight = {
        {'^', '>'}, {'>', 'v'}, {'v', '<'}, {'<', '^'}
    };

    int rows = labMap.size();
    int cols = labMap[0].size();

    pair<int, int> guardPos;
    char guardDir;



    // Parse the map to find guard's initial position and obstacles
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            char cell = labMap[r][c];
            if (directions.count(cell)) {
                guardPos = {r, c};
                guardDir = cell;
                break;
            }
        }
    }
    set<pair<pair<int, int>,char>> visitedPositions;
    visitedPositions.insert({guardPos, guardDir});


    while (true) {
        auto [dr, dc] = directions[guardDir];
        pair<int, int> nextPos = {guardPos.first + dr, guardPos.second + dc};

        if (nextPos.first < 0 || nextPos.second < 0 || nextPos.second >= cols || nextPos.first >= rows) {
            break;
        }

        if (visitedPositions.count({nextPos,guardDir}) == 1) {
            return true;
        }

        if (labMap[nextPos.first][nextPos.second] != '#') {
            guardPos = nextPos;
            visitedPositions.insert({guardPos,guardDir});
        } else {
            guardDir = turnRight[guardDir];
            visitedPositions.insert({guardPos, guardDir});
        }
    }
    return false;
}

int main() {
    ifstream inputFile("input.txt");
    vector<string> labMap;
    string line;

    // Read the map from the input file
    while (getline(inputFile, line)) {
        labMap.push_back(line);
    }

    inputFile.close();

    // Simulate the patrol and output the result
    auto result = simulatePatrol(labMap);
    cout << "Distinct positions visited: " << result.first << endl;

    auto part2 = 0;
    for (int i = 0; i < labMap.size(); ++i) {
        for (int j = 0; j < labMap[i].size(); ++j) {
            if (labMap[i][j] == '.') {
                labMap[i][j] = '#';
                part2 += loop(labMap);
                labMap[i][j] = '.';
            }
        }
    }

    cout << part2 << endl;
    return 0;
}
