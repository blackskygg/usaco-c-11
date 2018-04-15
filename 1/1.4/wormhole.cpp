/*
ID: blacksk2
TASK: wormhole
LANG: C++11
*/
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;
using hole = std::pair<int, int>;

bool check_loop(const vector<int> &neighbor, vector<int> &pair) {
  vector<bool> visited(neighbor.size(), false), curr_visited(neighbor.size());

  for (int i = 0; i < neighbor.size(); ++i) {
    if (visited[i])
      continue;

    curr_visited.assign(neighbor.size(), false);

    int next = i;
    for (;;) {
      if (curr_visited[next])
        return true;
      visited[next] = curr_visited[next] = true;
      next = neighbor[pair[next]];
      if (next == -1)
        break;
    }
  }

  return false;
}

int solve(const vector<int> &neighbor, vector<bool> &visited, vector<int> &pair) {
  int cnt = 0;
  bool full = true;

  for (int i = 0; i < visited.size(); ++i) {
    if (visited[i])
      continue;
    visited[i] = true;
    full = false;
    for (int j = i+1; j < visited.size(); ++j) {
      if (visited[j])
        continue;
      visited[j] = true;
      pair[i] = j;
      pair[j] = i;
      cnt += solve(neighbor, visited, pair);
      visited[j] = false;
    }
    visited[i] = false;
    break;
  }

  if (full)
    return check_loop(neighbor, pair) ? 1 : 0;

  return cnt;
}

int main() {
  ifstream fin("wormhole.in");
  ofstream fout("wormhole.out");

  int n;
  vector<hole> holes;
  int x, y;

  fin >> n;
  for (int i = 0; i < n; ++i) {
    fin >> x >> y;
    holes.emplace_back(y, x);
  }
  sort(holes.begin(), holes.end());

  vector<int> neigbor(n, -1);

  for (int i = 0; i < holes.size()-1; ++i) {
    if (holes[i+1].first == holes[i].first)
      neigbor[i] = i+1;
  }

  vector<bool> visited(n, false);
  vector<int> pair(n);

  fout << solve(neigbor, visited, pair) << endl;

  return 0;
}
