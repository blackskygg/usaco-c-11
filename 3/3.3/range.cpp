/*
  ID: blacksk2
  TASK: range
  LANG: C++11
*/

#include <fstream>
#include <vector>
#include <limits>

using namespace std;

int main() {
  ifstream fin("range.in");
  ofstream fout("range.out");

  int n;
  fin >> n;

  vector<string> field(n);
  for (int i = 0; i < n; ++i)
    fin >> field[i];

  vector<int> count(n+1, 0);
  vector<vector<int>> right(n,vector<int>(n)), down(n,vector<int>(n));

   for (int i = 0; i < n; ++i) {
     right[i][n-1] = field[i][n-1]-'0';
     down[n-1][i] = field[n-1][i]-'0';
     for (int j = n-2; j >= 0; --j) {
       right[i][j] = (field[i][j] == '1')? right[i][j+1]+1: 0;
       down[j][i] = (field[j][i] == '1')? down[j+1][i]+1: 0;
     }
   }

   for (int i = 0; i < n-1; ++i) {
     for (int j = 0; j < n-1; ++j) {
       if (field[i][j] == '0')
         continue;
       int maxl = std::min(n-i, n-j), l = 2;
       while (l <= maxl && down[i][j+l-1] >= l && right[i+l-1][j] >= l)
         count[l++]++;
     }
   }


  for (int i = 2; i <= n; ++i)
    if (count[i])
      fout << i << " " << count[i] << endl;

  return 0;
}
