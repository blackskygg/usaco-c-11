/*
  ID: blacksk2
  TASK: ditch
  LANG: C++11
*/
#include <algorithm>
#include <fstream>
#include <queue>
#include <vector>

const int INF = 1e9;

struct PointFlow {
  int no;
  int flow;

  PointFlow(int no, int flow) : no(no), flow(flow) {}
};

bool operator<(const PointFlow &lhs, const PointFlow &rhs) {
  return lhs.flow < rhs.flow;
}

int main() {
  std::ifstream fin("ditch.in");
  std::ofstream fout("ditch.out");

  int n, m, t;
  fin >> n >> m;
  t = m - 1;

  /* remove reverse-parallel edges */
  std::vector<std::vector<bool>> has_edge(m, std::vector<bool>(m, false));
  std::vector<std::vector<int>> edges;
  for (int i = 0; i < n; ++i) {
    int s, t, f;
    fin >> s >> t >> f;
    if (!has_edge[s - 1][t - 1]) {
      has_edge[s - 1][t - 1] = true;
      edges.push_back(std::vector<int>({s - 1, t - 1, f}));
    } else {
      edges.push_back(std::vector<int>({s - 1, m, f}));
      edges.push_back(std::vector<int>({m, t - 1, f}));
      m++;
    }
  }

  /* build res graph */
  std::vector<std::vector<int>> flow(m, std::vector<int>(m, 0));
  std::vector<std::vector<int>> adj(m);
  for (const auto &edge : edges) {
    if (flow[edge[0]][edge[1]] == 0) {
      adj[edge[0]].push_back(edge[1]);
      adj[edge[1]].push_back(edge[0]);
    }
    flow[edge[0]][edge[1]] += edge[2];
  }

  /* EK with Dijkstra */
  int total_flow = 0;
  for (;;) {
    std::vector<int> p(m, 0);
    std::vector<int> closed(m, false);
    std::vector<int> delta(m, 0);
    std::priority_queue<PointFlow> que;

    que.emplace(0, INF);
    delta[0] = INF;
    while (!que.empty()) {
      auto u = que.top();
      que.pop();
      if (closed[u.no])
        continue;

      closed[u.no] = true;
      if (u.no == t) {
        break;
      }

      for (int v : adj[u.no]) {
        if (closed[v] || flow[u.no][v] <= 0) {
          continue;
        }
        int new_delta = std::min(flow[u.no][v], u.flow);
        if (new_delta > delta[v]) {
          p[v] = u.no;
          delta[v] = new_delta;
          que.emplace(v, new_delta);
        }
      }
    }

    if (!delta[t]) {
      break;
    }

    int curr = t;
    while (curr != 0) {
      flow[p[curr]][curr] -= delta[t];
      flow[curr][p[curr]] += delta[t];
      curr = p[curr];
    }
    total_flow += delta[t];
  }

  fout << total_flow << std::endl;

  return 0;
}