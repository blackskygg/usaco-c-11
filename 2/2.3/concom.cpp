/*
  ID: blacksk2
  TASK: concom
  LANG: C++11
*/
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

int main () {
  ifstream fin("concom.in");
  ofstream fout("concom.out");

  int n;
  fin >> n;

  int i, j, p;
  vector<vector<int>> con(100, vector<int>(100, 0)),
    dom(100, vector<int>(100, 0));
  for (int i = 0; i < 100; ++i)
    dom[i][i] = 1;
  for (int t = 0; t < n; ++t) {
    fin >> i >> j >> p;
    con[i-1][j-1] = p;
    if (p > 50)
      dom[i-1][j-1] = 1;
  }

  for (int l = 0; l < 100; ++l) {
    for (int i = 0; i < 100; ++i) {
      vector<int> newcon(100, 0);
      for (int j = 0; j < 100; ++j) {
        if (!dom[i][j])
          continue;
        for (int c = 0; c < 100; ++c)
          newcon[c] += con[j][c];
      }
      for (int j = 0; j < 100; ++j)
        if (newcon[j] > 50)
          dom[i][j] = 1;
    }
  }

  for (int i = 0; i < 100; ++i) {
    for (int j = 0; j < 100; ++j) {
      if (i == j || !dom[i][j])
        continue;
      fout << i+1 << " " << j+1 << endl;
    }
  }

  return 0;
}
