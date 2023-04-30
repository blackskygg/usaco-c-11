/*
  ID: blacksk2
  TASK: window
  LANG: C++11
*/

#include <fstream>
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <list>
#include <iomanip>

struct Window {
  int x1, y1, x2, y2;

  void Normalize() {
    if (x1 > x2) std::swap(x1, x2);
    if (y1 > y2) std::swap(y1, y2);
  }
};

using Handle = std::list<Window>::iterator;

void sort_and_unique(std::vector<int>& v) {
  std::sort(v.begin(), v.end());
  v.erase(std::unique(v.begin(), v.end()), v.end());
}

double calc_percentage(const std::list<Window>& windows,
                       const Handle handle) {
  std::vector<int> xs, ys;
  for (Handle it = handle; it != windows.end(); ++it) {
    xs.push_back(it->x1);
    xs.push_back(it->x2);
    ys.push_back(it->y1);
    ys.push_back(it->y2);
  }
  sort_and_unique(xs);
  sort_and_unique(ys);

  std::unordered_map<int, int> x2i, y2i;
  for (int i = 0; i < xs.size(); ++i) {
    x2i[xs[i]] = i;
  }
  for (int i = 0; i < ys.size(); ++i) {
    y2i[ys[i]] = i;
  }

  std::vector<std::vector<int>> cnt(xs.size(), std::vector<int>(ys.size()));
  for (Handle it = std::next(handle); it != windows.end(); ++it) {
    // Line-by-line scaning.
    for (int i = x2i[it->x1]; i < x2i[it->x2]; ++i) {
      // Record start and leave point.
      cnt[i][y2i[it->y1]]++;
      cnt[i][y2i[it->y2]]--;
    }
  }


  double total = 0, clear = 0;
  for (int i = x2i[handle->x1]; i < x2i[handle->x2]; ++i) {
    for (int j = 0; j+1 < ys.size(); ++j) {
      // Compute accumulated cnt from start/leave ponits.
      if (j > 0) cnt[i][j] += cnt[i][j-1];
      // Out of range.
      if (j < y2i[handle->y1] || j >= y2i[handle->y2]) continue;
      int area = (xs[i+1]-xs[i]) * (ys[j+1]-ys[j]);
      total += area;
      if (cnt[i][j] == 0) clear += area;
    }
  }
  return clear * 100 / total;
}

int main() {
  std::ifstream fin("window.in");
  std::ofstream fout("window.out");
  fout.precision(3);
  fout << std::fixed;

  std::list<Window> windows;
  std::unordered_map<char, Handle> handles;

  std::string line;
  while (std::getline(fin, line)) {
    char id = line[2];
    switch (line[0]) {
      case 'w': {
        Window w;
        std::sscanf(line.c_str(), "w(%*c,%d,%d,%d,%d)", &w.x1, &w.y1, &w.x2, &w.y2);
        w.Normalize();
        windows.push_back(w);
        handles[id] = std::prev(windows.end());
        break;
      }
      case 't':
        windows.splice(windows.end(), windows, handles[id]);
        break;
      case 'b':
        windows.splice(windows.begin(), windows, handles[id]);
        break;
      case 'd':
        windows.erase(handles[id]);
        handles.erase(id);
        break;
      case 's':
        fout << calc_percentage(windows, handles[id]) << std::endl;
        break;
      default: break;
    }
  }

  return 0;
}
