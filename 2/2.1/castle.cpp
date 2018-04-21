/*
  ID: blacksk2
  TASK: castle
  LANG: C++11
*/
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

#define HAS_W(x) ((x)&1)
#define HAS_N(x) ((x)&2)
#define HAS_E(x) ((x)&4)
#define HAS_S(x) ((x)&8)
#define OUT(x, y) ((x) < 0 || (x) >= castle.size()              \
                      || (y) < 0 || (y) >= castle[0].size())

vector<vector<int>> castle;
vector<vector<int>> component;
vector<int> comp_sizes;

void dfs(int x, int y) {
  if (OUT(x, y) || component[x][y] >= 0)
    return;

  component[x][y] = comp_sizes.size()-1;
  comp_sizes.back()++;

  int curr = castle[x][y];
  if (!HAS_W(curr))
    dfs(x, y-1);
  if (!HAS_E(curr))
    dfs(x, y+1);
  if (!HAS_N(curr))
    dfs(x-1, y);
  if (!HAS_S(curr))
    dfs(x+1, y);
}

int main() {
  ifstream fin("castle.in");
  ofstream fout("castle.out");

  int n, m;
  fin >> m >> n;
  castle.assign(n, vector<int>(m));
  component.assign(n, vector<int>(m, -1));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      fin >> castle[i][j];
    }
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (component[i][j] == -1) {
        comp_sizes.push_back(0);
        dfs(i, j);
      }
    }
  }

  int best_x=-1, best_y=m, best_dir=1, best_size = 0;
  auto update_max = [&] (int size, int x, int y, int dir) {
    best_size = size;
    best_x = x;
    best_y = y;
    best_dir = dir;
  };
  auto try_update = [&] (int x1, int y1, int dir) {
    int x2=x1, y2=y1;
    if (dir == 0) // NORTH
      x2--;
    else // EAST
      y2++;
    if (OUT(x2, y2))
      return;
    if (component[x1][y1] == component[x2][y2])
      return;
    int new_size = comp_sizes[component[x1][y1]]+comp_sizes[component[x2][y2]];
    if (new_size < best_size)
      return;
    if (new_size > best_size) {
      update_max(new_size, x1, y1, dir);
      return;
    }
    if (y1 > best_y)
      return;
    if (y1 < best_y)
      return update_max(new_size, x1, y1, dir);
    if (x1 < best_x)
      return;
    if (x1 > best_x) {
      update_max(new_size, x1, y1, dir);
      return;
    }
    if (dir > best_dir)
      return;
    update_max(new_size, x1, y1, dir);
  };
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (HAS_N(castle[i][j]))
        try_update(i, j, 0);
      if (HAS_E(castle[i][j]))
        try_update(i, j, 1);
    }
  }

  fout << comp_sizes.size() << endl;
  fout << *std::max_element(comp_sizes.begin(), comp_sizes.end()) << endl;
  fout << best_size << endl;
  fout << best_x+1 << " " << best_y+1 << " " << (best_dir?'E':'N') << endl;

  return 0;
}
