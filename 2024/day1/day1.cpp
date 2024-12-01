#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <cmath> // For abs()

int calculateTotalDistance(std::vector<int>& left, std::vector<int>& right) {
    // Step 1: Sort both lists in ascending order
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());

    // Step 2: Calculate the total distance
    int totalDistance = 0;
    for (size_t i = 0; i < left.size(); ++i) {
        totalDistance += std::abs(left[i] - right[i]);
    }

    return totalDistance;
}

int calculateSimilarityScore(const std::vector<int>& left, const std::vector<int>& right) {
    // Step 1: Count frequencies in the right list
    std::unordered_map<int, int> rightFrequency;
    for (int num : right) {
        rightFrequency[num]++;
    }

    // Step 2: Calculate similarity score
    int similarityScore = 0;
    for (int num : left) {
        if (rightFrequency.find(num) != rightFrequency.end()) {
            similarityScore += num * rightFrequency[num];
        }
    }

    return similarityScore;
}

int main() {
    // Open the input file
    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open input file!" << std::endl;
        return 1;
    }

    // Vectors to store left and right lists
    std::vector<int> left, right;
    std::string line;

    // Read each line from the file
    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        int leftValue, rightValue;

        // Extract two integers from the line
        if (ss >> leftValue >> rightValue) {
            left.push_back(leftValue);
            right.push_back(rightValue);
        } else {
            std::cerr << "Error: Invalid input format in line: " << line << std::endl;
            return 1;
        }
    }

    inputFile.close();

    // Check if the lists are the same size
    if (left.size() != right.size()) {
        std::cerr << "Error: The two lists must have the same number of elements!" << std::endl;
        return 1;
    }

    // Calculate the total distance
    int result = calculateTotalDistance(left, right);

    // Output the result
    std::cout << "The total distance between the lists is: " << result << std::endl;

    result = calculateSimilarityScore(left, right);
    std::cout << "The similarity score between the lists is: " << result << std::endl;

    return 0;
}

