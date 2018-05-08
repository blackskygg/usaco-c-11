/*
  ID: blacksk2
  TASK: prefix
  LANG: C++11
*/
#include <fstream>
#include <algorithm>
#include <sstream>
#include <vector>

using namespace std;

int main() {
  ifstream fin("prefix.in");
  ofstream fout("prefix.out");

  vector<string> primitives;
  string t;
  ostringstream ss;

  for (;;) {
    fin >> t;
    if (t[0] == '.')
      break;
    primitives.emplace_back(std::move(t));
  }
  while (fin >> t)
    ss << t;

  string seq = ss.str();
  auto str_equal = [] (string::iterator &&ita, string::iterator &&itb, int len) {
    while (len--) {
      if (*ita++ != *itb++)
        return false;
    }
    return true;
  };

  vector<int> dp(seq.size(), 0);
  int highest = -1;
  for (int i = 0; i < seq.size(); ++i) {
    for (auto &p: primitives) {
      if (i < p.size()-1)
        continue;
      if (!str_equal(p.begin(), seq.begin()+(i-p.size()+1), p.size()))
        continue;
      if ((i == p.size()-1) || dp[i-p.size()]) {
        highest = i;
        dp[i] = 1;
        break;
      }
    }
  }

  fout << highest+1 << endl;

  return 0;
}
