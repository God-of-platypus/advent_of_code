#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>

using namespace std;

// Function to parse the input into a vector of pairs (target, numbers)
vector<pair<long long, vector<int>>> parseInput(const string& puzzleInput) {
    vector<pair<long long, vector<int>>> equations;
    stringstream ss(puzzleInput);
    string line;

    while (getline(ss, line)) {
        if (line.empty()) continue;

        size_t colonPos = line.find(":");
        if (colonPos == string::npos) {
            cerr << "Warning: Skipping malformed line: " << line << endl;
            continue;
        }

        try {
            string targetPart = line.substr(0, colonPos);
            stringstream targetStream(targetPart);
            long long target;
            targetStream >> target;

            string numbersPart = line.substr(colonPos + 1);
            vector<int> numbers;
            stringstream numsStream(numbersPart);
            int num;
            while (numsStream >> num) {
                numbers.push_back(num);
            }

            equations.emplace_back(target, numbers);
        } catch (const exception& e) {
            cerr << "Error: Unable to parse line: " << line << " - " << e.what() << endl;
        }
    }

    return equations;
}

// Evaluate the expression with the given numbers and operators
long long evaluateExpression(const vector<int>& numbers, const vector<char>& operators) {
    long long result = numbers[0];
    for (size_t i = 0; i < operators.size(); ++i) {
        if (operators[i] == '+') {
            result += numbers[i + 1];
        } else if (operators[i] == '*') {
            result *= numbers[i + 1];
        }
    }
    return result;
}

// Check if any operator combination can match the target
bool canMatchTarget(long long target, const vector<int>& numbers) {
    size_t numOperators = numbers.size() - 1;
    vector<char> operators(numOperators, '+');

    // Generate all combinations of operators
    do {
        if (evaluateExpression(numbers, operators) == target) {
            return true;
        }

        // Increment operator combination
        for (size_t i = 0; i < numOperators; ++i) {
            if (operators[i] == '+') {
                operators[i] = '*';
                break;
            } else {
                operators[i] = '+';
            }
        }
    } while (!all_of(operators.begin(), operators.end(), [](char op) { return op == '+'; }));

    return false;
}

// Compute the total calibration result
long long totalCalibrationResult(const string& puzzleInput) {
    auto equations = parseInput(puzzleInput);
    long long total = 0;

    for (const auto& [target, numbers] : equations) {
        if (canMatchTarget(target, numbers)) {
            total += target;
        }
    }

    return total;
}

int main() {
    // File input
    string filename = "input.txt";

    ifstream inputFile(filename);
    if (!inputFile) {
        cerr << "Error: Unable to open file " << filename << endl;
        return 1;
    }

    stringstream buffer;
    buffer << inputFile.rdbuf();
    string puzzleInput = buffer.str();

    // Compute the result
    long long result = totalCalibrationResult(puzzleInput);
    cout << "Total Calibration Result: " << result << endl;

    return 0;
}
