#include <filesystem>
#include <fmt/core.h>

void day01(const char *base) {
  std::filesystem::path path = base;
  path /= "day01.txt";
}
