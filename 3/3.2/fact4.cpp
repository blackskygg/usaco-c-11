/*
  ID: blacksk2
  TASK: fact4
  LANG: C++11
*/
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

int main () {
  ifstream fin("fact4.in");
  ofstream fout("fact4.out");

  int n;
  fin >> n;

  int ntwo = 0, res = 1;
  for (int i = 1; i <= n; ++i) {
    int curr = i;
    while (curr % 2 == 0) {
      curr /= 2;
      ntwo++;
    }
    while (curr % 5 == 0) {
      curr /= 5;
      ntwo--;
    }
    res = res*curr % 10;
  }

  while (ntwo--)
    res = res*2%10;

  fout << res << endl;

  return 0;
}
