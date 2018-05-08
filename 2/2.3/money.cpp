/*
  ID: blacksk2
  TASK: money
  LANG: C++11
*/
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

int main () {
  ifstream fin("money.in");
  ofstream fout("money.out");

  int V, N, t;
  fin >> V >> N;

  vector<int> coins(V, 0);
  for (int i = 0; i < V; ++i)
    fin >> coins[i];

  vector<unsigned long long> dp(N+1);
  dp[0] = 1;

  for (int i = 0; i < V; ++i)
    for (int n = coins[i]; n <= N; ++n)
      dp[n] += dp[n-coins[i]];

  fout << dp[N] << endl;

  return 0;
}
