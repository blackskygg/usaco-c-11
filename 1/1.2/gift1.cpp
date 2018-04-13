/*
ID: blacksk2
TASK: gift1
LANG: C++11
*/

#include <fstream>
#include <unordered_map>
#include <vector>

using namespace std;

int main()
{
  ifstream fin("gift1.in");
  ofstream fout("gift1.out");

  int np = 0;
  unordered_map<string, int> account;
  vector<string> names;
  string s;

  fin >> np;
  for (int i = 0; i < np; ++i) {
    fin >> s;
    names.push_back(s);
    account[s] = 0;
  }

  int ngift, money;
  for (int i = 0; i < np; ++i) {
    fin >> s >> money >> ngift;
    if (money == 0 || ngift == 0)
      continue;
    account[s] -= money/ngift * ngift;

    for (int j = 0; j < ngift; ++j) {
      fin >> s;
      account[s] += money/ngift;
    }
  }

  for (auto &n: names)
    fout << n << " " << account[n] << endl;

  return 0;
}
