/*
  ID: blacksk2
  TASK: nocows
  LANG: C++11
*/
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int solve(int n, int k, vector<vector<int>> &memoize) {
  if (k < 0 || n < 0)
    return 0;
  if (k <= 1 || n <= 1) {
    if (k == n)
      return 1;
    else
      return 0;
  }
  if (n < 2*k-1)
    return 0;
  if (memoize[n][k] != -1)
    return memoize[n][k];

  int cnt = 0, r, coef;
  for (int i = 1; i <= (n-1)/2; i += 2) {
    r = solve(i, k-1, memoize), coef = (i+i == n-1) ? 1 : 2;
    if (r != 0) {
      for (int j = 0; j < k-1; ++j)
        cnt += coef*r*solve(n-1-i, j, memoize);
    }
    r = solve(n-1-i, k-1, memoize);
    if (r != 0) {
      for (int j = 0; j < k-1; ++j)
        cnt += coef*r*solve(i, j, memoize);
    }
    cnt += coef*solve(i, k-1, memoize)*solve(n-i-1, k-1, memoize);
    cnt = cnt % 9901;
  }
  return memoize[n][k] = cnt;
}

int main() {
  ifstream fin("nocows.in");
  ofstream fout("nocows.out");

  int n, k;
  fin >> n >> k;

  vector<vector<int>> memoize(n+1, vector<int>(k+1, -1));
  fout << solve(n, k, memoize) << endl;

  return 0;
}
