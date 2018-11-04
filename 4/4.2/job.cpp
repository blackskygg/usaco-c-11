/*
  ID: blacksk2
  TASK: job
  LANG: C++11
*/
#include <algorithm>
#include <fstream>
#include <limits>
#include <vector>

static const int inf = std::numeric_limits<int>::max();

int main() {
  std::ifstream fin("job.in");
  std::ofstream fout("job.out");

  int n, m[2];
  fin >> n >> m[0] >> m[1];

  std::vector<int> mtime[2];
  for (int i = 0; i < 2; ++i) {
    mtime[i] = std::vector<int>(m[i], 0);
    for (int j = 0; j < m[i]; ++j) {
      fin >> mtime[i][j];
    }
  }
  std::vector<int> mfinish[2], tfinish[2];
  for (int i = 0; i < 2; ++i) {
    auto &mf = mfinish[i];
    auto &tf = tfinish[i];
    auto &mt = mtime[i];
    mf = std::vector<int>(m[i], 0);
    tf = std::vector<int>(n, 0);
    for (int tn = 0; tn < n; ++tn) {
      int min_finish = inf, idx;
      for (int tm = 0; tm < m[i]; ++tm) {
        if (mf[tm] + mt[tm] < min_finish) {
          min_finish = mf[tm] + mt[tm];
          idx = tm;
        }
      }
      mf[idx] = min_finish;
      tf[i ? (n - 1 - tn) : (tn)] = min_finish;
    }
  }

  int max_a = 0, max_total = 0;
  for (int j = 0; j < n; ++j) {
    max_a = std::max(max_a, tfinish[0][j]);
    max_total = std::max(max_total, tfinish[0][j] + tfinish[1][j]);
  }
  fout << max_a << " " << max_total << std::endl;

  return 0;
}