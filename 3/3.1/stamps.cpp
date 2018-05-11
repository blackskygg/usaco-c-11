/*
  ID: blacksk2
  TASK: stamps
  LANG: C++11
*/
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

const int INF = 1e9+7;

int main () {
  ifstream fin("stamps.in");
  ofstream fout("stamps.out");

  int n, k;
  fin >> k >> n;

  vector<int> stamps(n);
  for (int i = 0; i < n; ++i)
    fin >> stamps[i];

  int max_val = k**std::max_element(stamps.begin(), stamps.end());
  vector<int> dp(max_val+2, INF);
  dp[0] = 0;

  for (int i = 0; i < n; ++i)
    for (int j = stamps[i]; j <= max_val; ++j)
      dp[j] = min(dp[j-stamps[i]]+1, dp[j]);

  for (int i = 0; i <= max_val+1; ++i) {
    if (dp[i] == INF || dp[i] > k) {
      fout << i-1 << endl;
      break;
    }
  }

  return 0;
}
