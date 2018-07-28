/*
  ID: blacksk2
  TASK: fence9
  LANG: C++11
*/
#include <fstream>
#include <algorithm>
#include <vector>
#include <cstdlib>

using namespace std;

int main() {
  ifstream fin("fence9.in");
  ofstream fout("fence9.out");

  long n, m, p;
  fin >> n >> m >> p;

  long total = 0;
  long k1 = n, k2 = (n-p);
  for (int y = 1; y < m; ++y) {
    long x1 = y*k1, x2 = p*m+y*k2;
    if (x1 % m == 0)
      x1 += m;
    else
      x1 = (x1/m+1)*m;

    if (x2 % m == 0)
      x2 -= m;
    else
      x2 = (x2/m)*m;

    total += (x2-x1)/m+1;
  }

  fout << total << endl;
  return 0;
}
