#include <filesystem>
#include <fmt/core.h>
#include <fstream>
#include <ranges>
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

  std::regex num_regex("[0-9]+");

  std::string time_line;
  std::getline(input, time_line);
  auto time_begin =
      std::sregex_iterator(time_line.begin(), time_line.end(), num_regex);
  auto time_end = std::sregex_iterator();

  std::string dist_line;
  std::getline(input, dist_line);
  auto dist_begin =
      std::sregex_iterator(dist_line.begin(), dist_line.end(), num_regex);
  auto dist_end = std::sregex_iterator();

  int64_t part1 = 1;
  auto dist = dist_begin;
  std::string time_p2 = "";
  std::string dist_p2 = "";
  for (auto time = time_begin; time != time_end; ++time, ++dist) {
    time_p2 += (*time).str();
    dist_p2 += (*dist).str();
    auto t = stol((*time).str());
    auto d = stol((*dist).str());
    int64_t bot = ceil((t - sqrt(t * t - 4 * d)) / 2);
    int64_t top = floor((t + sqrt(t * t - 4 * d)) / 2);
    if (bot * (t - bot) <= d)
      ++bot;
    if (top * (t - top) <= d)
      --top;
    part1 *= (top - bot + 1);
  }

  auto t = stol(time_p2);
  auto d = stol(dist_p2);
  int64_t bot = ceil((t - sqrt(t * t - 4 * d)) / 2);
  int64_t top = floor((t + sqrt(t * t - 4 * d)) / 2);
  if (bot * (t - bot) <= d)
    ++bot;
  if (top * (t - top) <= d)
    --top;
  auto part2 = (top - bot + 1);

  fmt::print("Day06: {} {}\n", part1, part2);
}
