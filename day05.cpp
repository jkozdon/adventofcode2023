#include <filesystem>
#include <fmt/core.h>
#include <fstream>
#include <map>
#include <regex>
#include <set>
#include <string>

int64_t day05_1(const char *base) {
  std::filesystem::path path = base;
  path /= "day05.txt";
  std::ifstream input(path);
  if (!input.is_open()) {
    fmt::print(stderr, "Cannot open input: {}\n", path.string());
    exit(1);
  }

  std::string line;

  auto part2 = 0;
  using I = int64_t;
  std::set<I> data;

  std::regex num_regex("[0-9]+");

  std::getline(input, line);

  auto num_begin = std::sregex_iterator(line.begin(), line.end(), num_regex);
  auto num_end = std::sregex_iterator();

  // seeds
  for (auto i = num_begin; i != num_end; ++i) {
    data.insert(stol((*i).str()));
  }
  std::getline(input, line);

  auto a2b = [&](auto a_in) {
    std::map<I, std::pair<I, I>> a2b_map;
    std::regex map_regex("([0-9]+) ([0-9]+) ([0-9]+)");
    std::getline(input, line); // empty
    std::getline(input, line); // header
    while (std::getline(input, line) && line.size() > 0) {
      std::smatch match;
      std::regex_search(line, match, map_regex);
      auto a = stol(match[2].str());
      auto b = stol(match[1].str());
      auto rng = stol(match[3].str());
      a2b_map[a] = {b, rng};
    }

    std::set<I> b_out;
    auto abr = a2b_map.begin();
    auto a = abr->first;
    auto b = abr->second.first;
    auto r = abr->second.second;
    for (auto x : a_in) {
      while (a + r < x) {
        ++abr;
        a = abr->first;
        b = abr->second.first;
        r = abr->second.second;
      }
      if (x >= a) {
        x = b + (x - a);
      }
      b_out.insert(x);
    }

    return b_out;
  };
  data = a2b(data);
  data = a2b(data);
  data = a2b(data);
  data = a2b(data);
  data = a2b(data);
  data = a2b(data);
  data = a2b(data);

  return *data.begin();
}

int64_t day05_2(const char *base) {
  std::filesystem::path path = base;
  path /= "day05.txt";
  std::ifstream input(path);
  if (!input.is_open()) {
    fmt::print(stderr, "Cannot open input: {}\n", path.string());
    exit(1);
  }

  std::string line;

  auto part2 = 0;
  using I = int64_t;
  std::map<I, I> data;

  std::regex num_regex("[0-9]+");

  std::getline(input, line);

  auto num_begin = std::sregex_iterator(line.begin(), line.end(), num_regex);
  auto num_end = std::sregex_iterator();

  // seeds
  for (auto i = num_begin; i != num_end; ++i) {
    auto a = stol((*(i++)).str());
    auto r = stol((*i).str());
    data[a] = r;
  }
  std::getline(input, line); // empty

  auto a2b = [&](auto a_in) {
    std::map<I, std::pair<I, I>> a2b_map;
    std::regex map_regex("([0-9]+) ([0-9]+) ([0-9]+)");
    std::getline(input, line); // header
    while (std::getline(input, line) && line.size() > 0) {
      std::smatch match;
      std::regex_search(line, match, map_regex);
      auto a = stol(match[2].str());
      auto b = stol(match[1].str());
      auto rng = stol(match[3].str());
      a2b_map[a] = {b, rng};
    }

    std::map<I, I> b_out;
    auto abr = a2b_map.begin();
    auto abr_end = a2b_map.end();
    auto r = abr->second.second;
    auto a0 = abr->first;
    auto a1 = a0 + r;
    auto b = abr->second.first;
    ++abr;
    for (auto x : a_in) {
      auto z = x.second;
      auto y0 = x.first;
      auto y1 = y0 + z;
      while (y0 < y1) {
        // beyond the end and done
        if (y0 >= a1 && abr == abr_end) {
          b_out[y0] = y1 - y0;
          y0 = y1;
          // beyond the end and not done
        } else if (y0 >= a1) {
          r = abr->second.second;
          a0 = abr->first;
          a1 = a0 + r;
          b = abr->second.first;
          ++abr;
          // part segment before so add this part and shift
        } else if (y0 < a0) {
          auto b0 = y0;
          auto b1 = std::min(a1, y1);
          b_out[b0] = b1 - b0;
          y0 = b1;
          // inside the segment
        } else {
          auto b0 = b + (y0 - a0);
          auto db = std::min(y1, a1) - y0;
          b_out[b0] = db;
          y0 += db;
        }
      }
    }

    return b_out;
  };
  data = a2b(data);
  data = a2b(data);
  data = a2b(data);
  data = a2b(data);
  data = a2b(data);
  data = a2b(data);
  data = a2b(data);

  return data.begin()->first;
}

void day05(const char *base) {
  auto part1 = day05_1(base);
  auto part2 = day05_2(base);
  fmt::print("Day05: {} {}\n", part1, part2);
}
