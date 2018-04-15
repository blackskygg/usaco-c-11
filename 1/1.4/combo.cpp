/*
ID: blacksk2
TASK: combo
LANG: C++11
*/
#include <fstream>
#include <cstdlib>
#include <algorithm>

using namespace std;

int main() {
  ifstream fin("combo.in");
  ofstream fout("combo.out");

  int n, cntjm[3]={0,0,0}, pass[2][3];

  fin >> n;
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 3; ++j) {
      fin >> pass[i][j];
    }
  }

  auto is_within = [n] (int s, int t) {
    if (s > t)
      std::swap(s, t);
    return (t-s <= 2) || (s+n-t <= 2);
  };

  for (int i = 0; i < 3; ++i) {
    for (int t = 1; t <= n; ++t) {
      if (is_within(t, pass[0][i]) && is_within(t, pass[1][i]))
        cntjm[i]++;
    }
  }

  if (n >= 5)
    fout << 250 - cntjm[0]*cntjm[1]*cntjm[2] << endl;
  else
    fout << 2*n*n*n - cntjm[0]*cntjm[1]*cntjm[2] << endl;

  return 0;
}
