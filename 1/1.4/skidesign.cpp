/*
ID: blacksk2
TASK: skidesign
LANG: C++11
*/
#include <fstream>
#include <vector>

using namespace std;

int main()
{
  ifstream fin("skidesign.in");
  ofstream fout("skidesign.out");

  int n;
  fin >> n;

  vector<int> heights(n);
  for (int i = 0; i < n; ++i)
    fin >> heights[i];

  int min_cnt = 10000 * 1000;
  for (int i = 0; i <= 100-17; ++i) {
    int low = i, high = i+17, cnt = 0;

    for (auto &h: heights) {
      if (h < low)
        cnt += (low-h) * (low-h);
      else if (h > high)
        cnt += (high-h) * (high-h);
    }
    if (min_cnt > cnt)
      min_cnt = cnt;
  }

  fout << min_cnt << endl;

  return 0;
}
