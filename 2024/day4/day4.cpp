#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

const string word = "XMAS";
const int word_length = word.length();

// Function to check for occurrences in all directions
int countXmasOccurrences(const vector<string>& grid) {
    int count = 0;
    int rows = grid.size();
    int cols = grid[0].length();

    // Check horizontally (both left-to-right and right-to-left)
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c <= cols - word_length; ++c) {
            // Left to right
            if (grid[r].substr(c, word_length) == word) {
                count++;
            }
            // Right to left
            if (string(grid[r].rbegin() + c, grid[r].rbegin() + c + word_length) == word) {
                count++;
            }
        }
    }

    // Check vertically (both top-to-bottom and bottom-to-top)
    for (int c = 0; c < cols; ++c) {
        for (int r = 0; r <= rows - word_length; ++r) {
            // Top to bottom
            string vertical_word = "";
            for (int i = 0; i < word_length; ++i) {
                vertical_word += grid[r + i][c];
            }
            if (vertical_word == word) {
                count++;
            }

            // Bottom to top
            vertical_word = "";
            for (int i = 0; i < word_length; ++i) {
                vertical_word += grid[r + word_length - 1 - i][c];
            }
            if (vertical_word == word) {
                count++;
            }
        }
    }

    // Check diagonally (all four diagonal directions)
    for (int r = 0; r <= rows - word_length; ++r) {
        for (int c = 0; c <= cols - word_length; ++c) {
            // Top-left to bottom-right
            string diagonal_word = "";
            for (int i = 0; i < word_length; ++i) {
                diagonal_word += grid[r + i][c + i];
            }
            if (diagonal_word == word) {
                count++;
            }

            // Bottom-left to top-right
            diagonal_word = "";
            for (int i = 0; i < word_length; ++i) {
                diagonal_word += grid[r + word_length - 1 - i][c + i];
            }
            if (diagonal_word == word) {
                count++;
            }

            // Top-right to bottom-left
            diagonal_word = "";
            for (int i = 0; i < word_length; ++i) {
                diagonal_word += grid[r + i][c + word_length - 1 - i];
            }
            if (diagonal_word == word) {
                count++;
            }

            // Bottom-right to top-left
            diagonal_word = "";
            for (int i = 0; i < word_length; ++i) {
                diagonal_word += grid[r + word_length - 1 - i][c + word_length - 1 - i];
            }
            if (diagonal_word == word) {
                count++;
            }
        }
    }

    return count;
}

int countX_MASOccurrences(const vector<string>& grid) {
    int count = 0;
    int rows = grid.size();
    int cols = grid[0].length();
    const string mas = "MAS";

    // Loop through the grid and check for X-MAS shapes
    for (int r = 1; r < rows - 1; ++r) {  // Center must be in the middle of the X
        for (int c = 1; c < cols - 1; ++c) {
            // Check for the "X" shape centered at (r, c)
            // Forward "MAS" on top-left to bottom-right
            if (grid[r-1][c-1] == 'M' && grid[r][c] == 'A' && grid[r+1][c+1] == 'S' &&
                grid[r-1][c+1] == 'M' && grid[r][c] == 'A' && grid[r+1][c-1] == 'S') {
                count++;
                }

            // Backward "MAS" on top-left to bottom-right
            if (grid[r-1][c-1] == 'S' && grid[r][c] == 'A' && grid[r+1][c+1] == 'M' &&
                grid[r-1][c+1] == 'S' && grid[r][c] == 'A' && grid[r+1][c-1] == 'M') {
                count++;
                }
            if (grid[r-1][c-1] == 'S' && grid[r][c] == 'A' && grid[r+1][c+1] == 'M' &&
                grid[r+1][c-1] == 'S' && grid[r][c] == 'A' && grid[r-1][c+1] == 'M') {
                count++;
                }
            if (grid[r-1][c-1] == 'M' && grid[r][c] == 'A' && grid[r+1][c+1] == 'S' &&
                grid[r+1][c-1] == 'M' && grid[r][c] == 'A' && grid[r-1][c+1] == 'S') {
                count++;
                }

        }
    }

    return count;
}

int main() {
    ifstream file("input.txt");
    if (!file) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    vector<string> grid;
    string line;

    // Read grid from file
    while (getline(file, line)) {
        grid.push_back(line);
    }

    // Count occurrences of "XMAS"
    int result = countXmasOccurrences(grid);
    int x_mas = countX_MASOccurrences(grid);

    cout << "The word 'XMAS' appears " << result << " times." << endl;
    cout << "The word 'MAS' appears " << x_mas << " times in an X shape." << endl;
    return 0;
}
