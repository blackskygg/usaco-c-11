/*
  ID: blacksk2
  TASK: ttwo
  LANG: C++11
*/
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

static bool visited[10][10][4][10][10][4]; // c.i c.j c.d f.i f.j f.d
static string map[10];

int main () {
  ifstream fin("ttwo.in");
  ofstream fout("ttwo.out");

  int pos[2][2]; // c,f i,j
  int dir[2] = {0, 0}; // c f : n e s w
  int pos_diff[4][2] = {{-1, 0}, {0, +1}, {+1, 0}, {0, -1}};

  for (int i = 0; i < 10; ++i) {
    getline(fin, map[i]);
    for (int j = 0; j < map[i].size(); ++j)
      if (map[i][j] == 'F') {
        pos[1][0] = i;
        pos[1][1] = j;
      } else if (map[i][j] == 'C') {
        pos[0][0] = i;
        pos[0][1] = j;
      }
  }

  auto is_good = [] (int i, int j) {
    return i >= 0 && i < 10 && j >= 0 && j < 10 && map[i][j] != '*';
  };

  visited[pos[0][0]][pos[0][1]][dir[0]][pos[1][0]][pos[1][1]][dir[1]] = true;
  for (int i = 1; i < 160000; ++i) {
    for (int r = 0; r < 2; ++r) {
      int new_pos[2];
      new_pos[0] = pos[r][0] + pos_diff[dir[r]][0];
      new_pos[1] = pos[r][1] + pos_diff[dir[r]][1];

      if (is_good(new_pos[0], new_pos[1])) {
        pos[r][0] = new_pos[0];
        pos[r][1] = new_pos[1];
      } else {
        dir[r] = (dir[r]+1) % 4;
      }
    }

    auto &vis = visited[pos[0][0]][pos[0][1]][dir[0]][pos[1][0]][pos[1][1]][dir[1]];
    if (vis)
      break;
    vis = true;
    if (pos[0][0] == pos[1][0] && pos[0][1] == pos[1][1]) {
      fout << i << endl;
      return 0;
    }
  }

  fout << 0 << endl;

  return 0;
}
