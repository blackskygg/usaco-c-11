/*
ID: blacksk2
TASK: ariprog
LANG: C++11
*/
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

bool is_good[250*250*2 + 1024];

int main()
{
  ifstream fin("ariprog.in");
  ofstream fout("ariprog.out");

  int l, m;
  fin >> l >> m;

  const unsigned long MAX = m*m+m*m;

  for (int i = 0; i <= m; ++i) {
    for (int j = i; j <= m; ++j) {
      int n = i*i+j*j;
      is_good[n] = true;
    }
  }

  vector<int> good_nums;
  for (int i = 0; i <= MAX; ++i) {
    if (is_good[i])
      good_nums.push_back(i);
  }

  vector<pair<int,int>> ans;
  for (int i = 0; i < good_nums.size(); ++i) {
    for (int j = i+1; j < good_nums.size(); ++j) {
      int a = good_nums[i], b = good_nums[j] - good_nums[i];

      bool flag = true;
      for (unsigned long n = 0; n < l; ++n) {
        unsigned long ni = a + n*b;
        if (ni > MAX || !is_good[ni]) {
          flag = false;
          break;
        }
      }
      if (flag)
        ans.emplace_back(b, a);
    }
  }
  sort(ans.begin(), ans.end());

  if (ans.size() == 0) {
    fout << "NONE" << endl;
  } else {
    for (auto &p: ans)
      fout << p.second << " " << p.first << endl;
  }

  return 0;
}
