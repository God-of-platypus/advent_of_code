#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath> // For abs()
#include <string>
#include <bits/locale_facets_nonio.h>


bool is_safe(const std::vector<int>& report) {
    std::vector<int> differences;
    for (size_t i = 0; i < report.size() - 1; ++i) {
        differences.push_back(report[i + 1] - report[i]);
    }

    // Check if all differences are valid
    bool valid_differences = true;
    for (int diff : differences) {
        if (!(abs(diff) >= 1 && abs(diff) <= 3)) {
            valid_differences = false;
            break;
        }
    }

    // Check if the sequence is increasing or decreasing
    bool increasing = true, decreasing = true;
    for (int diff : differences) {
        if (diff <= 0) increasing = false;
        if (diff >= 0) decreasing = false;
    }

    return valid_differences && (increasing || decreasing);
}

bool can_be_made_safe(const std::vector<int>& report) {
    for (size_t i = 0; i < report.size(); ++i) {
        // Create a temporary report excluding the current level
        std::vector<int> temp_report;
        for (size_t j = 0; j < report.size(); ++j) {
            if (i != j) {
                temp_report.push_back(report[j]);
            }
        }
        // Check if the modified report is safe
        if (is_safe(temp_report)) {
            return true;
        }
    }
    return false;
}

int main() {
    // Open the input file
    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open input file!" << std::endl;
        return 1;
    }

    std::string line;

    // Read each line from the file
    int result = 0;
    int result2 = 0;
    while (std::getline(inputFile, line)) {
        std::vector<int> values;
        std::stringstream ss(line);
        int value;
        while (ss >> value) {
            values.push_back(value);
        }
        if (is_safe(values)) {
            result++;
            result2++;
        } else if (can_be_made_safe(values)) {
            result2++;
        }
    }


    std::cout << "There is "<< result << " safe results" << std::endl;
    std::cout << "There is "<< result2 << " safe results with Problem Dampeners" << std::endl;

    inputFile.close();
    return 0;
}
