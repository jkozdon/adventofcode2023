#include <filesystem>
#include <fmt/core.h>
#include <string>

#include "day01.cpp"

int main(int argc, char *argv[]) {
  if (argc < 2 || argc > 3) {
    fmt::print(stderr, "usage: {} base_path [day]\n", argv[0]);
    return 1;
  }

  char *base_path = argv[1];
  day01(base_path);
}
