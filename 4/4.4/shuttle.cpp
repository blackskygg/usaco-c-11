/*
  ID: blacksk2
  TASK: shuttle
  LANG: C++11
*/
#include <fstream>
#include <vector>

int main() {
  std::ifstream fin("shuttle.in");
  std::ofstream fout("shuttle.out");

  int n;
  fin >> n;

  int start = n, direction = 2;
  std::vector<std::vector<int>> results;
  for (int scale = 2; scale <= n + 1; ++scale) {
    results.emplace_back();
    for (int i = 0; i < scale; ++i) {
      results.back().push_back(start + (i * direction));
    }
    start += (scale - 1) * direction + direction / 2;
    direction = -direction;
  }
  for (int i = results.size() - 2; i >= 0; --i) {
    results.push_back(results[i]);
  }
  results.back().push_back(n + 1);

  int nnums = 0;
  for (const auto &vec : results) {
    for (const int x : vec) {
      ++nnums;
      if (nnums == 21) {
        nnums = 1;
        fout << std::endl;
      } else if (nnums != 1) {
        fout << " ";
      }
      fout << x;
    }
  }
  fout << std::endl;

  return 0;
}