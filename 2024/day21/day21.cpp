#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <tuple>
#include <algorithm>
#include <limits>
#include <sstream>
#include <functional>


namespace std {
    template <>
    struct hash<std::pair<int, int>> {
        std::size_t operator()(const std::pair<int, int>& p) const noexcept {
            auto hash1 = std::hash<int>{}(p.first);
            auto hash2 = std::hash<int>{}(p.second);
            return hash1 ^ (hash2 << 1); // Combine the two hash values
        }
    };
}

// Direction dictionary
std::unordered_map<std::pair<int, int>, char, std::hash<std::pair<int, int>>> DD = {
    {{1, 0}, '>'}, {{-1, 0}, '<'}, {{0, 1}, 'v'}, {{0, -1}, '^'}
};

// Keypad mapping
std::unordered_map<char, std::pair<int, int>> PADD = {
    {'7', {0, 0}}, {'8', {1, 0}}, {'9', {2, 0}},
    {'4', {0, 1}}, {'5', {1, 1}}, {'6', {2, 1}},
    {'1', {0, 2}}, {'2', {1, 2}}, {'3', {2, 2}},
    {'0', {1, 3}}, {'A', {2, 3}}, {'^', {1, 0}},
    {'a', {2, 0}}, {'<', {0, 1}}, {'v', {1, 1}}, {'>', {2, 1}}
};

// Custom hash function for std::tuple
struct TupleHash {
    template <typename T>
    size_t operator()(const T& tuple) const {
        size_t hash = 0;
        std::apply([&](auto&&... args) {
            ((hash ^= std::hash<std::decay_t<decltype(args)>>{}(args) + 0x9e3779b9 + (hash << 6) + (hash >> 2)), ...);
        }, tuple);
        return hash;
    }
};

std::unordered_map<std::tuple<std::string, int, int>, int, TupleHash> SEEN;

std::vector<std::string> moves_set(int x, int y, int dx, int dy, int robs) {
    int ax = (dx < x) ? -1 : 1;
    int ay = (dy < y) ? -1 : 1;

    if (x == dx && y == dy) {
        return {"a"};
    }

    std::vector<std::string> results;
    std::string x_first, y_first;
    int x1 = x, y1 = y, x2 = x, y2 = y;

    // X first
    while (x1 != dx) {
        if (x1 + ax == 0 && y1 == robs) break;
        x1 += ax;
        x_first += DD[{ax, 0}];
    }
    while (y1 != dy) {
        y1 += ay;
        x_first += DD[{0, ay}];
    }
    while (x1 != dx) {
        x1 += ax;
        x_first += DD[{ax, 0}];
    }
    x_first += "a";

    // Y first
    while (y2 != dy) {
        if (x2 == 0 && y2 + ay == robs) break;
        y2 += ay;
        y_first += DD[{0, ay}];
    }
    while (x2 != dx) {
        x2 += ax;
        y_first += DD[{ax, 0}];
    }
    while (y2 != dy) {
        y2 += ay;
        y_first += DD[{0, ay}];
    }
    y_first += "a";

    results.push_back(x_first);
    results.push_back(y_first);
    return results;
}

int shortest(const std::string& code, int lim, int depth = 0) {
    auto key = std::make_tuple(code, depth, lim);
    if (SEEN.find(key) != SEEN.end()) {
        return SEEN[key];
    }

    bool first = (depth == 0);
    int x = 2, y = (first ? 3 : 0);
    int acc = 0;

    for (char c : code) {
        auto [dx, dy] = PADD[c];
        auto moves = moves_set(x, y, dx, dy, first ? 3 : 0);

        if (depth == lim) {
            acc += moves[0].length();
        } else {
            int min_moves = std::numeric_limits<int>::max();
            for (const auto& move : moves) {
                min_moves = std::min(min_moves, shortest(move, lim, depth + 1));
            }
            acc += min_moves;
        }

        x = dx;
        y = dy;
    }

    SEEN[key] = acc;
    return acc;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::ifstream infile(argv[1]);
    if (!infile) {
        std::cerr << "Error: Could not open file " << argv[1] << std::endl;
        return 1;
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(infile, line)) {
        lines.push_back(line);
    }
    infile.close();

    int acc = 0, acc2 = 0;

    for (const auto& code : lines) {
        std::string trimmed_code = code;
        trimmed_code.erase(std::remove(trimmed_code.begin(), trimmed_code.end(), '\n'), trimmed_code.end());

        int res = std::stoi(trimmed_code.substr(0, 3));
        acc += shortest(trimmed_code, 2) * res;
        acc2 += shortest(trimmed_code, 25) * res;
    }

    std::cout << "Part1: " << acc << std::endl;
    std::cout << "Part2: " << acc2 << std::endl;

    return 0;
}
