/*
  ID: blacksk2
  TASK: bigbrn
  LANG: C++11
*/

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

int solve(std::vector<std::vector<int>>& grid) {
  for (int i = 1; i < grid.size(); ++i) {
    for (int j = 0; j < grid[0].size(); ++j) {
      grid[i][j] += grid[i-1][j];
    }
  }

  int lo = 1, hi = grid.size();
  while (lo < hi) {
    int mid = (lo+hi+1) / 2;

    bool found = false;
    for (int up = 0, down = mid-1; down < grid.size(); ++up, ++down) {
      int prev_span = 0;
      for (int i = 0; i < grid.size(); ++i) {
        int curr = grid[down][i];
        if (up > 0) curr -= grid[up-1][i];
        if (curr == 0) {
          ++prev_span;
        } else {
          prev_span = 0;
        }
        if (prev_span >= mid) {
          found = true;
          break;
        }
      }
      if (found) break;
    }

    if (found) {
      lo = mid;
    } else {
      hi = mid-1;
    }
  }
  return lo;
}

int main() {
  std::ifstream fin("bigbrn.in");
  std::ofstream fout("bigbrn.out");

  int n, t;
  fin >> n >> t;

  std::vector<std::vector<int>> grid(n, std::vector<int>(n));
  for (int i = 0; i < t; ++i) {
    int x, y;
    fin >> x >> y;
    grid[x-1][y-1] = 1;
  }

  fout << solve(grid) << std::endl;

  return 0;
}
