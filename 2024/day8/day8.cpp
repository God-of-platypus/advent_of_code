#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <optional>

using namespace std;

typedef pair<int, int> Point;
typedef vector<Point> VPoint;
typedef map<char, VPoint> VMap;

optional<Point> antinodePosition(vector<string> map, Point A, Point B) {
    int row = map.size();
    int col = map[0].size();

    const int dx = A.first - B.first;
    const int dy = A.second - B.second;

    Point candidate = {A.first + dx, A.second + dy};
    if (candidate == B) {
        candidate = {A.first - dx, A.second - dy};
        if (candidate.first < 0 || candidate.second < 0 || candidate.first >= row || candidate.second >= col) {
            return {};
        }
        return candidate;
    }
    if (candidate.first >= row || candidate.second >= col || candidate.first < 0 || candidate.second < 0) {
        return {};
    }
    return candidate;
}


VPoint antinodesPosition(vector<string> map, Point A, Point B) {
    int row = map.size();
    int col = map[0].size();

    const int dx = A.first - B.first;
    const int dy = A.second - B.second;

    VPoint result;
    bool a_out = false;
    bool b_out = false;
    int i = 0;
    while (!a_out || !b_out) {
        if (A.first + i * dx < row && A.second + i * dy < col && A.first + i * dx >= 0 && A.second + i * dy >= 0) {
            result.emplace_back(A.first + i *dx, A.second + i * dy);
        } else {
            a_out = true;
        }

        if (B.first - i * dx < row && B.second - i * dy < col && B.first - i * dx >= 0 && B.second - i * dy >= 0) {
            result.emplace_back(B.first - i *dx, B.second - i * dy);
        } else {
            b_out = true;
        }
        i++;
    }
    return result;
}


int main() {
    ifstream inputFile("input.txt");
    vector<string> map;
    string line;

    // Read the input file into the map
    while (getline(inputFile, line)) {
        map.push_back(line);
    }

    inputFile.close();

    int rows = map.size();
    int cols = map[0].size();

    // Map to store positions of each frequency
    VMap antennas;

    // Populate the antennas map
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            char ch = map[r][c];
            if (ch != '.') {
                antennas[ch].emplace_back(r, c);
            }
        }
    }

    set<Point> antinodes; // To store unique antinodes
    set<Point> antinodesPart2;

    // Iterate over each frequency
    for (auto& entry : antennas) {
        char freq = entry.first;
        vector<Point>& positions = entry.second;
        int n = positions.size();
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                // Calculate distance between two antennas
                Point p1 = positions[i];
                Point p2 = positions[j];
                optional<Point> antinode = antinodePosition(map, p1, p2);
                if (antinode.has_value()) {
                    antinodes.insert(*antinode);
                }
                antinode = antinodePosition(map, p2, p1);
                if (antinode.has_value()) {
                    antinodes.insert(*antinode);
                }

                VPoint result = antinodesPosition(map, p1, p2);
                for (auto& p : result) {
                    antinodesPart2.insert(p);
                }
            }
        }
    }

    // Output the number of unique antinodes
    cout << "Unique antinodes: " << antinodes.size() << endl;
    cout << "Unique antinodesPart2: " << antinodesPart2.size() << endl;

    return 0;
}
