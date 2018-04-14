/*
ID: blacksk2
TASK: milk2
LANG: C++11
*/
#include <fstream>
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;
using event = std::pair<int, int>;

int main()
{
  ifstream fin("milk2.in");
  ofstream fout("milk2.out");

  int n;
  vector<event> events;
  int t;

  fin >> n;
  for (int i = 0; i < n; ++i) {
    fin >> t;
    events.emplace_back(t, 0);
    fin >> t;
    events.emplace_back(t, 1);
  }
  sort(events.begin(), events.end());

  int ocp_start = -1, max_ocp = 0, empty_start = -1, max_empty = 0, curr_cnt = 0;

  for (auto const &ev : events) {
    if (ev.second == 0) {
      if (++curr_cnt == 1) {
        ocp_start = ev.first;
        if (empty_start != -1)
          max_empty = std::max(max_empty, ev.first - empty_start);
      }
    } else {
      if (--curr_cnt == 0) {
        empty_start = ev.first;
        max_ocp = std::max(max_ocp, ev.first - ocp_start);
      }
    }
  }

  fout << max_ocp << " " << max_empty << endl;

  return 0;
}
