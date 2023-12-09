#include <filesystem>
#include <fmt/core.h>
#include <fstream>
#include <regex>
#include <unordered_map>

void day08(const char *base) {
  std::filesystem::path path = base;
  path /= "day08.txt";
  std::ifstream input(path);
  if (!input.is_open()) {
    fmt::print(stderr, "Cannot open input: {}\n", path.string());
    exit(1);
  }

  std::unordered_map<std::string, std::pair<std::string, std::string>> graph;
  std::vector<std::string> nodes2;

  std::string steps;
  std::getline(input, steps);

  std::string line;
  std::getline(input, line);
  std::regex graph_regex("(.*) = \\((.*), (.*)\\)");
  while (std::getline(input, line)) {
    std::smatch match;
    std::regex_search(line, match, graph_regex);
    graph[match[1].str()] = {match[2].str(), match[3].str()};
    if (match[1].str()[2] == 'A') {
      nodes2.push_back(match[1].str());
    }
  }

  auto part1 = 0;
  auto i = 0;
  auto n = steps.size();
  // for(std::string node = "AAA"; node != "ZZZ";part1++)
  // {
  //   auto c = steps[i];
  //   i = (i+1) % n;
  //   node = c == 'L' ? graph[node].first : graph[node].second;
  // }

  i = 0;
  bool done = false;
  auto part2 = 0;
  while (!done) {
    auto c = steps[i];
    i = (i + 1) % n;
    done = true;
    for (auto &node : nodes2) {
      node = c == 'L' ? graph[node].first : graph[node].second;
      done = done && node[2] == 'Z';
    }
    part2 += 1;
  }

  fmt::print("Day08: {} {}\n", part1, part2);
}
