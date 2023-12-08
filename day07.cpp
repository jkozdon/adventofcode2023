#include <filesystem>
#include <fmt/core.h>
#include <fstream>
#include <map>
#include <ranges>
#include <regex>
#include <string>
#include <unordered_map>

void day07(const char *base) {
  std::filesystem::path path = base;
  path /= "day07.txt";
  std::ifstream input(path);
  if (!input.is_open()) {
    fmt::print(stderr, "Cannot open input: {}\n", path.string());
    exit(1);
  }
  enum Hand {
    high = 1,
    pair = 2,
    twopair = 3,
    threekind = 4,
    fullhouse = 5,
    fourkind = 6,
    fivekind = 7,
  };

  auto card2key = [](const char c, bool part2 = false) {
    switch (c) {
    case 'A':
      return 'n';
    case 'K':
      return 'm';
    case 'Q':
      return 'l';
    case 'J':
      return part2 ? 'J' : 'k';
    case 'T':
      return 'j';
    case '9':
      return 'i';
    case '8':
      return 'h';
    case '7':
      return 'g';
    case '6':
      return 'f';
    case '5':
      return 'e';
    case '4':
      return 'd';
    case '3':
      return 'c';
    case '2':
      return 'b';
    case '1':
      return 'a';
    }
    return 'X';
  };
  auto add_to_map = [](auto &map, auto c, auto &hand, auto &hand2) {
    (map.contains(c) && (map[c] += 1)) || ((map[c] = 1));
    switch (map[c]) {
    case 2:
      hand = hand == high ? pair : (hand == pair ? twopair : fullhouse);
      break;
    case 3:
      hand = hand == pair ? threekind : fullhouse;
      break;
    case 4:
      hand = fourkind;
      break;
    case 5:
      hand = fivekind;
      break;
    }
    if (c == 'J')
      return;
    switch (map[c]) {
    case 2:
      hand2 = hand2 == high ? pair : (hand2 == pair ? twopair : fullhouse);
      break;
    case 3:
      hand2 = hand2 == pair ? threekind : fullhouse;
      break;
    case 4:
      hand2 = fourkind;
      break;
    case 5:
      hand2 = fivekind;
      break;
    }
  };
  int64_t part1 = 0;
  std::map<std::string, int> cards_score;
  std::map<std::string, int> cards_score2;
  std::string line;
  while (std::getline(input, line)) {
    auto c0 = line[0];
    auto c1 = line[1];
    auto c2 = line[2];
    auto c3 = line[3];
    auto c4 = line[4];
    std::unordered_map<char, int> count;
    Hand hand = high;
    Hand hand2 = high;
    add_to_map(count, c0, hand, hand2);
    add_to_map(count, c1, hand, hand2);
    add_to_map(count, c2, hand, hand2);
    add_to_map(count, c3, hand, hand2);
    add_to_map(count, c4, hand, hand2);
    std::string key = {(char)(hand + '0'), card2key(c0), card2key(c1),
                       card2key(c2),       card2key(c3), card2key(c4)};
    cards_score[key] = std::stoi(line.c_str() + 6);

    if (count.contains('J')) {
      if (count['J'] == 5 || count['J'] == 4 ||
          (count['J'] == 3 && hand2 == pair) ||
          (count['J'] == 2 && hand2 == threekind) ||
          (count['J'] == 1 && hand2 == fourkind)) {
        hand2 = fivekind;
      } else if (count['J'] == 3 || (count['J'] == 2 && hand2 == pair) ||
                 (count['J'] == 1 && hand2 == threekind)) {
        hand2 = fourkind;
      } else if ((count['J'] == 2 && hand2 == pair) ||
                 (count['J'] == 1 && hand2 == twopair)) {
        hand2 = fullhouse;
      } else if ((count['J'] == 2 && hand2 == high) ||
                 (count['J'] == 1 && hand2 == pair)) {
        hand2 = threekind;
      } else if ((count['J'] == 1 && hand2 == high)) {
        hand2 = pair;
      } else {
        fmt::print("Missing case: {}\n", line);
      }
    }
    std::string key2 = {(char)(hand2 + '0'), card2key(c0, true),
                        card2key(c1, true),  card2key(c2, true),
                        card2key(c3, true),  card2key(c4, true)};
    cards_score2[key2] = std::stoi(line.c_str() + 6);
  }
  int count = 1;
  for (auto x : cards_score) {
    part1 += (count++) * x.second;
  }
  int count2 = 1;
  int64_t part2 = 0;
  for (auto x : cards_score2) {
    part2 += (count2++) * x.second;
  }

  fmt::print("Day07: {} {}\n", part1, part2);
}
