/*
  ID: blacksk2
  TASK: msquare
  LANG: C++11
*/
#include <fstream>
#include <algorithm>
#include <queue>
#include <stack>
#include <unordered_map>
#include <vector>
#include <functional>

using namespace std;
using parent = std::pair<string, int>;

int main () {
  ifstream fin("msquare.in");
  ofstream fout("msquare.out");

  string t(8, 0);
  for (int i = 0; i < 8; ++i)
    fin >> t[i];

  vector<std::function<string(const string &)>> trans = {
    [](const string &a) -> string {
      auto s = a;
      std::reverse(s.begin(), s.end());
      return s;
    },
    [](const string &a) -> string {
      return a.substr(3,1)+a.substr(0, 3)+a.substr(5, 3)+a.substr(4,1);
    },
    [](const string &a) -> string {
      string s(8, '0');
      static int mapping[] = {0, 6, 1, 3, 4, 2, 5, 7};
      for (int i = 0; i < 8; ++i)
        s[i] = a[mapping[i]];
      return s;
    }
  };


  unordered_map<string, parent> vis;
  vector<string> curr, next;
  string s = "12345678";

  curr.push_back(s);
  vis[s] = make_pair("", -1);

  if (s == t)
    goto OUTPUT;
  for (;;) {
    for (auto &st: curr) {
      for (int i = 0; i < 3; ++i) {
        string new_st = trans[i](st);
        if (vis.count(new_st))
          continue;
        vis[new_st] = make_pair(st, i);
        next.push_back(new_st);
        if (new_st == t)
          goto OUTPUT;
      }
    }
    swap(curr, next);
  }

 OUTPUT:
  stack<int> ss;
  string st = t;
  while (st != s) {
    auto p = vis[st];
    ss.push(p.second);
    st = p.first;
  }
  fout << ss.size() << endl;
  int lcnt = 0;
  while (!ss.empty()) {
    fout << (char)(ss.top()+'A');
    ss.pop();
    if (++lcnt % 60 == 0) {
      fout << endl;
    }
  }
  if (lcnt == 0 || lcnt % 60 != 0)
    fout << endl;

  return 0;
}
