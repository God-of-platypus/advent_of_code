#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

int64_t part1(const std::vector<std::string> input) {
    int64_t result = 0;
    for (const auto & string : input) {
        std::vector<std::pair<int64_t, bool>> memory;
        bool empty = false;
        int id = 0;
        for (int j = 0; j < string.size(); j++) {
            int c = string[j] - '0';
            for (int k = 0; k < c; k++) {
                memory.emplace_back(id, empty);
            }
            if (!empty) {
                empty = true;
                id++;
            } else {
                empty = false;
            }
        }
        for (size_t i = memory.size(); i > 0; i--) {
            auto & pair = memory[i - 1];
            if (!pair.second) {
                for (int j = 0; j < i - 1; j++) {
                    auto & pair2 = memory[j];
                    if (pair2.second) {
                        pair2.second = false;
                        pair.second = true;
                        pair2.first =pair.first;
                        break;
                    }
                }
            }
        }
        for (int i = 0; i < memory.size(); i++) {
            if (!memory[i].second) {
                result += i * memory[i].first;
            }
        }
    }
    return result;
}

int64_t part2 (std::vector<std::string> input) {
    int64_t result = 0;
    for (const auto & string : input) {
        std::vector<std::pair<int64_t, bool>> memory;
        bool empty = false;
        int id = 0;
        for (char j : string) {
            int c = j - '0';
            for (int k = 0; k < c; k++) {
                memory.emplace_back(id, empty);
            }
            if (!empty) {
                empty = true;
                id++;
            } else {
                empty = false;
            }
        }

        int following = 0;
        int previousId = memory[memory.size() - 1 ].first;
        for (size_t i = memory.size(); i > 0; i--) {
            auto & pair = memory[i - 1];
            if (!pair.second && following == 0) {
                previousId = pair.first;
            }
            if (!pair.second && pair.first == previousId) {
                following++;
            }
            if ((pair.second && pair.first ==  previousId && following !=0 ) || (previousId != pair.first)) {
                for (int j = 0; j < i -1; j++) {
                    auto & pair2 = memory[j];
                    if (pair2.second) {
                        int count = 0;
                        for (int k = j; k < j + following; k++) {
                            if (!memory[k].second) {
                                break;
                            }
                            count++;
                        }
                        if (count == following) {
                            for (int l = 0; l < following; l++) {
                                memory[j + l].second = false;
                                memory[j + l].first = previousId;
                                memory[i + l].second = true;
                            }
                            break;

                        } else {
                            j += count - 1;
                        }
                    }
                }
                if (pair.second) {
                    i++;
                    following = 0;
                } else {
                    following = 1;
                    previousId = pair.first;
                }
                /*
                for (auto &[fst, snd] : memory) {
                    if (!snd) {
                        std::cout << fst;
                    } else {
                        std::cout << ".";
                    }
                }
                std::cout << std::endl;
                */
            }

        }
        for (int i = 0; i < memory.size(); i++) {
            if (!memory[i].second) {
                result += i * memory[i].first;
            }
        }

    }
    return result;
}

int main() {
    std::ifstream inputFile("input.txt");
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(inputFile, line)) {
        lines.push_back(line);
    }

    int64_t result = part1(lines);
    std::cout << result << std::endl;
    result = part2(lines);
    std::cout << result << std::endl;


    return 0;
}
