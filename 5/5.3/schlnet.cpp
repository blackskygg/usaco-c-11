/*
  ID: blacksk2
  TASK: schlnet
  LANG: C++11
*/

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>


void dfs(int u, const std::vector<std::vector<int>>& g,
         std::vector<int>& vis, std::vector<int>* sorted = nullptr) {
  vis[u] = true;
  for (const auto v : g[u]) {
    if (vis[v]) continue;
    dfs(v, g, vis, sorted);
  }
  if (sorted != nullptr) sorted->push_back(u);
}


std::vector<int> topo_sort(const std::vector<std::vector<int>>& g) {
  std::vector<int> sorted, vis(g.size());
  for (int i = 0; i < g.size(); ++i) {
    if (vis[i]) continue;
    dfs(i, g, vis, &sorted);
  }
  std::reverse(sorted.begin(), sorted.end());
  return sorted;
}

int solve_task1(const std::vector<std::vector<int>>& g,
                const std::vector<int>& topo) {
  int ans = 0;

  std::vector<int> vis(g.size());
  for (const auto u : topo) {
    if (vis[u]) continue;
    ++ans;
    dfs(u, g, vis);
  }

  return ans;
}

int solve_task2(const std::vector<std::vector<int>>& g,
                const std::vector<int>& topo) {
  std::vector<std::vector<int>> rg(g.size());
  for (int u = 0; u < g.size(); ++u) {
    for (const auto v : g[u]) {
      rg[v].push_back(u);
    }
  }

  std::vector<int> vis(g.size()), u2id(g.size(), -1);
  int comp_id = 0;
  for (const auto u : topo) {
    if (vis[u]) continue;
    std::vector<int> comp;
    dfs(u, rg, vis, &comp);
    for (const auto x : comp) {
      u2id[x] = comp_id;
    }
    ++comp_id;
  }
  if (comp_id == 1) return 0;

  std::vector<bool> is_end(comp_id, true), is_start(comp_id, true);
  for (int u = 0; u < g.size(); ++u) {
    const int u_id = u2id[u];
    for (const auto v : g[u]) {
      const int v_id = u2id[v];
      if (u_id != v_id) {
        is_end[u_id] = false;
        is_start[v_id] = false;
      }
    }
  }

  return std::max(
      std::count(is_end.begin(), is_end.end(), true),
      std::count(is_start.begin(), is_start.end(), true));
}


int main() {
  std::ifstream fin("schlnet.in");
  std::ofstream fout("schlnet.out");

  int n;
  fin >> n;

  std::vector<std::vector<int>> g(n);
  for (int i = 0; i < n; ++i) {
    int t;
    fin >> t;
    while (t != 0) {
      g[i].push_back(t-1);
      fin >> t;
    }
  }

  std::vector<int> topo = topo_sort(g);
  fout << solve_task1(g, topo) << std::endl;
  fout << solve_task2(g, topo) << std::endl;

  return 0;
}
