/*
ID: blacksk2
TASK: ride
LANG: C++11
*/

#include <fstream>

using namespace std;

int main()
{
  ifstream fin("ride.in");
  ofstream fout("ride.out");
  string comet, group;
  int comet_sc = 1, group_sc = 1;

  fin >> comet >> group;
  for (auto c: comet)
    comet_sc *= c-'A'+1;
  for (auto c: group)
    group_sc *= c-'A'+1;

  if (comet_sc % 47 == group_sc % 47)
    fout << "GO" << endl;
  else
    fout << "STAY" << endl;

  return 0;
}
