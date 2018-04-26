/*
  ID: blacksk2
  TASK: subset
  LANG: C++11
*/
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
  ifstream fin("subset.in");
  ofstream fout("subset.out");

  int n;
  fin >> n;

  if ((1+n)*n % 4 != 0) {
    fout << 0 << endl;
    return 0;
  }

  int target = (1+n)*n/4;
  vector<unsigned long> dp(target+1, 0);
  dp[0] = dp[1] = 1;
  for (int i = 1; i < n; ++i)
    for (int t = target; t >= 0; t--)
      dp[t] = dp[t]+ ((t-i-1 >= 0)? dp[t-i-1]: 0);
  fout << dp[target]/2 << endl;

  return 0;
}
