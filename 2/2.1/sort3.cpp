/*
  ID: blacksk2
  TASK: sort3
  LANG: C++11
*/
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
  ifstream fin("sort3.in");
  ofstream fout("sort3.out");

  int n;
  fin >> n;

  vector<int> vals(n), nums(3);
  for (int i = 0; i < n; ++i) {
    fin >> vals[i];
    nums[--vals[i]]++;
  }
  nums[1] += nums[0];
  nums[2] += nums[1];

  vector<vector<int>> place(3, vector<int>(3, 0));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (i < nums[j]) {
        place[j][vals[i]]++;
        break;
      }
    }
  }

  int ans = 0;
  //eliminate pairs
  for (int i = 0; i < 2; ++i) {
    for (int j = i+1; j < 3; ++j) {
      int p = std::min(place[i][j], place[j][i]);
      place[i][j] -= p;
      place[j][i] -= p;
      ans += p;
    }
  }
  // eliminate 3-node cycles
  ans += (place[0][1] + place[1][0])*2;

  fout << ans << endl;

  return 0;
}
