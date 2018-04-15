/*
ID: blacksk2
TASK: barn1
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  ifstream fin("barn1.in");
  ofstream fout("barn1.out");

  int m, s, c, t;
  vector<int> cows, holes;

  fin >> m >> s >> c;
  while (c--) {
    fin >> t;
    cows.push_back(t);
  }
  sort(cows.begin(), cows.end());

  for (int i = 1; i < cows.size(); ++i) {
    int hole = cows[i]-cows[i-1]-1;
    if (hole > 0)
      holes.push_back(hole);
  }
  sort(holes.begin(), holes.end(), [](int a, int b) { return a > b; });

  if (cows.back() != s)
    s -= s-cows.back();
  if (cows[0] != 1)
    s -= cows[0]-1;
  for (int i = 0; i < m-1 && i < holes.size(); ++i)
    s -= holes[i];
  fout << s << endl;

  return 0;
}
