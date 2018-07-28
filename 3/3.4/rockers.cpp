/*
  ID: blacksk2
  TASK: rockers
  LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
  ifstream fin("rockers.in");
  ofstream fout("rockers.out");

  int N, T, M;
  fin >> N >> T >> M;

  vector<int> duration(N);
  for (int i = 0; i < N; ++i)
    fin >> duration[i];

  int dp[N][M][T];

  for (int m = 0; m < M; ++m) {
    for (int t = 0; t < T; ++t) {
      if (m > 0 && duration[0] <= T) {
        dp[0][m][t] = 1;
      } else {
        if (duration[0] <= t+1) {
          dp[0][m][t] = 1;
        } else {
          dp[0][m][t] = 0;
        }
      }
    }
  }

  for (int n = 1; n < N; ++n) {
    for (int m = 0; m < M; ++m) {
      for (int t = 0; t < T; ++t) {
        auto &curr = dp[n][m][t] = dp[n-1][m][t];
        if (duration[n] <= t) {
          curr = std::max(curr, dp[n-1][m][t-duration[n]]+1);
        } else if (duration[n] == t+1) {
          if (m == 0) {
            curr = std::max(curr, 1);
          } else {
            curr = std::max(curr, dp[n-1][m-1][T-1]+1);
          }
        } else if (duration[n] < T && m > 0) {
          curr = std::max(curr, dp[n-1][m-1][T-1-duration[n]]+1);
        } else if (duration[n] == T && m > 0) {
          if (m == 1) {
            curr = std::max(curr, 1);
          } else {
            curr = std::max(curr, dp[n-1][m-2][T-1]+1);
          }
        }
      }
    }
  }


  fout << dp[N-1][M-1][T-1] << std::endl;


  return 0;
}
