/*
  ID: blacksk2
  TASK: frameup
  LANG: C++11
*/

#include <algorithm>
#include <fstream>
#include <set>
#include <vector>

static std::vector<std::vector<int>> ins, outs;
static std::vector<char> letters;

void get_ins(std::ifstream &fin) {
  int n, m;
  fin >> n >> m;

  std::vector<std::string> frame(n);
  for (auto &row : frame) {
    fin >> row;
  }

  letters.assign(26, -1);
  std::vector<int> ids(26, -1);
  std::vector<std::vector<int>> bounds; // (xmin, xmax, ymin, ymax)

  for (int x = 0; x < n; ++x) {
    for (int y = 0; y < m; ++y) {
      if (frame[x][y] == '.') {
        continue;
      }
      char c = frame[x][y] - 'A';
      if (ids[c] == -1) {
        ids[c] = bounds.size();
        letters[ids[c]] = frame[x][y];
        bounds.push_back({x, x, y, y});
      }
      auto &bound = bounds[ids[c]];
      bound[0] = std::min(bound[0], x);
      bound[1] = std::max(bound[1], x);
      bound[2] = std::min(bound[2], y);
      bound[3] = std::max(bound[3], y);
    }
  }

  ins.assign(bounds.size(), {});
  outs.assign(bounds.size(), {});
  for (int i = 0; i < bounds.size(); ++i) {
    const auto &bound = bounds[i];
    std::vector<bool> vis(bounds.size(), false);
    for (int x = bound[0]; x <= bound[1]; ++x) {
      for (int yi = 2; yi <= 3; ++yi) {
        int y = bound[yi], id = ids[frame[x][y] - 'A'];
        if (frame[x][y] != '.' && id != i) {
          vis[id] = true;
        }
      }
    }
    for (int y = bound[2]; y <= bound[3]; ++y) {
      for (int xi = 0; xi <= 1; ++xi) {
        int x = bound[xi], id = ids[frame[x][y] - 'A'];
        if (frame[x][y] != '.' && id != i) {
          vis[id] = true;
        }
      }
    }

    for (int c = 0; c <= bounds.size(); ++c) {
      if (vis[c]) {
        ins[i].push_back(c);
        outs[c].push_back(i);
      }
    }
  }
}

void dfs_out(std::vector<std::set<int>> &degree_map, std::vector<int> &degrees,
             std::vector<int> &curr, std::vector<std::string> &results) {
  if (degree_map[0].size() == 0) {
    results.emplace_back();
    for (auto it = curr.rbegin(); it != curr.rend(); ++it) {
      results.back().push_back(letters[*it]);
    }
    return;
  }

  std::vector<int> candidates;
  for (const int c : degree_map[0]) {
    candidates.push_back(c);
  }

  for (const int c : candidates) {
    curr.push_back(c);
    degree_map[0].erase(c);
    for (const int ch : outs[c]) {
      degree_map[degrees[ch]].erase(ch);
      degree_map[--degrees[ch]].insert(ch);
    }

    dfs_out(degree_map, degrees, curr, results);

    for (const int ch : outs[c]) {
      degree_map[degrees[ch]].erase(ch);
      degree_map[++degrees[ch]].insert(ch);
    }
    degree_map[0].insert(c);
    curr.pop_back();
  }
}

int main() {
  std::ifstream fin("frameup.in");
  std::ofstream fout("frameup.out");

  get_ins(fin);

  size_t max_in = 0;
  for (const auto &in : ins) {
    max_in = std::max(max_in, in.size());
  }

  std::vector<std::set<int>> degree_map(max_in + 1);
  std::vector<int> degrees(ins.size(), -1);
  std::vector<int> curr;
  std::vector<std::string> results;
  for (int i = 0; i < ins.size(); ++i) {
    degrees[i] = ins[i].size();
    degree_map[ins[i].size()].insert(i);
  }
  dfs_out(degree_map, degrees, curr, results);
  std::sort(results.begin(), results.end());
  for (const auto &r : results) {
    fout << r << std::endl;
  }

  return 0;
}