/*
  ID: blacksk2
  TASK: milk6
  LANG: C++11
*/

#include <algorithm>
#include <fstream>
#include <queue>
#include <unordered_set>
#include <vector>

static const int INF = 1e9;

struct Edge {
  int from;
  int to;
  int cap;
  int flow;

  Edge(int from, int to, int cap, int flow)
      : from(from), to(to), cap(cap), flow(flow) {}
};

int EK(const std::vector<std::vector<int>> &adj, std::vector<Edge> &edges) {
  const int n = adj.size();
  int max_flow = 0;
  for (;;) {
    std::priority_queue<std::pair<int, int>> que; // flow, id
    std::vector<int> flow(n, 0), pe(n, -1);
    std::vector<bool> closed(n, false);

    flow[0] = INF;
    que.emplace(INF, 0);
    while (!que.empty()) {
      int u = que.top().second;
      que.pop();
      if (closed[u]) {
        continue;
      }
      closed[u] = true;

      for (const int ei : adj[u]) {
        const auto &e = edges[ei];
        if (e.flow == e.cap) {
          continue;
        }
        int v = e.to, vflow = std::min(flow[u], e.cap - e.flow);
        if (vflow > flow[v]) {
          pe[v] = ei;
          flow[v] = vflow;
          que.emplace(vflow, v);
        }
      }
    }

    int delta = flow[n - 1];
    if (delta == 0) {
      break;
    }

    int u = n - 1;
    while (pe[u] != -1) {
      int ei = pe[u];
      edges[ei].flow += delta;
      edges[ei ^ 1].flow -= delta;
      u = edges[ei].from;
    }
    max_flow += delta;
  }

  return max_flow;
}

// TODO: the following algo comes from my intuition, formal proof needed:
//   1. Find first cut set by doing DFS through the residual graph.
//   2. See if the cut set is better the the existing one (if any).
//   3. Add all the edges in the cut set to the residual graph.
//   4. goto 1 util there's no cut left.
std::vector<int> get_mincut(const std::vector<std::vector<int>> &adj,
                            const std::vector<Edge> &edges) {
  std::vector<int> mincut;
  std::vector<bool> allowd(edges.size(), false);
  for (;;) {
    std::vector<bool> vis(adj.size(), 0);
    std::queue<int> que;
    vis[0] = true;
    que.push(0);
    while (!que.empty()) {
      int u = que.front();
      que.pop();

      for (const int ei : adj[u]) {
        const auto &e = edges[ei];
        int v = e.to;
        if (!vis[v] && (e.cap > e.flow || allowd[ei])) {
          vis[v] = true;
          que.push(v);
        }
      }
    }
    if (vis[adj.size() - 1]) {
      break;
    }

    std::vector<int> cut;
    for (int i = 0; i < edges.size(); i += 2) {
      const auto &e = edges[i];
      if (vis[e.from] && !vis[e.to]) {
        cut.push_back(i);
      }
    }
    if (cut.empty()) {
      break;
    }
    std::sort(cut.begin(), cut.end());
    if (mincut.empty()) {
      mincut = cut;
    } else if (cut.size() != mincut.size()) {
      if (cut.size() < mincut.size()) {
        mincut = cut;
      }
    } else {
      bool new_min = false;
      for (int i = 0; i < cut.size(); ++i) {
        if (cut[i] != mincut[i]) {
          new_min = cut[i] < mincut[i];
          break;
        }
      }
      if (new_min) {
        mincut = cut;
      }
    }
    for (const int ei : cut) {
      allowd[ei] = true;
    }
  }

  return mincut;
}

int main() {
  std::ifstream fin("milk6.in");
  std::ofstream fout("milk6.out");

  int n, m;
  fin >> n >> m;

  std::vector<Edge> edges;
  std::vector<std::vector<int>> adj(n);
  for (int i = 1; i <= m; ++i) {
    int s, t, w;
    fin >> s >> t >> w;
    s--;
    t--;
    edges.emplace_back(s, t, w, 0);
    adj[s].push_back(edges.size() - 1);
    edges.emplace_back(t, s, 0, 0);
    adj[t].push_back(edges.size() - 1);
  }

  int max_flow = EK(adj, edges);
  auto mincut = get_mincut(adj, edges);

  fout << max_flow << " " << mincut.size() << std::endl;
  for (const int ei : mincut) {
    fout << ei / 2 + 1 << std::endl;
  }
  return 0;
}