/*
ID: blacksk2
TASK: dualpal
LANG: C++11
*/
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

string base_n(int num, int b) {
  string r;

  while (num) {
    r.push_back(num % b);
    num /= b;
  }
  std::reverse(r.begin(), r.end());

  return r;
}

bool is_palindrome(string s) {
  for (int i = 0; i < s.size()/2; ++i) {
    if (s[i] != s[s.size()-1-i])
      return false;
  }
  return true;
}

bool is_dual_palindrome(int n) {
  int cnt = 0;

  for (int i = 10; i >= 2; --i) {
    if (is_palindrome(base_n(n,i ))) {
      if (++cnt == 2)
        break;
    }
  }

  return cnt == 2;
}

int main() {
  ifstream fin("dualpal.in");
  ofstream fout("dualpal.out");

  int n, s;
  fin >> n >> s;

  for (int i = 0; i < n; ++i) {
    while (!is_dual_palindrome(++s))
      ;
    fout << s << endl;
  }

  return 0;
}
