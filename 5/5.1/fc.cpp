/*
  ID: blacksk2
  TASK: fc
  LANG: C++11
*/
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <utility>
#include <vector>

using Point = std::pair<double, double>;

std::vector<int> convex_hull(std::vector<Point> &points) {
  std::vector<int> ch;
  auto signed_area = [&](int i, int j, int k) {
    return (points[j].first - points[i].first) *
               (points[k].second - points[i].second) -
           (points[j].second - points[i].second) *
               (points[k].first - points[i].first);
  };
  auto half_ch = [&](int a, int b, int s) {
    for (int i = a; i != b; i += s) {
      while (ch.size() > 1 &&
             signed_area(ch[ch.size() - 2], ch[ch.size() - 1], i) < 0) {
        ch.pop_back();
      }
      ch.push_back(i);
    }
  };

  std::sort(points.begin(), points.end());
  half_ch(0, points.size(), 1);
  half_ch(points.size() - 2, -1, -1);
  return ch;
}

int main() {
  std::ifstream fin("fc.in");
  std::ofstream fout("fc.out");

  int n;
  fin >> n;

  std::vector<Point> points(n);
  for (auto &p : points) {
    fin >> p.first >> p.second;
  }
  std::vector<int> ch = convex_hull(points);

  double total_dist = 0;
  auto square = [](double x) -> double { return x * x; };
  auto dist = [&](int i, int j) -> double {
    return std::sqrt(square(points[ch[i]].first - points[ch[j]].first) +
                     square(points[ch[i]].second - points[ch[j]].second));
  };

  for (int i = 0; i + 1 < ch.size(); ++i) {
    total_dist += dist(i, i + 1);
  }
  fout << std::fixed << std::setprecision(2) << total_dist << std::endl;

  return 0;
}