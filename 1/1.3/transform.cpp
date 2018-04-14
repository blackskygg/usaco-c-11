/*
ID: blacksk2
TASK: transform
LANG: C++11
*/

#include <fstream>
#include <vector>
#include <utility>
#include <functional>

using namespace std;
using point = std::pair<int, int>;

int main() {
  ifstream fin("transform.in");
  ofstream fout("transform.out");

  int n;
  fin >> n;

  vector<string> before(n), after(n);
  for (int i = 0; i < n; ++i)
    fin >> before[i];
  for (int i = 0; i < n; ++i)
    fin >> after[i];

  vector<std::function<point(const point &)>> trans= {
    [&] (const point &p) { return make_pair(p.second, n-1-p.first); },
    [&] (const point &p) { return make_pair(n-1-p.first, n-1-p.second); },
    [&] (const point &p) { return make_pair(n-1-p.second, p.first); },
    [&] (const point &p) { return make_pair(p.first, n-1-p.second);},
    [&] (const point &p) { return trans[3](trans[0](p)); },
    [&] (const point &p) { return trans[3](trans[1](p)); },
    [&] (const point &p) { return trans[3](trans[2](p)); },
    [&] (const point &p) { return make_pair(p.first, p.second); }
  };

  auto check_trans = [&] (std::function<point(const point &)> &f) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        auto fp = f(make_pair(i, j));
        if (before[i][j] != after[fp.first][fp.second])
          return false;
      }
    }
    return true;
  };

  for (int i = 0; i < 7; ++i) {
    if (check_trans(trans[i])) {
      if (i < 4)
        fout << i+1 << endl;
      else if (i < 7)
        fout << 5 << endl;
      else
        fout << 6 << endl;
      return 0;
    }
  }

  fout << 7 << endl;

  return 0;
}
