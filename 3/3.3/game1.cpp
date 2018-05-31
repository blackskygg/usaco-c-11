/*
  ID: blacksk2
  TASK: game1
  LANG: C++11
*/

#include <fstream>
#include <vector>
#include <array>
#include <algorithm>

using namespace std;

int main() {
  ifstream fin("game1.in");
  ofstream fout("game1.out");

  int n;
  fin >> n;

  vector<int> nums(n), sums(n);
  for (int i = 0; i < n; ++i) {
    fin >> nums[i];
    if (i == 0)
      sums[i] = nums[i];
    else
      sums[i] = nums[i]+sums[i-1];
  }

  auto get_sum = [&sums] (int i, int j) {
    if (i == 0)
      return sums[j];
    else
      return sums[j]-sums[i-1];
  };

  array<vector<int>, 2> dp;
  dp.fill(vector<int>(n+1, 0));

  for (int l = 1; l <= n; ++l) {
    for (int i = 0; i+l-1 < n; ++i)
      dp[1][i] = get_sum(i, i+l-1)-std::min(dp[0][i+1],dp[0][i]);
    swap(dp[0], dp[1]);
  }

  fout << dp[0][0] << " " << sums[n-1]-dp[0][0] << endl;

  return 0;
}
