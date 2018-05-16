/*
  ID: blacksk2
  TASK: butter
  LANG: C++11
*/
#include <fstream>
#include <algorithm>
#include <vector>
#include <limits>
#include <queue>

using namespace std;

const int INF = numeric_limits<int>::max();

struct edge {
  int to;
  int w;
};

pair<int, int> calc(int curr, const vector<vector<edge>> &sp_tree, const vector<int> &pcount) {
  int count = pcount[curr], len = 0;
  for (auto &e: sp_tree[curr]) {
    auto res = calc(e.to, sp_tree, pcount);
    count += res.second;
    len += res.first + res.second*e.w;
  }
  return {len, count};
}

int solve(int src, const vector<int> &pcount, const vector<vector<edge>> &graph) {
  int np = pcount.size();
  vector<vector<edge>> sp_tree(np);
  vector<int> d(np, INF), pai(np, -1), paid(np, -1);
  vector<bool> done(np, false);

  using que_item = std::pair<int, int>;
  auto cmp = [] (const que_item &a, const que_item &b) {
    return a.second > b.second;
  };

  priority_queue<que_item, vector<que_item>, decltype(cmp)> que(cmp);
  d[src] = 0;
  que.emplace(src, 0);
  while (!que.empty()) {
    auto top = que.top();
    que.pop();

    int curr = top.first;
    if (done[curr])
      continue;
    done[curr] = true;
    if (curr != src)
      sp_tree[pai[curr]].emplace_back((edge){curr, paid[curr]});

    for (auto &e: graph[curr]) {
      if (!done[e.to] && d[e.to] > d[curr]+e.w) {
        d[e.to] = d[curr]+e.w;
        pai[e.to] = curr;
        paid[e.to] = e.w;
        que.emplace(e.to, d[e.to]);
      }
    }
  }

  bool ok = true;
  for (int i = 0; i < np; ++i) {
    if (pcount[np] > 0 && d[np] == INF) {
      ok = false;
      break;
    }
  }

  if (ok)
    return calc(src, sp_tree, pcount).first;
  else
    return INF;
}

int main() {
  ifstream fin("butter.in");
  ofstream fout("butter.out");

  int n, p, c;
  fin >> n >> p >> c;

  vector<int> pcount(p, 0);
  for (int i = 0; i < n; ++i) {
    int t;
    fin >> t;
    pcount[t-1]++;
  }

  vector<vector<edge>> graph(p);
  for (int i = 0; i < c; ++i) {
    int f, t, w;
    fin >> f >> t >> w;
    f--;
    t--;
    graph[f].emplace_back((edge){t,w});
    graph[t].emplace_back((edge){f,w});
  }


  int r, ans = INF;
  for (int i = 0; i < p; ++i) {
    r = solve(i, pcount, graph);
    ans = std::min(ans, r);
  }

  fout << ans << endl;

  return 0;
}
