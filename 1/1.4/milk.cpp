/*
ID: blacksk2
TASK: milk
LANG: C++11
*/
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;
using farmer = std::pair<int, int>;

int main() {
  ifstream fin("milk.in");
  ofstream fout("milk.out");

  int n, m, price, unit;
  vector<farmer> farmers;

  fin >> n >> m;
  while (m--) {
    fin >> price >> unit;
    farmers.emplace_back(price, unit);
  }
  sort(farmers.begin(), farmers.end());

  int cnt = 0, fm_idx = 0, total_money = 0;
  while (n) {
    auto &curr_fm = farmers[fm_idx++];
    if (n >= curr_fm.second) {
      total_money += curr_fm.first * curr_fm.second;
      n -= curr_fm.second;
    } else {
      total_money += curr_fm.first * n;
      n -= n;
    }
  }

  fout << total_money << endl;

  return 0;
}
