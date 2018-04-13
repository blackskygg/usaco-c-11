/*
ID: blacksk2
TASK: beads
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  ifstream fin("beads.in");
  ofstream fout("beads.out");

  int len;
  string beads;

  fin >> len >> beads;
  beads += beads;

  vector<int> color, span;
  for (int i = 0, j = 1; i < 2 * len; i = j, j = i+1) {
    while (j < 2*len && beads[j] == beads[i])
      j++;
    color.push_back(beads[i]);
    span.push_back(j-i);
  }

  int prev_len = 0, max_len = 0;
  for (int i = 0, j = 1; i < span.size(); i = j, j = i+1) {
    int curr_cl = color[i], curr_len = span[i];

    while (j < span.size() && (color[j] == curr_cl || color[j] == 'w' || curr_cl == 'w')) {
      curr_len += span[j];
      if (curr_cl == 'w' && color[j] != 'w')
        curr_cl = color[j];
      j++;
    }

    max_len = std::max(max_len, curr_len + prev_len);
    prev_len = curr_len;
    if (i != 0 && color[i-1] == 'w')
      prev_len += span[i-1];
  }

  fout << (max_len > len ? len : max_len) << endl;

  return 0;
}
