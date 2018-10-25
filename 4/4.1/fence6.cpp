/*
  ID: blacksk2
  TASK: fence6
  LANG: C++11
*/
#include <algorithm>
#include <fstream>
#include <limits>
#include <unordered_map>
#include <unordered_set>
#include <vector>

const int INF = 255 * 200;

std::vector<std::vector<int>> adj;
std::vector<std::vector<int>> dist;
std::vector<std::vector<int>> graph;

int get_estimate(int prev, int curr, int goal) {
  int estimate = 2 * INF;
  for (auto ch : adj[curr]) {
    if (ch != prev) {
      estimate = std::min(dist[ch][goal] + graph[curr][ch], estimate);
    }
  }
  return estimate >= INF ? INF : estimate;
}

void search(int start, int prev, int curr, int length,
            std::unordered_set<int> &path, int &best) {
  path.insert(curr);
  length += graph[prev][curr];

  for (const auto ch : adj[curr]) {
    if (ch != prev && ch == start) {
      best = std::min(length + graph[curr][ch], best);
      continue;
    }
    if (!path.count(ch) && get_estimate(curr, ch, start) < best) {
      search(start, curr, ch, length, path, best);
    }
  }

  path.erase(curr);
}

uint64_t encode_edges(std::vector<int> &edges) {
  sort(edges.begin(), edges.end());

  uint64_t code = 0;
  for (const int e : edges) {
    code |= e;
    code <<= 7;
  }
  return code;
}

int get_overlap(const std::unordered_set<int> &a,
                const std::unordered_set<int> &b) {
  for (const auto &e : a) {
    if (b.count(e)) {
      return e;
    }
  }
  return -1;
}

int main() {
  std::ifstream fin("fence6.in");
  std::ofstream fout("fence6.out");

  int n;
  fin >> n;

  std::vector<int> lengths(n + 1);
  std::unordered_map<uint64_t, std::unordered_set<int>> edge_sets;
  for (int i = 0; i < n; ++i) {
    int e, n[2];
    fin >> e;
    fin >> lengths[e];
    fin >> n[0] >> n[1];
    for (int side = 0; side < 2; ++side) {
      std::vector<int> edge_vec(n[side] + 1, 0);
      for (int ne = 0; ne < n[side]; ++ne) {
        fin >> edge_vec[ne];
      }
      edge_vec[n[side]] = e;
      uint64_t code = encode_edges(edge_vec);
      if (!edge_sets.count(code)) {
        edge_sets[code] =
            std::unordered_set<int>(edge_vec.begin(), edge_vec.end());
      }
    }
  }

  std::vector<std::unordered_set<int>> points(edge_sets.size());
  for (auto &edge_set : edge_sets) {
    points.emplace_back(std::move(edge_set.second));
  }

  graph.assign(points.size(), std::vector<int>(points.size(), INF));
  adj.assign(points.size(), std::vector<int>());
  for (int i = 0; i + 1 < points.size(); ++i) {
    graph[i][i] = 0;
    for (int j = i + 1; j < points.size(); ++j) {
      int e = get_overlap(points[i], points[j]);
      if (e != -1) {
        adj[i].push_back(j);
        adj[j].push_back(i);
        graph[i][j] = graph[j][i] = lengths[e];
      }
    }
  }

  // Floyd
  dist = graph;
  for (int i = 0; i < points.size(); ++i) {
    for (int j = 0; j < points.size(); ++j) {
      for (int k = 0; k < points.size(); ++k) {
        dist[j][k] = std::min(dist[j][i] + dist[i][k], dist[j][k]);
      }
    }
  }

  int best = INF;
  std::unordered_set<int> path;
  for (int i = 0; i < points.size(); ++i) {
    path.insert(i);
    for (const auto ch : adj[i]) {
      if (dist[i][ch] + get_estimate(i, ch, i) < best) {
        search(i, i, ch, 0, path, best);
      }
    }
    path.clear();
  }
  fout << best << std::endl;

  return 0;
}