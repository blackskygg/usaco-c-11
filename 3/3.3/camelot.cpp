/*
  ID: blacksk2
  TASK: camelot
  LANG: C++11
*/
#include <fstream>
#include <algorithm>
#include <vector>
#include <limits>
#include <queue>

using namespace std;

#define MP(x, y) ((y)*C+(x))
#define X(n) ((n)%C)
#define Y(n) ((n)/C)
#define valid(x, y) ((x) >= 0 && (x) < C && (y) >= 0 && (y) < R)

const int INF = numeric_limits<int>::max();
int R, C;

struct queue_item {
  int has_king;
  int pos;
  int d;

  queue_item(int hk, int p, int d) : has_king(hk), pos(p), d(d) {}
  bool operator<(const queue_item &rhs) const {
    return this->d > rhs.d;
  }
};

void dijkstra(int s, vector<vector<int>> &dist, vector<int> &kdist) {
  const static vector<vector<int>> moves{
    {-1, +2}, {-1, -2}, {-2, +1}, {-2, -1},
    {+1, +2}, {+1, -2}, {+2, +1}, {+2, -1}};

  priority_queue<queue_item> q;
  static vector<vector<bool>> done(R*C);

  dist.assign(R*C, vector<int>(2, INF));
  done.assign(R*C, vector<bool>(2, false));

  q.emplace(0, s, 0);
  q.emplace(1, s, kdist[s]);
  while (!q.empty()) {
    auto curr = q.top();
    q.pop();

    if (done[curr.pos][curr.has_king])
      continue;
    done[curr.pos][curr.has_king] = true;
    dist[curr.pos][curr.has_king] = curr.d;

    int x = X(curr.pos), y = Y(curr.pos);
    for (auto &mv: moves) {
      int tx = x+mv[0], ty = y+mv[1], tp = MP(tx, ty);
      if (!valid(tx, ty))
        continue;
      if (curr.has_king == 0) {
        if (curr.d+1 < dist[tp][0]) {
          dist[tp][0] = curr.d+1;
          q.emplace(0, tp, dist[tp][0]);
        }
        if (curr.d+kdist[tp]+1 < dist[tp][1]+1) {
          dist[tp][1] = curr.d+kdist[tp]+1;
          q.emplace(1, tp, dist[tp][1]);
        }
      } else {
        if (curr.d+1 < dist[tp][1]) {
          dist[tp][1] = curr.d+1;
          q.emplace(1, tp, dist[tp][1]);
        }
      }
    }

  }

}

int main () {
  ifstream fin("camelot.in");
  ofstream fout("camelot.out");
  fin >> R >> C;

  char x;
  int y, kx, ky;

  fin >> x >> y;
  kx = x-'A';
  ky = y-1;

  vector<int> knights;
  while (fin >> x >> y)
    knights.push_back(MP(x-'A',y-1));

  vector<vector<int>> dist(R*C, vector<int>(2, INF));
  vector<int> total_dist(R*C, 0), kdist(R*C, INF), kdist_min(R*C, INF);

  for (int p = 0; p < R*C; ++p)
    kdist_min[p] = kdist[p] = max(abs(kx-X(p)), abs(ky-Y(p)));

  for (auto kn: knights) {
    dijkstra(kn, dist, kdist);
    for (int p = 0; p < R*C; ++p) {
      if (total_dist[p] == INF)
        continue;
      if (dist[p][0] == INF) {
        total_dist[p] = INF;
        continue;
      }
      total_dist[p] += dist[p][0];
      kdist_min[p] = std::min(kdist_min[p], dist[p][1]-dist[p][0]);
    }
  }

  int ans = INF;
  for (int p = 0; p < R*C; ++p) {
    if (total_dist[p] == INF)
      continue;
    ans = std::min(ans, total_dist[p]+kdist_min[p]);
  }
  fout << ans << endl;

  return 0;
}
