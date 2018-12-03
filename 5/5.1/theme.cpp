/*
  ID: blacksk2
  TASK: theme
  LANG: C++11
*/

#include <algorithm>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

static int n;
static std::string notes;

void read_input(std::ifstream &fin) {
  fin >> n;
  notes.resize(n);
  for (char &c : notes) {
    int i;
    fin >> i;
    c = i;
  }
}

std::string normalize(std::string s) {
  int base = *std::min_element(s.begin(), s.end());
  for (char &c : s) {
    c -= base;
  }
  return s;
}

bool check(int k) {
  std::unordered_map<std::string, std::vector<int>> pieces;
  for (int i = 0; i < n; ++i) {
    if (i < k && i + k >= n) {
      continue;
    }
    std::string piece = normalize(notes.substr(i, k));
    if (!pieces.count(piece)) {
      pieces[piece] = std::vector<int>{i, i};
    }
    auto &p = pieces[piece];
    p[0] = std::min(p[0], i);
    p[1] = std::max(p[1], i);
  }
  for (const auto &kv : pieces) {
    if (kv.second[1] - kv.second[0] >= k) {
      return true;
    }
  }
  return false;
}

int search() {
  int lo = 5, hi = n / 2 + 1;
  while (lo < hi) {
    int m = lo + (hi - lo) / 2;
    if (check(m)) {
      lo = m + 1;
    } else {
      hi = m;
    }
  }
  return lo - 1;
}

int main() {
  std::ifstream fin("theme.in");
  std::ofstream fout("theme.out");

  read_input(fin);
  int ans = search();
  fout << ((ans < 5) ? 0 : ans) << std::endl;

  return 0;
}
