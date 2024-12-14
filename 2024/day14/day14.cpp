#include <array>
#include <fstream>
#include <iostream>
#include <regex>
#include <set>
#include <unistd.h>

struct Robot {
  std::pair<int, int> starting_position;
  std::pair<int, int> velocity;
};

int main() {
  std::ifstream file("input.txt");
  if (!file.is_open()) {
    std::cerr << "Failed to open file" << std::endl;
    return -1;
  }

  std::regex regex("p=(\\d+),(\\d+) v=(-?\\d+),(-?\\d+)");
  std::string line;
  std::vector<Robot> robots;

  while (std::getline(file, line)) {
    std::smatch match;
    if (std::regex_search(line, match, regex)) {
      int starting_position_x = std::stoi(match[1].str());
      int starting_position_y = std::stoi(match[2].str());
      int velocity_x = std::stoi(match[3].str());
      int velocity_y = std::stoi(match[4].str());
      robots.push_back(Robot{{starting_position_x, starting_position_y},{velocity_x,velocity_y}});
    }
  }
  file.close();

  std::array<int, 4> acc =  {0,0,0,0};
  for (Robot robot : robots) {
    int end_position_x = (robot.starting_position.first + 100 * robot.velocity.first) % 101;
    int end_position_y = (robot.starting_position.second + 100 * robot.velocity.second) % 103;

    if (end_position_x < 0) {
      end_position_x += 101;
    }
    if (end_position_y < 0) {
      end_position_y += 103;
    }

    if (end_position_x < 101 /2 && end_position_y < 103 / 2) {
      acc[0]++;
    } else if (end_position_x > 101 / 2 && end_position_y > 103 / 2) {
      acc[2]++;
    } else if (end_position_x < 101 / 2 && end_position_y > 103 / 2) {
      acc[1]++;
    } else if (end_position_x > 101 / 2 && end_position_y < 103 / 2) {
      acc[3]++;
    }
  }
  ino64_t result = 1;
  for (int i = 0; i < 4; i++) {
    result = result * acc[i];
  }
  std::cout << "The security factor is " << result << std::endl;

    std::vector<std::string> map;
    for (int j = 0; j < 103; ++j) {
      map.emplace_back(101,'.');
    }
    for (Robot robot : robots) {
      int64_t end_position_x = (robot.starting_position.first + 6620 * robot.velocity.first) % 101;
      int64_t end_position_y = (robot.starting_position.second + 6620 * robot.velocity.second) % 103;

      if (end_position_x < 0) {
        end_position_x += 101;
      }
      if (end_position_y < 0) {
        end_position_y += 103;
      }

      map[end_position_y][end_position_x] = '#';
    }
    std::cout << "Map at time " << 6620 <<std::endl;
    for (int j = 0; j < 103; j++) {
      std::cout << map[j] << std::endl;
    }

  return 0;
}
