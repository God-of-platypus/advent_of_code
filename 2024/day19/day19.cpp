#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <string>
#include <sstream>
#include <algorithm>
#include <unordered_map>

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return (first == std::string::npos) ? "" : str.substr(first, last - first + 1);
}

// Function to check if a design can be formed using the towel patterns
bool canFormDesign(const std::string& design, const std::unordered_set<std::string>& patterns) {
    int n = design.size();
    std::vector<bool> dp(n + 1, false);
    dp[0] = true; // Base case: empty string can always be formed

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (dp[j] && patterns.count(design.substr(j, i - j))) {
                dp[i] = true;
                break;
            }
        }
    }

    return dp[n];
}

// Recursive function to count all ways to form a design
u_int64_t countWays(const std::string& design, const std::unordered_set<std::string>& patterns, std::unordered_map<std::string, u_int64_t>& memo) {
    // Base case: empty design
    if (design.empty()) return 1;

    // Check if the result is already computed
    if (memo.find(design) != memo.end()) {
        return memo[design];
    }

    u_int64_t totalWays = 0;

    // Try all patterns that match the prefix of the design
    for (const auto& pattern : patterns) {
        if (design.substr(0, pattern.size()) == pattern) {
            totalWays += countWays(design.substr(pattern.size()), patterns, memo);
        }
    }

    // Memoize the result
    memo[design] = totalWays;
    return totalWays;
}

int main() {
    std::ifstream inputFile("input.txt");
    if (!inputFile) {
        std::cerr << "Error: Unable to open input file." << std::endl;
        return 1;
    }

    // Read towel patterns from the first line
    std::string line;
    std::getline(inputFile, line);
    std::unordered_set<std::string> patterns;
    std::istringstream patternStream(line);
    std::string pattern;
    while (std::getline(patternStream, pattern, ',')) {
        patterns.insert(trim(pattern));
    }

    // Skip the blank line
    std::getline(inputFile, line);

    // Read desired designs
    std::vector<std::string> designs;
    while (std::getline(inputFile, line)) {
        if (!line.empty()) {
            designs.push_back(line);
        }
    }

    inputFile.close();

    // Count how many designs can be formed
    int possibleCount = 0;
    for (const auto& design : designs) {
        if (canFormDesign(design, patterns)) {
            ++possibleCount;
        }
    }
    std::cout << "Number of possible designs: " << possibleCount << std::endl;

    u_int64_t totalArrangements = 0;
    for (const auto& design : designs) {
        std::unordered_map<std::string, u_int64_t> memo;
        totalArrangements += countWays(design, patterns, memo);
    }

    std::cout << "Total number of arrangements: " << totalArrangements << std::endl;
    return 0;
}
