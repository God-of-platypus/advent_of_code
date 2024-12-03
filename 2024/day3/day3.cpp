#include <iostream>
#include <fstream>
#include <regex>
#include <string>

int main() {
    // File containing the corrupted memory
    std::string filename = "input.txt";
    std::ifstream input_file(filename);

    if (!input_file.is_open()) {
        std::cerr << "Error: Could not open the file!" << std::endl;
        return 1;
    }

    // Read the entire file content into a string
    std::string corrupted_memory((std::istreambuf_iterator<char>(input_file)),
                                 std::istreambuf_iterator<char>());

    // Close the file
    input_file.close();

    // Define a regex pattern for valid mul(X,Y)
    std::regex full_pattern(R"(mul\((\d{1,3}),(\d{1,3})\)|do\(\)|don't\(\))");
    std::regex pattern(R"(mul\((\d{1,3}),(\d{1,3})\))");
    std::regex do_pattern(R"(do\(\))");
    std::regex dont_pattern(R"(don't\(\))");

    // Iterator to find all matches
    std::sregex_iterator begin(corrupted_memory.begin(), corrupted_memory.end(), full_pattern);
    auto end = std::sregex_iterator();

    // Calculate the sum of valid results
    int total_sum_part1 = 0;
    int total_sum_part2 = 0;
    bool mul_enabled = true;
    for (auto it = begin; it != end; ++it) {
        const std::smatch& match = *it;


        if (std::regex_match(match.str(), do_pattern)) {
            mul_enabled = true;
            std::cout << "Matched a do" << std::endl;
        }
        // Check for don't()
        else if (std::regex_match(match.str(), dont_pattern)) {
            std::cout << "Matched a dont" << std::endl;
            mul_enabled = false;
        } else if (match[1].matched && match[2].matched) {
            int x = std::stoi(match[1].str());
            int y = std::stoi(match[2].str());
            if (mul_enabled) {
                total_sum_part2 += x * y;
            }
            total_sum_part1 += x * y;
        }
        // Check for do()

    }

    // Output the result
    std::cout << "Total Sum: " << total_sum_part1 << std::endl;
    std::cout << "Total Sum: " << total_sum_part2 << std::endl;

    return 0;
}