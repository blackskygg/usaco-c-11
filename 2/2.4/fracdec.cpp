/*
  ID: blacksk2
  TASK: fracdec
  LANG: C++11
*/
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;

int main () {
  ifstream fin("fracdec.in");
  ofstream fout("fracdec.out");

  int n, d;
  fin >> n >> d;

  vector<int> decimals;
  unordered_map<int, int> numerators;
  int integer, rep_pos=-1;
  ostringstream sout;

  integer = n/d;
  n = (n%d)*10;
  while (n) {
    if (numerators.count(n)) {
      rep_pos = numerators[n];
      break;
    }
    numerators[n] = decimals.size();
    decimals.push_back(n/d);
    n = (n%d)*10;
  }

  sout << integer << '.';
  if (rep_pos == -1) {
    if (decimals.size() == 0) {
      sout << 0;
    } else {
        for (auto d: decimals)
          sout << d;
    }
  } else {
      for (int i = 0; i < rep_pos; ++i)
        sout << decimals[i];
      sout << '(';
      for (int i = rep_pos; i < decimals.size(); ++i)
        sout << decimals[i];
      sout << ')';
  }

  auto &&outs = sout.str();
  for (int i = 0; i < outs.size(); i+=76) {
    int len = std::min((int)(outs.size()-i), 76);
    for (int j = 0; j < len; ++j)
      fout << outs[i+j];
    fout << endl;
  }

  return 0;
}
