/*
  ID: blacksk2
  TASK: comehome
  LANG: C++11
*/
#include <fstream>
#include <algorithm>
#include <utility>
#include <vector>
#include <queue>

using namespace std;

const int INF = 1000000000;
const int N   = 26*2;

using point = std::pair<int, int>;

int main () {
  ifstream fin("comehome.in");
  ofstream fout("comehome.out");

  int P;
  fin >> P;

  vector<vector<int>> adj(N, vector<int>(N, INF));
  char src, dst;
  int len;
  auto id = [] (int c) {
    if (isupper(c))
      return c-'A'+26;
    else
      return c-'a';
  };
  while (P--) {
    fin >> src >> dst >> len;
    src = id(src);
    dst = id(dst);
    if (src == dst)
      continue;
    adj[src][dst] = adj[dst][src] = std::min(adj[src][dst], len);
  }

  auto sp = vector<int>(N, INF);
  auto point_less = [] (const point &a, const point &b) { return a.second > b.second; };
  priority_queue<point, vector<point>, decltype(point_less)> que(point_less);
  vector<bool> set(N, false);
  int barn = N-1;

  sp[barn] = 0;
  que.emplace(barn, 0);
  while (!que.empty()) {
    int curr = que.top().first;
    que.pop();
    if (set[curr])
      continue;
    set[curr] = true;

    for (int i = 0; i < N; ++i) {
      if (set[i] || adj[curr][i] == INF)
        continue;
      if (sp[curr]+adj[curr][i] < sp[i]) {
        sp[i] = sp[curr]+adj[curr][i];
        que.emplace(i, sp[i]);
      }
    }
  }

  int minsp = INF, bestp = -1;
  for (int i = 26; i < barn; ++i) {
    if (sp[i] < minsp) {
      minsp = sp[i];
      bestp = i;
    }
  }

  fout << (char)(bestp-26+'A') << " " << minsp << endl;

  return 0;
}
