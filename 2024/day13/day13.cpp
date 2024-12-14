#include <iostream>
#include <vector>
#include <tuple>
#include <array>
#include <cmath>
#include <fstream>
#include <optional>
#include <regex>


double determinant(const std::array<std::array<double, 2>, 2>& mat) {
    return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
}

int main() {
    std::vector<std::tuple<int, int, int, int, int, int>> data;

    // Read input from file
    std::ifstream infile("input.txt");
    if (!infile) {
        std::cerr << "Error: Could not open input file." << std::endl;
        return 1;
    }

    std::string line;
    std::regex pattern_a("Button A: X\\+(-?\\d+), Y\\+(-?\\d+)");
    std::regex pattern_b("Button B: X\\+(-?\\d+), Y\\+(-?\\d+)");
    std::regex pattern_prize("Prize: X=(-?\\d+), Y=(-?\\d+)");
    int a_x, a_y, b_x, b_y, p_x, p_y;

    while (getline(infile, line)) {
        std::smatch match;
        if (regex_search(line, match, pattern_a)) {
            a_x = stoi(match[1]);
            a_y = stoi(match[2]);
        } else if (regex_search(line, match, pattern_b)) {
            b_x = stoi(match[1]);
            b_y = stoi(match[2]);
        } else if (regex_search(line, match, pattern_prize)) {
            p_x = stoi(match[1]);
            p_y = stoi(match[2]);
            data.emplace_back(a_x, a_y, b_x, b_y, p_x, p_y);
        }
    }

    infile.close();
    std::array<u_int64_t, 2> result = {0,0};
    for (const auto& [ax, ay, bx, by, px,py] : data) {
        std::array<std::array<double, 2>, 2> A = {{{static_cast<double>(ax), static_cast<double>(bx)},
                                                  {static_cast<double>(ay), static_cast<double>(by)}}};

        const double detA = determinant(A);
        if (detA != 0) {
            for (int i = 0; i < 2; i++) {
                double x = i == 0 ? 0 : 1e13;
                std::array<std::array<double, 2>, 2> B = {
                    {
                        {static_cast<double>(px + x), static_cast<double>(bx)},
                        {static_cast<double>(py + x), static_cast<double>(by)}
                    }};

                std::array<std::array<double, 2>, 2> C = {
                    {
                        {static_cast<double>(ax), static_cast<double>(px + x)},
                        {static_cast<double>(ay), static_cast<double>(py + x)}
                    }};

                double t = determinant(B) / detA;
                double u = determinant(C) / detA;

                if (t <= 0 || u <= 0 || std::abs(t - std::round(t)) > 0.01 || std::abs(u - std::round(u)) > 0.01) {
                } else {
                    result[i] += static_cast<u_int64_t>(std::round(t)) * 3 + static_cast<u_int64_t>(std::round(u));
                }
            }
        }
    }

    std::cout << result[0] << std::endl;
    std::cout << result[1] << std::endl;


    return 0;
}
