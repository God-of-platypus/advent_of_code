#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <regex>
#include <map>
#include <cmath>
#include <cstdlib>

const std::vector<std::pair<int, int>> cross_dirs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
const int MIN_SAVE = 100;

std::vector<std::vector<int>> MapLoad(const std::string& filename) {
    std::vector<std::vector<int>> map;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file." << std::endl;
        exit(1);
    }
    std::string line;
    while (std::getline(file, line)) {
        std::vector<int> row;
        for (char c : line) {
            row.push_back(c == '#' ? -1 : (c == '.' ? 0 : c));
        }
        map.push_back(row);
    }
    return map;
}

template <typename T>
std::vector<std::vector<T>> MapCopy(const std::vector<std::vector<T>>& Map) {
    return Map;
}

bool MapIsOutOfBounds(const std::vector<std::vector<int>>& Map, int x, int y) {
    return x < 0 || y < 0 || y >= Map.size() || x >= Map[0].size();
}

void BFS(std::vector<std::vector<int>>& Map, int stx, int sty, int edx, int edy, std::vector<int> gdchars, int stn = 0, int max_n = -1) {
    std::queue<std::tuple<int, int, int>> q;
    q.push({stx, sty, stn});
    Map[sty][stx] = stn;

    while (!q.empty()) {
        auto [x, y, n] = q.front();
        q.pop();

        for (const auto& [dx, dy] : cross_dirs) {
            int nx = x + dx, ny = y + dy, nn = n + 1;
            if (max_n > 0 && nn >= max_n) return;
            if (MapIsOutOfBounds(Map, nx, ny)) continue;
            if (std::find(gdchars.begin(), gdchars.end(), Map[ny][nx]) == gdchars.end()) continue;

            Map[ny][nx] = nn;
            if (nx == edx && ny == edy) return;
            q.push({nx, ny, nn});
        }
    }
}

void BFS2(std::vector<std::vector<int>>& Map, int stchar, int edchar, std::vector<int> gdchars = {0}) {
    int stx = -1, sty = -1, edx = -1, edy = -1;
    for (int y = 0; y < Map.size(); ++y) {
        for (int x = 0; x < Map[y].size(); ++x) {
            if (Map[y][x] == stchar) { stx = x; sty = y; }
            if (Map[y][x] == edchar) { edx = x; edy = y; }
        }
    }
    if (stx == -1 || edx == -1) return;

    gdchars.push_back(edchar);
    BFS(Map, stx, sty, edx, edy, gdchars);
}

std::vector<int> getDiff(const std::vector<std::vector<int>>& NormalRace, const std::vector<std::vector<int>>& Map, int x, int y, int offset) {
    std::vector<int> diffs;
    for (int dx = -offset; dx <= offset; ++dx) {
        int dy = std::abs(dx) - offset;

        int nx = x + dx, ny = y + dy;
        if (!MapIsOutOfBounds(Map, nx, ny) && NormalRace[ny][nx] >= 0) {
            int d = NormalRace[ny][nx] - offset - NormalRace[y][x];
            diffs.push_back(d);
        }

        dy = -dy;
        nx = x + dx, ny = y + dy;
        if (dy != 0 && !MapIsOutOfBounds(Map, nx, ny) && NormalRace[ny][nx] >= 0) {
            int d = NormalRace[ny][nx] - offset - NormalRace[y][x];
            diffs.push_back(d);
        }
    }
    return diffs;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " [input filename]" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::vector<std::vector<int>> Map = MapLoad(filename);

    int w = Map[0].size(), h = Map.size();

    auto NormalRace = MapCopy(Map);
    BFS2(NormalRace, 'S', 'E');

    std::map<int, int> shortcut2;
    std::map<int, int> shortcut1;
    int ttshortcuts = 0;

    int part1 = 0;

    for (int x = 1; x < w - 1; ++x) {
        for (int y = 1; y < h - 1; ++y) {
            if (Map[y][x] == -1) continue;

            auto d = getDiff(NormalRace, Map, x, y, 2);
            for (int diff : d) {
                if (diff >= MIN_SAVE) {
                    shortcut1[diff]++;
                    part1++;
                }
            }
            for (int offset = 2; offset <= 20; ++offset) {
                auto diffs = getDiff(NormalRace, Map, x, y, offset);
                for (int diff : diffs) {
                    if (diff >= MIN_SAVE) {
                        shortcut2[diff]++;
                        ttshortcuts++;

                    }
                }
            }
        }
    }
    std::cout << "Part 1: " << part1 << std::endl;
    std::cout << "Part 2: " << ttshortcuts << std::endl;
    return 0;
}
