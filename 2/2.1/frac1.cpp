/*
  ID: blacksk2
  TASK: frac1
  LANG: C++11
*/
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;
using frac = std::pair<int, int>;

int gcd(int a, int b) {
  if (b == 0)
    return a;
  return gcd(b, a%b);
}

int main()
{
  ifstream fin("frac1.in");
  ofstream fout("frac1.out");

  int n;
  fin >> n;

  vector<frac> nums;

  for (int i = 2; i <= n; ++i) {
    for (int j = 1; j < i; ++j) {
      if (gcd(i, j) == 1)
        nums.emplace_back(j, i);
    }
  }
  sort(nums.begin(), nums.end(),
       [](const frac &f1, const frac &f2) {
         return f1.first*f2.second < f2.first*f1.second;
       });

  fout << "0/1" << endl;
  for (auto &f: nums)
    fout << f.first << "/" << f.second << endl;
  fout << "1/1" << endl;

  return 0;
}
