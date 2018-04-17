/*
  ID: blacksk2
  TASK: numtri
  LANG: C++11
*/
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

int dp[1024], curr[1024];

int main()
{
  ifstream fin("numtri.in");
  ofstream fout("numtri.out");

  int n;
  fin >> n;

  fin >> dp[0];
  for (int i = 1; i < n; ++i) {
    for (int j = 0; j <= i; ++j)
      fin >> curr[j];
    dp[i] = dp[i-1] + curr[i];
    for (int j = i-1; j >= 1; --j)
      dp[j] = std::max(dp[j], dp[j-1]) + curr[j];
    dp[0] = dp[0] + curr[0];
  }

  int ans = 0;
  for (int i = 0; i < n; ++i)
    ans = std::max(ans, dp[i]);

  fout << ans << endl;

  return 0;
}
