/*
  ID: blacksk2
  TASK: race3
  LANG: C++11
*/
#include <algorithm>
#include <fstream>
#include <limits>
#include <queue>
#include <vector>

std::vector<std::vector<int>> get_neigh(std::ifstream &fin) {
  std::vector<std::vector<int>> neigh;
  bool end = false;
  for (int i = 0; !end; ++i) {
    neigh.push_back(std::vector<int>());
    for (;;) {
      int v;
      fin >> v;
      if (v < 0) {
        if (v == -1) {
          end = true;
        }
        break;
      } else {
        neigh.back().push_back(v);
      }
    }
  }
  neigh.pop_back();
  return neigh;
}

bool reach_end(int u, const std::vector<std::vector<int>> &neigh, int taboo,
               std::vector<bool> &vis) {
  vis[u] = true;
  if (u == neigh.size() - 1) {
    return true;
  }
  for (const int v : neigh[u]) {
    if (vis[v] || v == taboo) {
      continue;
    }
    if (reach_end(v, neigh, taboo, vis)) {
      return true;
    }
  }
  return false;
}

std::vector<int> get_bridge_points(const std::vector<std::vector<int>> &neigh) {
  std::vector<int> res;
  for (int taboo = 1; taboo + 1 < neigh.size(); ++taboo) {
    std::vector<bool> vis(neigh.size());
    if (!reach_end(0, neigh, taboo, vis)) {
      res.push_back(taboo);
    }
  }
  return res;
}

bool color(int u, const std::vector<std::vector<int>> &neigh, int c, int t,
           std::vector<int> &vis) {
  vis[u] = c;
  if (u == t) {
    return true;
  }
  for (const int v : neigh[u]) {
    if (vis[v] != -1) {
      if (vis[v] != c) {
        return false;
      }
    } else {
      if (!color(v, neigh, c, t, vis)) {
        return false;
      }
    }
  }
  return true;
}

std::vector<int> get_split_points(const std::vector<std::vector<int>> &neigh,
                                  const std::vector<int> &candidates) {
  std::vector<int> res;
  for (const auto u : candidates) {
    std::vector<int> vis(neigh.size(), -1);
    color(0, neigh, 0, u, vis);
    if (color(u, neigh, 1, neigh.size() - 1, vis)) {
      res.push_back(u);
    }
  }
  return res;
}

void output_vector(const std::vector<int> &vec, std::ofstream &fout) {
  fout << vec.size();
  if (!vec.empty()) {
    fout << " " << vec[0];
  }
  for (int i = 1; i < vec.size(); ++i) {
    fout << " " << vec[i];
  }
  fout << std::endl;
}

int main() {
  std::ifstream fin("race3.in");
  std::ofstream fout("race3.out");

  auto neigh = get_neigh(fin);
  auto bridge_points = get_bridge_points(neigh);
  auto split_points = get_split_points(neigh, bridge_points);
  output_vector(bridge_points, fout);
  output_vector(split_points, fout);

  return 0;
}