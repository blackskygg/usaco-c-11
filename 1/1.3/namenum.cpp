/*
ID: blacksk2
TASK: namenum
LANG: C++11
*/
#include <fstream>
#include <vector>

using namespace std;

int main() {
  ifstream fin("namenum.in"), fdict("dict.txt");
  ofstream fout("namenum.out");

  string num, name;
  const vector<int> al2num = {2,2,2,3,3,3,4,4,4,5,5,5,
                              6,6,6,7,0,7,7,8,8,8,9,9,9};
  bool has_ans = false;

  fin >> num;
  while (fdict >> name) {
    if (name.size() != num.size())
      continue;

    bool flag = true;
    for (int i = 0; i < name.size(); ++i) {
      if (num[i] != al2num[name[i]-'A']+'0') {
        flag = false;
        break;
      }
    }

    if (flag) {
      fout << name << endl;
      has_ans = true;
    }
  }

  if (!has_ans)
    fout << "NONE" << endl;

  return 0;
}
