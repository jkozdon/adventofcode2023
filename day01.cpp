#include <cstdint>
#include <filesystem>
#include <fmt/core.h>
#include <fstream>
#include <sstream>
#include <string>

void day01(const char *base) {
  std::filesystem::path path = base;
  path /= "day01.txt";
  std::ifstream input(path);
  if (!input.is_open()) {
    fmt::print(stderr, "Cannot open input: {}\n", path.string());
    exit(1);
  }

  std::string line;
  while (std::getline(input, line)) {
    int32_t val;
    std::istringstream(line) >> val;
  }
}
