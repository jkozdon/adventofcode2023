#include <cstdint>
#include <filesystem>
#include <fmt/core.h>
#include <fstream>
#include <regex>
#include <sstream>
#include <string>

void day01(const char *base) {
  auto part1 = 0;
  {
    std::filesystem::path path = base;
    path /= "day01.txt";
    std::ifstream input(path);
    if (!input.is_open()) {
      fmt::print(stderr, "Cannot open input: {}\n", path.string());
      exit(1);
    }

    std::string line;
    while (std::getline(input, line)) {
      std::size_t first = line.find_first_of("1234567890");
      std::size_t last = line.find_last_of("1234567890");
      part1 += (line[first] - '0') * 10 + (line[last] - '0');
    }
  }

  /*
   */
  auto part2 = 0;
  {
    std::filesystem::path path = base;
    path /= "day01_2.txt";
    std::ifstream input(path);
    if (!input.is_open()) {
      path = base;
      path /= "day01.txt";
      input.open(path);
    }

    auto convert = [&](std::string digit) {
      if (digit == "1" || digit == "one") {
        return 1;
      } else if (digit == "2" || digit == "two") {
        return 2;
      } else if (digit == "3" || digit == "three") {
        return 3;
      } else if (digit == "4" || digit == "four") {
        return 4;
      } else if (digit == "5" || digit == "five") {
        return 5;
      } else if (digit == "6" || digit == "six") {
        return 6;
      } else if (digit == "7" || digit == "seven") {
        return 7;
      } else if (digit == "8" || digit == "eight") {
        return 8;
      } else if (digit == "9" || digit == "nine") {
        return 9;
      }
      return 0;
    };

    std::string line;
    std::regex start_regex(
        "([1-9]|one|two|three|four|five|six|seven|eight|nine)");
    std::regex end_regex(
        "^(.*)([1-9]|one|two|three|four|five|six|seven|eight|nine)");
    while (std::getline(input, line)) {
      std::smatch match;
      std::regex_search(line, match, start_regex);
      part2 += 10 * convert(match[1]);
      std::regex_search(line, match, end_regex);
      part2 += convert(match[2]);
    }
  }

  fmt::print("Day01: {} {}\n", part1, part2);
}
