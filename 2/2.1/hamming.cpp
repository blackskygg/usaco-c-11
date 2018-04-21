/*
  ID: blacksk2
  TASK: hamming
  LANG: C++11
*/
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

int calc_ham(int a, int b) {
  int diff = a ^ b, cnt = 0;
  while (diff) {
    cnt ++;
    diff -= diff&(-diff);
  }
  return cnt;
}

int main() {
  ifstream fin("hamming.in");
  ofstream fout("hamming.out");

  int n, b, d;
  fin >> n >> b >> d;

  int max = (1<<b)-1;
  vector<int> ans;
  bool found = false;
  for (int i = 0; i <= max-n+1 && !found; ++i) {
    ans = {i};
    for (int j = i+1; j <= max; ++j) {
      bool good=true;
      for (auto &a: ans) {
        if (calc_ham(a, j) < d) {
          good = false;
          break;
        }
      }
      if (good) {
        ans.push_back(j);
        if (ans.size() == n) {
          found = true;
          break;
        }
      }
    }
  }

  for (int i = 0; i < ans.size(); ++i) {
    if (i % 10 == 0)
      fout << ans[i];
    else if (i % 10 == 9)
      fout << " " << ans[i] << endl;
    else
      fout << " " << ans[i];
  }
  if (ans.size() % 10)
    fout << endl;

  return 0;
}
