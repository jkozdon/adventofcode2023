#include <filesystem>
#include <fmt/core.h>
#include <fstream>
#include <regex>
#include <string>

void day06(const char *base) {
  std::filesystem::path path = base;
  path /= "day06.txt";
  std::ifstream input(path);
  if (!input.is_open()) {
    fmt::print(stderr, "Cannot open input: {}\n", path.string());
    exit(1);
  }

  std::string line;
  std::regex num_regex("[0-9]+");
  std::getline(input, line);
  auto num_begin = std::sregex_iterator(line.begin(), line.end(), num_regex);
  auto num_end = std::sregex_iterator();
  std::vector<int64_t> time;
  for (auto i = num_begin; i != num_end; ++i) {
    time.push_back(stol((*i).str()));
  }
  std::getline(input, line);
  num_begin = std::sregex_iterator(line.begin(), line.end(), num_regex);
  num_end = std::sregex_iterator();
  std::vector<int64_t> dist;
  for (auto i = num_begin; i != num_end; ++i) {
    dist.push_back(stol((*i).str()));
  }

  int64_t part1 = 0;
  int64_t part2 = 0;

  fmt::print("Day06: {} {}\n", part1, part2);
}
