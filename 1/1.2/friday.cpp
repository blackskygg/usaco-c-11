/*
ID: blacksk2
TASK: friday
LANG: C++11
*/
#include <fstream>
#include <vector>

using namespace std;

const vector<int> doms[2] = {{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
                             {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};
int is_leap(int year) {
  return ((year % 400 == 0) || ((year % 100 != 0) && (year % 4 == 0))) ? 1 : 0;
}

int main()
{
  ifstream fin("friday.in");
  ofstream fout("friday.out");
  vector<int> stats(7, 0);
  int n, curr_year = 1900, curr_wd = 0;

  fin >> n;
  while (n--) {
    auto &dom = doms[is_leap(curr_year)];
    for (int i = 0; i < 12; ++i) {
      stats[curr_wd]++;
      curr_wd = (curr_wd+dom[i]) % 7;
    }
    curr_year++;
  }

  fout << stats[0];
  for (int i = 1; i < stats.size(); ++i)
    fout << " " << stats[i];
  fout << endl;

  return 0;
}
