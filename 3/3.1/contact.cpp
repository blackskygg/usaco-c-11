/*
  ID: blacksk2
  TASK: contact
  LANG: C++11
*/
#include <fstream>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <vector>

using namespace std;

int myhash(const string &s) {
    int res = 1;
    for (auto c: s)
      res = (res<<1)+c-'0';
    return res;
};

string rhash(int h) {
  string s;
  while (h != 1) {
    s.push_back((h&0x1)+'0');
    h = h>>1;
  }
  std::reverse(s.begin(), s.end());
  return s;
}

int main () {
  ifstream fin("contact.in");
  ofstream fout("contact.out");

  int a, b, n;
  fin >> a >> b >> n;

  string t;
  ostringstream os;
  while (fin >> t)
    os << t;
  auto &&s = os.str();

  int lowhash = 1<<a, highhash = 1<<(b+1);
  vector<pair<int, int>> stats(highhash);
  for (int ch = lowhash; ch < highhash; ++ch)
    stats[ch].second = ch;
  for (int len = a; len <= b; ++len)
    for (int i = 0; i+len <= s.size(); ++i)
      stats[myhash(s.substr(i, len))].first++;

  sort(stats.begin()+lowhash, stats.begin()+highhash,
       [](const pair<int, int> &pa, const pair<int, int> &pb) {
         if (pa.first != pb.first)
           return pa.first > pb.first;
         else
           return pa.second < pb.second;
       });

  auto it = stats.begin()+lowhash;
  for (int i = 0; i < n && it != stats.end(); ++i) {
    int curr_freq = it->first;
    if (curr_freq == 0)
      break;

    fout << curr_freq << endl;
    int cnt = 0;
    while (it != stats.end() && it->first == curr_freq) {
      ++cnt;
      if (cnt != 1)
        fout << " ";
      fout << rhash(it->second);
      if (cnt == 6) {
        cnt = 0;
        fout << endl;
      }
      ++it;
    }
    if (cnt != 0)
      fout << endl;
  }

  return 0;
}
