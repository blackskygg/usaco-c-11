/*
  ID: blacksk2
  TASK: ratios
  LANG: C++11
*/
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

int main () {
  ifstream fin("ratios.in");
  ofstream fout("ratios.out");

  int ratios[4][3];

  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 3; ++j)
      fin >> ratios[i][j];

  int besti=100, bestj=100, bestk=100, bestans = -1;
  for (int i = 0; i < 100; ++i) {
    for (int j = 0; j < 100; ++j) {
      for (int k = 0; k < 100; ++k) {
        int t = i*ratios[1][0]+j*ratios[2][0]+k*ratios[3][0];
        if ((ratios[0][0] == 0 && t != 0) || (ratios[0][0] != 0  && t % ratios[0][0]))
          continue;
        int ans = t / ratios[0][0];
        if (ans == 0)
          continue;
        bool yes = true;
        for (int r = 1; r < 3; ++r) {
          t = i*ratios[1][r]+j*ratios[2][r]+k*ratios[3][r];
          if ((ratios[0][r] == 0 && t != 0) ||
              (ratios[0][r] != 0 && (t%ratios[0][r] || t/ratios[0][r] != ans))) {
            yes = false;
            continue;
          }
        }
        if (yes) {
          if (i+j+k < besti+bestj+bestk) {
            besti = i;
            bestj = j;
            bestk = k;
            bestans = ans;
          }
        }
      }
    }
  }

  if (besti < 100)
    fout << besti << " " << bestj << " " << bestk << " "<< bestans << endl;
  else
    fout << "NONE" << endl;



  return 0;
}
