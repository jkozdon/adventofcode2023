#include <filesystem>
#include <fmt/core.h>
#include <fstream>
#include <regex>
#include <string>
#include <unordered_set>

void day04(const char *base) {
  std::filesystem::path path = base;
  path /= "day04.txt";
  std::ifstream input(path);
  if (!input.is_open()) {
    fmt::print(stderr, "Cannot open input: {}\n", path.string());
    exit(1);
  }

  std::string line;

  std::regex split_regex("^.*:(.*)\\|(.*)$");
  std::regex num_regex("[0-9]+");

  auto part1 = 0;

  auto part2 = 0;
  std::vector<int> cards;
  int game = 0;
  cards.push_back(1);
  while (std::getline(input, line)) {
    // build the winning number set
    std::unordered_set<int> winning_set;
    std::smatch match;
    std::regex_search(line, match, split_regex);
    auto win_str = match[1].str();
    auto win_begin =
        std::sregex_iterator(win_str.begin(), win_str.end(), num_regex);
    auto win_end = std::sregex_iterator();
    for (std::sregex_iterator i = win_begin; i != win_end; ++i) {
      auto num = stoi((*i).str());
      winning_set.insert(num);
    }

    // find the matches
    auto nums_str = match[2].str();
    auto num_begin =
        std::sregex_iterator(nums_str.begin(), nums_str.end(), num_regex);
    auto num_end = std::sregex_iterator();
    auto res1 = 1;
    auto res2 = 0;
    for (std::sregex_iterator i = num_begin; i != num_end; ++i) {
      auto num = stoi((*i).str());
      if (winning_set.contains(num)) {
        res1 *= 2;
        ++res2;
      }
    }
    res1 /= 2;
    part1 += res1;

    auto copies = cards[game];
    part2 += copies;
    ++game;
    while (cards.size() <= game + res2) {
      cards.push_back(1);
    }
    for (int i = 0; i < res2; ++i) {
      cards[game + i] += copies;
    }
  }

  fmt::print("Day04: {} {}\n", part1, part2);
}
