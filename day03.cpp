#include <filesystem>
#include <fmt/core.h>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

struct pair_hash {
  template <class T1, class T2>
  std::size_t operator()(const std::pair<T1, T2> &p) const {
    auto h1 = std::hash<T1>{}(p.first);
    auto h2 = std::hash<T2>{}(p.second);

    // Mainly for demonstration purposes, i.e. works but is overly simple
    // In the real world, use sth. like boost.hash_combine
    return h1 ^ h2;
  }
};

void day03(const char *base) {
  std::filesystem::path path = base;
  path /= "day03.txt";
  std::ifstream input(path);
  if (!input.is_open()) {
    fmt::print(stderr, "Cannot open input: {}\n", path.string());
    exit(1);
  }

  std::string line;
  int row = 0;
  int entry = 0;
  std::vector<std::pair<int, bool>> values;
  std::unordered_map<std::pair<int, int>, int, pair_hash> val_map;
  std::unordered_map<std::pair<int, int>, char, pair_hash> sym_map;
  while (std::getline(input, line)) {
    int num = 0;
    for (int col = 0; line[col]; ++col) {
      auto c = line[col];
      if ('0' <= c && c <= '9') {
        num = 10 * num + c - '0';
        val_map.insert({{row, col}, entry});
      } else {
        if (num != 0) {
          values.push_back({num, false});
          ++entry;
          num = 0;
        }
        if (c != '.') {
          sym_map.insert({{row, col}, c});
        }
      }
    }
    if (num != 0) {
      values.push_back({num, false});
      ++entry;
      num = 0;
    }
    ++row;
  }

  auto part1 = 0;
  for (auto [sym_loc, sym] : sym_map) {
    for (auto r = sym_loc.first - 1; r <= sym_loc.first + 1; ++r) {
      for (auto c = sym_loc.second - 1; c <= sym_loc.second + 1; ++c) {
        // if has neighbor
        if (val_map.contains({r, c})) {
          auto val_ind = val_map[{r, c}];
          // if not seen
          if (!values[val_ind].second) {
            part1 += values[val_ind].first;
            values[val_ind].second = true;
          }
        }
      }
    }
  }

  // Reset array
  for(auto &[val, chk]: values) {
    chk = false;
  }
  auto part2 = 0;
  for (auto [sym_loc, sym] : sym_map) {
    if (sym != '*') continue;
    std::array<int, 2> v = {0,0};
    int fnd = 0;
    for (auto r = sym_loc.first - 1; r <= sym_loc.first + 1; ++r) {
      for (auto c = sym_loc.second - 1; c <= sym_loc.second + 1; ++c) {
        // If has neighbor
        if (val_map.contains({r, c})) {
          auto val_ind = val_map[{r, c}];
          // If not seen
          if (!values[val_ind].second) {
            v[fnd++] = values[val_ind].first;
            values[val_ind].second = true;
          }
        }
      }
    }
    part2 += v[0] * v[1];
  }

  fmt::print("Day03: {} {}\n", part1, part2);
}
