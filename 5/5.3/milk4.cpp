/*
  ID: blacksk2
  TASK: milk4
  LANG: C++11
*/

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

// Represents the best solution for a given q.
// This means q can be acheived with `total_cnt` pails,
// and the last pail `p` is repeated `cnt` times.
struct Solution { int p, cnt, total; };

// Returns true if the sequence for rem1 < rem2.
bool smaller(const std::vector<Solution>& best, int rem1, int rem2) {
  assert(best[rem1].total == best[rem2].total);
  while (rem1 && rem2) {
    if (best[rem1].p != best[rem2].p) {
      return best[rem1].p < best[rem2].p;
    }
    rem1 -= best[rem1].cnt * best[rem1].p;
    rem2 -= best[rem2].cnt * best[rem2].p;
  }
  return false;
}

std::vector<int> solve(const int q, std::vector<int>& pails) {
  std::sort(pails.begin(), pails.end());
  pails.erase(std::unique(pails.begin(), pails.end()), pails.end());

  // Best solution so far.
  std::vector<Solution> best(q+1, {-1, -1, -1});
  best[0] = {-1, 0, 0};
  // Best solution ending with the current pail.
  std::vector<Solution> best_with_p = best;

  for (int i = pails.size()-1; i >= 0; --i) {
    const int p = pails[i];
    best_with_p[p] = {p, 1, 1};

    for (int j = p+1; j <= q; ++j) {
      const int prev = j-p;
      best_with_p[j] = best[j];

      // Option 1: Combo.
      if (best_with_p[prev].p == p) {
        best_with_p[j] = best_with_p[prev];
        best_with_p[j].cnt++;
      }
      // Option 2: Put one current pail.
      if (best[prev].total == -1) continue;
      if (best_with_p[j].p != p  // No combo.
          || (best[prev].total+1 < best_with_p[j].total)  // Better in length.
          || (best[prev].total+1 == best_with_p[j].total
              && smaller(best, prev, j-p*best_with_p[j].cnt)) // Smaller
          ) {
        best_with_p[j] = {p, 1, best[prev].total + 1};
      }
    }

    // Update best solution so far.
    for (int j = 1; j <= q; ++j) {
      if (best_with_p[j].p != p) continue;
      if (best[j].total == -1 || (best_with_p[j].total <= best[j].total)) {
        best[j] = best_with_p[j];
      }
    }
  }

  std::vector<int> ans;
  int rem = q;
  while (rem) {
    ans.push_back(best[rem].p);
    rem -= best[rem].p * best[rem].cnt;
  }
  return ans;
}

int main() {
  std::ifstream fin("milk4.in");
  std::ofstream fout("milk4.out");

  int q, p;
  fin >> q >> p;

  std::vector<int> pails(p);
  for (int i = 0; i < p; ++i) fin >> pails[i];

  auto ans = solve(q, pails);
  fout << ans.size();
  for (const auto x : ans) fout << " " << x;
  fout << std::endl;

  return 0;
}
