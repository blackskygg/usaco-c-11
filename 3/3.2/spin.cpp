/*
  ID: blacksk2
  TASK: spin
  LANG: C++11
*/
#include <fstream>
#include <algorithm>
#include <vector>
#include <tuple>
#include <cstring>

using namespace std;

int mod(int x, int m) {
  if (x >= 0)
    return x % m;
  else
    return (m-std::abs(x)%m)%m;
}

int main () {
  ifstream fin("spin.in");
  ofstream fout("spin.out");

  int rates[5];
  vector<bool> wedges[5];

  for (int i = 0; i < 5; ++i) {
    int nw = 0;
    fin >> rates[i] >> nw;
    wedges[i] = vector<bool>(360, false);
    for (int j = 0; j < nw; ++j) {
      int s, e;
      fin >> s >> e;
      for (int ang = s; ang <= s+e; ++ang)
        wedges[i][ang%360] = 1;
    }
  }

  vector<int> curr_ang(5, 0);
  for (int t = 0; t < 360; ++t) {
    for (int ang = 0; ang < 360; ++ang) {
      bool yes = true;
      for (int w = 0; w < 5; ++w) {
        if (!wedges[w][mod(ang-curr_ang[w], 360)]) {
          yes = false;
          break;
        }
      }
      if(yes) {
        fout << t << endl;
        return 0;
      }
    }
    // fout << "t=" << t << ": "  << endl;
    // for (int w = 0; w < 5; ++w) {
    //   fout << "\tw=" << w << ": " << endl <<  "\t";
    //   for (int i = 0; i < 360;) {
    //     int saved_i = i;
    //     while (i < 360 && wedges[w][mod(i-curr_ang[w], 360)])
    //       i++;
    //     if (i-saved_i > 0) {
    //       fout << saved_i << "->" << i-1 << " ";
    //     } else {
    //       i++;
    //     }
    //   }
    //   fout << endl;
    // }
    for (int w = 0; w < 5; ++w)
      curr_ang[w] += rates[w];
  }

  fout << "none" << endl;

  return 0;
}
