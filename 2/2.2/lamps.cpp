/*
  ID: blacksk2
  TASK: lamps
  LANG: C++11
*/
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

int c, n;
vector<int> ons, offs;
vector<vector<int>> ans;

void check(const vector<int> &pressed) {
  int np = count_if(pressed.begin(), pressed.end(),
                    [](int x) { return x == 1; });
  if (c < np || (c-np)%2 == 1)
    return;

  vector<int> stat(n, 1);
  if (pressed[0]) {
    for (int i = 1; i <= n; i+=1)
      stat[i-1] = 1-stat[i-1];
  }
  if (pressed[1]) {
    for (int i = 1; i <= n; i+=2)
      stat[i-1] = 1-stat[i-1];
  }
  if (pressed[2]) {
    for (int i = 2; i <= n; i+=2)
      stat[i-1] = 1-stat[i-1];
  }
  if (pressed[3]) {
    for (int i = 1; i <= n; i+=3)
      stat[i-1] = 1-stat[i-1];
  }

  for (auto &on: ons) {
    if (stat[on-1] == 0)
      return;
  }
  for (auto &off: offs) {
    if (stat[off-1] == 1)
      return;
  }
  ans.push_back(std::move(stat));
}

int main() {
  ifstream fin("lamps.in");
  ofstream fout("lamps.out");

  fin >> n >> c;

  ons.push_back(0);
  fin >> ons.back();
  while (ons.back() != -1) {
    ons.push_back(0);
    fin >> ons.back();
  }
  ons.pop_back();

  offs.push_back(0);
  fin >> offs.back();
  while (offs.back() != -1) {
    offs.push_back(0);
    fin >> offs.back();
  }
  offs.pop_back();

  vector<int> pressed(4);
  for (int i = 0; i <= 0xf; ++i) {
    for (int j = 0; j < 4; ++j) {
      if (i & (1<<j))
        pressed[j] = 1;
      else
        pressed[j] = 0;
    }
    check(pressed);
  }

  std::sort(ans.begin(), ans.end());
  auto end_uniq = std::unique(ans.begin(), ans.end());
  for (auto it = ans.begin(); it != end_uniq; ++it) {
    for (auto &b: *it)
      fout << b;
    fout << endl;
  }
  if (ans.begin() == end_uniq)
    fout << "IMPOSSIBLE" << endl;

  return 0;
}
