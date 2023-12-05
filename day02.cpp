#include <filesystem>
#include <fmt/core.h>
#include <fstream>
#include <regex>
#include <string>

void day02(const char *base) {
  auto part1 = 0;
  {
    std::filesystem::path path = base;
    path /= "day02.txt";
    std::ifstream input(path);
    if (!input.is_open()) {
      fmt::print(stderr, "Cannot open input: {}\n", path.string());
      exit(1);
    }

    std::regex regex("([0-9]*) (red|green|blue)");
    auto max_red = 12;
    auto max_green = 13;
    auto max_blue = 14;
    std::string line;
    auto game = 0;
    while (std::getline(input, line)) {
      ++game;
      part1 += game;
      auto color_begin = std::sregex_iterator(line.begin(), line.end(), regex);
      auto color_end = std::sregex_iterator();
      for (std::sregex_iterator i = color_begin; i != color_end; ++i) {
        std::smatch match = *i;
        auto num = stoi(match[1]);
        if ((match[2] == "red" && max_red < num) ||
            (match[2] == "green" && max_green < num) ||
            (match[2] == "blue" && max_blue < num)) {
          part1 -= game;
          break;
        }
      }
    }
  }

  auto part2 = 0;
  {
    std::filesystem::path path = base;
    path /= "day02.txt";
    std::ifstream input(path);
    if (!input.is_open()) {
      fmt::print(stderr, "Cannot open input: {}\n", path.string());
      exit(1);
    }

    std::regex regex("([0-9]*) (red|green|blue)");
    std::string line;
    auto game = 0;
    while (std::getline(input, line)) {
      ++game;
      auto red = 0;
      auto green = 0;
      auto blue = 0;
      auto color_begin = std::sregex_iterator(line.begin(), line.end(), regex);
      auto color_end = std::sregex_iterator();
      for (std::sregex_iterator i = color_begin; i != color_end; ++i) {
        std::smatch match = *i;
        auto num = stoi(match[1]);
        if (match[2] == "red") {
          red = std::max(red, num);
        } else if (match[2] == "blue") {
          blue = std::max(blue, num);
        } else if (match[2] == "green") {
          green = std::max(green, num);
        }
      }
      part2 += red * blue * green;
    }
  }

  fmt::print("Day02: {} {}\n", part1, part2);
}
