/*
ID: blacksk2
TASK: palsquare
LANG: C++11
*/
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

bool is_palindrome(string s) {
  for (int i = 0; i < s.size()/2; ++i) {
    if (s[i] != s[s.size()-1-i])
      return false;
  }
  return true;
}

string base_n(int num, int base) {
  string r;

  while (num) {
    int remain = num % base;
    if (remain < 10)
      r.push_back(remain+'0');
    else
      r.push_back(remain-10+'A');
    num /= base;
  }

  std::reverse(r.begin(), r.end());
  return r;
}

int main() {
  ifstream fin("palsquare.in");
  ofstream fout("palsquare.out");

  int base;
  fin >> base;

  for (int i = 1; i <= 300; ++i) {
    string s = base_n(i*i, base);
    if (is_palindrome(s))
      fout << base_n(i, base) << " " << s << endl;
  }

  return 0;
}

