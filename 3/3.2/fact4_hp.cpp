/*
  ID: blacksk2
  TASK: fact4
  LANG: C++11
*/
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

string add(const string &s1, const string &s2) {
  string result;
  int carry = 0, len = max(s1.size(), s2.size());
  for (int i = 0; i < len ; ++i) {
    char a, b, sum;
    if (i > s1.size()-1)
      a = '0';
    else
      a = s1[s1.size()-1-i];
    if (i > s2.size()-1)
      b = '0';
    else
      b = s2[s2.size()-1-i];
    sum = a-'0'+b-'0'+carry;
    carry = sum/10;
    result.push_back(sum%10+'0');
  }
  if (carry > 0)
    result.push_back(carry+'0');
  while (result.size() > 1 && result.back() == '0')
    result.pop_back();
  std::reverse(result.begin(), result.end());
  return result;
}

string mul_one(const string &s, int n) {
  string result;
  int carry = 0;
  for (int i = 0; i < s.size(); ++i) {
    int prod = (s[s.size()-1-i]-'0')*n+carry;
    carry = prod/10;
    prod = prod%10;
    result.push_back(prod+'0');
  }
  if (carry > 0)
    result.push_back(carry+'0');
  while (result.size() > 1 && result.back() == '0')
    result.pop_back();
  std::reverse(result.begin(), result.end());
  return result;
}

string mul(const string &s, int n) {
  string t = s, result = "0";
  while (n) {
    result = add(result, mul_one(t, n%10));
    t.push_back('0');
    n = n / 10;
  }
  return result;
}

int main () {
  ifstream fin("fact4.in");
  ofstream fout("fact4.out");

  int n;
  fin >> n;

  string s = "1";
  for (int i = 1; i <= n; ++i)
    s = mul(s, i);

  for (auto it = s.rbegin(); it != s.rend(); ++it) {
    if (*it != '0') {
      fout << *it << endl;
      break;
    }
  }

  return 0;
}
