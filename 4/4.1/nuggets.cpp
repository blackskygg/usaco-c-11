/*
  ID: blacksk2
  TASK: nuggets
  LANG: C++11
*/
#include <algorithm>
#include <cstdlib>
#include <deque>
#include <fstream>
#include <vector>

void uniq_vector(std::vector<int> &vec) {
  std::vector<bool> seen(257, false);
  std::vector<int> result;

  for (const auto n : vec) {
    if (!seen[n]) {
      seen[n] = true;
      result.push_back(n);
    }
  }

  std::swap(vec, result);
}

int calc_ans_from_dp(const std::deque<bool> &vec, int base, int bound) {
  for (int i = bound; i >= 0; --i) {
    if (!vec[i]) {
      return base + i;
    }
  }
  return 0;
}

int calc_ans(std::vector<int> &packs) {
  uniq_vector(packs);

  int max_pack = *std::max_element(packs.begin(), packs.end());
  int min_pack = *std::min_element(packs.begin(), packs.end());
  int base = 1, combo = 0, count = 0, prev_count = 0;
  std::deque<bool> dp(max_pack, false);
  for (const int p : packs) {
    dp[p - 1] = true;
  }
  for (int i = 0; i < max_pack; ++i) {
    for (const int p : packs) {
      dp[i] = dp[i] || (i >= p && dp[i - p]);
    }
    count += dp[i] ? 1 : 0;
    combo = dp[i] ? combo + 1 : 0;
    if (combo == min_pack) {
      return calc_ans_from_dp(dp, base, i);
    }
  }
  prev_count = count;

  for (unsigned int i = 0; i < 2000000000; ++i) {
    int target = false;
    for (const int p : packs) {
      target = target || dp[dp.size() - p];
    }
    count += dp.front() ? -1 : 1;
    count += target ? 1 : -1;
    dp.pop_front();
    dp.push_back(target);
    base++;
    combo = target ? combo + 1 : 0;
    if (combo == min_pack) {
      return calc_ans_from_dp(dp, base, dp.size() - 1);
    }
    if (base != 1 && base % max_pack == 1) {
      if (prev_count == count) {
        return 0;
      } else {
        prev_count = count;
      }
    }
  }

  return 0;
}

int main() {
  std::ifstream fin("nuggets.in");
  std::ofstream fout("nuggets.out");

  int n;
  fin >> n;

  std::vector<int> packs(n, 0);
  for (int i = 0; i < n; ++i) {
    fin >> packs[i];
  }

  fout << calc_ans(packs) << std::endl;

  return 0;
}