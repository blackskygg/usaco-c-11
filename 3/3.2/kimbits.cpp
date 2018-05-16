/*
  ID: blacksk2
  TASK: kimbits
  LANG: C++11
*/
#include <fstream>
#include <algorithm>
#include <vector>
#include <bitset>

using namespace std;

unsigned int C(int a, int b) {
  static unsigned int memo[32][32];
  if (memo[a][b] != 0)
    return memo[a][b];
  if (b > a)
    return 0;
  if (b == 0 || b == a)
    return 1;
  if (b == 1)
    return a;
  return memo[a][b] = C(a-1, b)+C(a-1, b-1);
}

unsigned int C_less(int a, int b) {
  static unsigned int memo[32][32];
  if (memo[a][b] != 0)
    return memo[a][b];
  for (int i = 0; i <= b; ++i)
    memo[a][b] += C(a, i);
  return memo[a][b];
}

int main () {
  ifstream fin("kimbits.in");
  ofstream fout("kimbits.out");

  unsigned int n, l, i;
  fin >> n >> l >> i;

  unsigned int ans = 0, bits_left = l;
  for (int bit = 31; bit >= 2; --bit) {
    if (i > C_less(bit-1, bits_left)) {
      i -= C_less(bit-1, bits_left);
      bits_left--;
      ans++;
    }
    ans = ans<<1;
  }
  if (i == 2)
    ans++;

  auto &&anss = bitset<31>(ans).to_string();
  fout << anss.substr(31-n) << endl;

  return 0;
}
