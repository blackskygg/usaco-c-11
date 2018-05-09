/*
  ID: blacksk2
  TASK: cowtour
  LANG: C++11
*/
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;
using point = pair<double, double>;

#define square(x) ((x)*(x))
#define dist(p1, p2) sqrt(square(p1.first-p2.first) + square(p1.second-p2.second))
const double MAX = 1e20;

void dfs(int n, const vector<vector<double>> &adj, vector<bool> &vis, vector<int> &component) {
  if (vis[n])
    return;
  vis[n] = true;
  component.push_back(n);

  for (int i = 0; i < adj[n].size(); ++i) {
    if (adj[n][i] < MAX)
      dfs(i, adj, vis, component);
  }
}

int main () {
  ifstream fin("cowtour.in");
  ofstream fout("cowtour.out");

  int n;
  fin >> n;

  vector<point> pos(n);
  vector<vector<double>> adj(n, vector<double>(n, MAX));
  for (int i = 0; i < n; ++i)
    fin >> pos[i].first >> pos[i].second;
  string s;
  for (int i = 0; i < n; ++i) {
    fin >> s;
    adj[i][i] = 0;
    for (int j = 0; j < s.size(); ++j) {
      if (s[j] == '1')
        adj[i][j] = dist(pos[i], pos[j]);
    }
  }

  for (int k = 0; k < n; ++k)
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
        adj[i][j] = std::min(adj[i][k] + adj[k][j], adj[i][j]);

  vector<vector<int>> components;
  vector<bool> vis(n, false);
  for (int i = 0; i < n; ++i) {
    if (!vis[i]) {
      components.push_back(vector<int>());
      dfs(i, adj, vis, components.back());
    }
  }

  vector<double> furthest(n, 0), diameter(components.size(), 0);
  for (int i = 0; i < components.size(); ++i) {
    for (auto &na: components[i]) {
      for (auto &nb: components[i]) {
        furthest[na] = std::max(furthest[na], adj[na][nb]);
      }
      diameter[i] = std::max(diameter[i], furthest[na]);
    }
  }

  double ans = MAX;
  for (int i = 0; i < components.size()-1; ++i) {
    for (int j = i+1; j < components.size(); ++j) {
      for (auto &na: components[i]) {
        for (auto &nb: components[j]) {
          double new_dia = std::max(furthest[na]+dist(pos[na], pos[nb])+furthest[nb],
                                    std::max(diameter[i], diameter[j]));
          ans = std::min(ans, new_dia);
        }
      }
    }
  }

  fout << std::setprecision(6) << std::fixed << ans << endl;

  return 0;
}
