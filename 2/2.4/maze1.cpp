/*
  ID: blacksk2
  TASK: maze1
  LANG: C++11
*/
#include <fstream>
#include <algorithm>
#include <utility>
#include <vector>
#include <queue>

using namespace std;

int main () {
  ifstream fin("maze1.in");
  ofstream fout("maze1.out");

  int w, h;
  fin >> w >> h;

  fin.ignore(256, '\n');
  vector<string> maze(2*h+1);
  for (int i = 0; i < 2*h+1; ++i)
    getline(fin, maze[i]);

  // dir: 0 n, 1 e, 2 s, 3 w
  vector<pair<int, int>> pos_diff = {{-1, 0}, {0, +1}, {+1, 0}, {0, -1}};
  int exits[2][2], ne = 0;

  for (int i = 0; i < w; ++i) {
    if (maze[0][2*i+1] == ' ') {
      exits[ne][0] = 0;
      exits[ne][1] = i;
      ne++;
    }
    if (maze[2*h][2*i+1] == ' ') {
      exits[ne][0] = h-1;
      exits[ne][1] = i;
      ne++;
    }
  }
  for (int i = 0; i < h; ++i) {
    if (maze[2*i+1][0] == ' ') {
      exits[ne][0] = i;
      exits[ne][1] = 0;
      ne++;
    }
    if (maze[2*i+1][2*w] == ' ') {
      exits[ne][0] = i;
      exits[ne][1] = w-1;
      ne++;
    }
  }

  vector<vector<int>> spaths[2];
  spaths[0] = vector<vector<int>>(h, vector<int>(w, -1));
  spaths[1] = vector<vector<int>>(h, vector<int>(w, -1));

  for (int i = 0; i < 2; ++i) {
    queue<pair<int, int>> que;
    auto &sp = spaths[i];
    sp[exits[i][0]][exits[i][1]] = 0;
    que.emplace(exits[i][0], exits[i][1]);

    while (!que.empty()) {
      auto curr = que.front();
      que.pop();

      for (auto &diff: pos_diff) {
        auto edge = make_pair(curr.first*2+1+diff.first, curr.second*2+1+diff.second);
        if (maze[edge.first][edge.second] != ' ')
          continue;
        auto new_pos = make_pair(curr.first+diff.first, curr.second+diff.second);
        if (new_pos.first < 0 || new_pos.first >= h || new_pos.second < 0 || new_pos.second >= w)
          continue;
        if (sp[new_pos.first][new_pos.second] != -1)
          continue;
        sp[new_pos.first][new_pos.second] = sp[curr.first][curr.second]+1;
        que.push(new_pos);
      }
    }
  }

  pair<int, int> best_pos;
  int max_len = 0;
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      if (max_len <= std::min(spaths[0][i][j], spaths[1][i][j])) {
        best_pos = make_pair(i, j);
        max_len = std::min(spaths[0][i][j], spaths[1][i][j]);
      }
    }
  }

  fout << max_len+1 << endl;

  return 0;
}
