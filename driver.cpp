#include <fmt/core.h>

#include "day01.cpp"
#include "day02.cpp"
#include "day03.cpp"

int main(int argc, char *argv[]) {
  if (argc < 2 || argc > 3) {
    fmt::print(stderr, "usage: {} base_path [day]\n", argv[0]);
    return 1;
  }

  char *base_path = argv[1];
  day01(base_path);
  day02(base_path);
  day03(base_path);
}
