/*
  ID: blacksk2
  TASK: snail
  LANG: C++11
*/

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct Dir {
  int dx;
  int dy;
  int next[2];
};

const static std::vector<Dir> dirs = {{.dx = 1, .dy = 0, .next = {1, 3}},
                                      {.dx = 0, .dy = 1, .next = {0, 2}},
                                      {.dx = -1, .dy = 0, .next = {1, 3}},
                                      {.dx = 0, .dy = -1, .next = {0, 2}}};
static std::vector<std::string> map;

int search(int x, int y, int dirno, int steps) {
  const Dir &dir = dirs[dirno];
  const int n = map.size();

  auto is_valid = [&](int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < n;
  };

  int tx = x, ty = y;
  while (is_valid(tx, ty) && map[tx][ty] == '.') {
    map[tx][ty] = 'x';
    tx += dir.dx;
    ty += dir.dy;
    steps++;
  }

  int max_steps = steps;
  if (!is_valid(tx, ty) || map[tx][ty] == '#') {
    for (int i = 0; i < 2; ++i) {
      const Dir &next_dir = dirs[dir.next[i]];
      int nx = tx - dir.dx + next_dir.dx, ny = ty - dir.dy + next_dir.dy;
      if (is_valid(nx, ny) && map[nx][ny] == '.') {
        max_steps = std::max(max_steps, search(nx, ny, dir.next[i], steps));
      }
    }
  }

  while (tx != x || ty != y) {
    tx -= dir.dx;
    ty -= dir.dy;
    map[tx][ty] = '.';
  }

  return max_steps;
}

int main() {
  std::ifstream fin("snail.in");
  std::ofstream fout("snail.out");

  int n, b;
  fin >> n >> b;
  map.assign(n, std::string(n, '.'));

  for (int i = 0; i < b; ++i) {
    std::string s;
    fin >> s;
    int c = s[0] - 'A', r = std::stoi(s.substr(1)) - 1;
    map[r][c] = '#';
  }

  fout << std::max(search(0, 0, 0, 0), search(0, 0, 1, 0)) << std::endl;

  return 0;
}
