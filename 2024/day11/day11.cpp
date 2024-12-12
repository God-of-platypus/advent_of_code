#include <iostream>
#include <unordered_map>
#include <cstdint>

// Function to count the number of stones after a given number of blinks
uint64_t count_stones_after_blinks(const std::unordered_map<uint64_t, uint64_t>& initial_histogram, int blinks) {
    std::unordered_map<uint64_t, uint64_t> histogram = initial_histogram;

    for (int i = 0; i < blinks; ++i) {
        std::unordered_map<uint64_t, uint64_t> new_histogram;

        for (const auto& [stone, count] : histogram) {
            if (stone == 0) {
                new_histogram[1] += count;
            } else {
                // Calculate the number of digits
                uint64_t temp = stone, digits = 0;
                while (temp > 0) {
                    temp /= 10;
                    digits++;
                }

                if (digits % 2 == 0) {
                    // Split the number
                    uint64_t divisor = 1;
                    for (uint64_t j = 0; j < digits / 2; ++j) {
                        divisor *= 10;
                    }
                    uint64_t left = stone / divisor;
                    uint64_t right = stone % divisor;
                    new_histogram[left] += count;
                    new_histogram[right] += count;
                } else {
                    new_histogram[stone * 2024] += count;
                }
            }
        }

        histogram.swap(new_histogram); // Efficiently replace the old histogram
    }

    uint64_t total_stones = 0;
    for (const auto& [stone, count] : histogram) {
        total_stones += count;
    }
    return total_stones;
}

int main() {
    // Initial arrangement of stones as a histogram
    std::unordered_map<uint64_t, uint64_t> initial_histogram = {
        {28591, 1}, {78, 1}, {0, 1}, {3159881, 1}, {4254, 1}, {524155, 1}, {598, 1}, {1, 1}
    };

    // Number of blinks
    int blinks = 75;

    // Compute the number of stones after 75 blinks
    try {
        uint64_t number_of_stones = count_stones_after_blinks(initial_histogram, blinks);
        std::cout << "Number of stones after " << blinks << " blinks: " << number_of_stones << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

