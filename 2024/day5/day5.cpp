#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

// Function to parse the input from the file
void parseInput(const string& filename, vector<pair<int, int>>& rules, vector<vector<int>>& updates) {
    ifstream file(filename);
    string line;
    bool parsingUpdates = false;

    while (getline(file, line)) {
        if (line.empty()) {
            parsingUpdates = true;
            continue;
        }

        if (!parsingUpdates) {
            // Parse rules in the format "X|Y"
            stringstream ss(line);
            int x, y;
            char sep;
            ss >> x >> sep >> y;
            rules.emplace_back(x, y);
        } else {
            // Parse updates in the format "X,Y,Z,..."
            vector<int> update;
            stringstream ss(line);
            int page;
            while (ss >> page) {
                update.push_back(page);
                if (ss.peek() == ',') ss.ignore();
            }
            updates.push_back(update);
        }
    }
}

// Function to check if an update is valid
bool isValidUpdate(const vector<int>& update, const vector<pair<int, int>>& rules) {
    unordered_map<int, int> pagePosition;
    for (int i = 0; i < update.size(); ++i) {
        pagePosition[update[i]] = i;
    }

    // Check each rule
    for (const auto& rule : rules) {
        int x = rule.first, y = rule.second;
        if (pagePosition.count(x) && pagePosition.count(y)) {
            if (pagePosition[x] >= pagePosition[y]) {
                return false;
            }
        }
    }

    return true;
}

// Function to reorder an update based on the rules
vector<int> reorderUpdate(const vector<int>& update, const vector<pair<int, int>>& rules) {
    vector<int> reordered = update;

    // Simple sort based on the rules
    sort(reordered.begin(), reordered.end(), [&rules, &reordered](int a, int b) {
        for (const auto& rule : rules) {
            if (rule.first == a && rule.second == b) return true;  // a must come before b
            if (rule.first == b && rule.second == a) return false; // b must come before a
        }
        return false; // Default, no rule implies no specific order
    });

    return reordered;
}


int main() {
    string filename = "input.txt";
    vector<pair<int, int>> rules;
    vector<vector<int>> updates;

    // Parse the input
    parseInput(filename, rules, updates);

    int middlePageSum = 0;

    int updateSum = 0;
    // Process each update
    for (const auto& update : updates) {
        if (isValidUpdate(update, rules)) {
            int middleIndex = update.size() / 2;
            middlePageSum += update[middleIndex];
        } else {
            auto tmp = reorderUpdate(update, rules);
            int middleIndex = tmp.size() / 2;
            updateSum += tmp[middleIndex];
        }
    }

    // Output the result
    cout << "Sum of middle pages: " << middlePageSum << endl;
    cout << "Sum of updates: " << updateSum << endl;


    return 0;
}
