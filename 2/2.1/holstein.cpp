/*
  ID: blacksk2
  TASK: holstein
  LANG: C++11
*/
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
  ifstream fin("holstein.in");
  ofstream fout("holstein.out");

  int nv, v;
  vector<int> minv;
  fin >> nv;
  for (int i = 0; i < nv; ++i) {
    fin >> v;
    minv.push_back(v);
  }

  int nscoop;
  vector<vector<int>> scoops;
  fin >> nscoop;
  for (int i = 0; i < nscoop; ++i) {
    scoops.push_back(vector<int>(nv));
    for (auto &t: scoops.back())
      fin >> t;
  }

  unsigned int max = (1U<<nscoop)-1;
  vector<int> ans(nscoop, nscoop);
  int min_ns = nscoop+1;
  for (unsigned int bm = 1; bm <= max; ++bm) {
    vector<int> curr_nv(nv, 0), curr_sc;
    for (unsigned int i = 0; i < nscoop; ++i) {
      if (bm & (0x1U<<i)) {
        curr_sc.push_back(i+1);
        for (int v = 0; v < nv; ++v)
          curr_nv[v] += scoops[i][v];
      }
    }

    bool enough = true;
    for (int v = 0; v < nv; ++v) {
      if (curr_nv[v] < minv[v]) {
        enough = false;
        break;
      }
    }
    if (enough) {
      if ((curr_sc.size() < ans.size())
          || ((curr_sc.size() == ans.size()) && curr_sc < ans))
        ans = curr_sc;
    }
  }

  fout << ans.size();
  for (auto &s: ans)
    fout << " " << s;
  fout << endl;

  return 0;
}
