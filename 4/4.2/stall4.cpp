/*
  ID: blacksk2
  TASK: stall4
  LANG: C++11
*/
#include <algorithm>
#include <fstream>
#include <queue>
#include <vector>

const int INF = 2;

int main() {
  std::ifstream fin("stall4.in");
  std::ofstream fout("stall4.out");

  int n, m;
  fin >> n >> m;

  int N = n + m + 2; // source+sink+cow+barn
  int s = 0, t = N - 1;
  std::vector<std::vector<bool>> flow(N, std::vector<bool>(N, false));
  std::vector<std::vector<int>> adj(N);
  auto add_pair = [&](int x, int y) {
    adj[x].push_back(y);
    adj[y].push_back(x);
    flow[x][y] = true;
  };

  for (int i = 1; i <= n; ++i) {
    add_pair(s, i);
  }
  for (int i = 1; i <= m; ++i) {
    add_pair(n + i, t);
  }
  for (int i = 1; i <= n; ++i) {
    int s, b;
    fin >> s;
    while (s--) {
      fin >> b;
      add_pair(i, n + b);
    }
  }

  /* EK with BFS */
  int total_flow = 0;
  for (;;) {
    std::vector<bool> delta(N, false);
    std::vector<int> p(N, -1);
    std::queue<int> que;

    que.push(s);
    delta[s] = true;
    while (!que.empty() && !delta[t]) {
      int u = que.front();
      que.pop();

      for (auto v : adj[u]) {
        if (!delta[v] && flow[u][v]) {
          p[v] = u;
          delta[v] = true;
          que.push(v);
        }
      }
    }

    if (!delta[t]) {
      break;
    }

    int curr = t;
    while (curr != s) {
      flow[p[curr]][curr] = false;
      flow[curr][p[curr]] = true;
      curr = p[curr];
    }
    total_flow++;
  }

  fout << total_flow << std::endl;

  return 0;
}