/*
  ID: blacksk2
  TASK: pprime
  LANG: C++11
*/
#include <fstream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

const vector<int> heads = {1, 3, 7, 9};
const vector<int> high_n = {1, 10, 100, 1000, 10000, 100000};

ifstream fin("pprime.in");
ofstream fout("pprime.out");

int low, high;

bool is_prime(int num) {
  if (num & 1 == 0)
    return false;
  for (int i = 3; i*i < num; i+=2) {
    if (num % i == 0)
      return false;
  }
  return true;
}

void gen_pal(int n) {
  int half_n = (n%2 == 0) ? (n/2) : (n/2+1);
  int num, half_num;
  string s(n, '0'), half_s;

  if (n == 1) {
    if (5 >= low && 5 <= high)
          fout << 5 << endl;
    if (7 >= low && 7 <= high)
        fout << 7 << endl;
    return;
  }

  for (auto &h : heads) {
    for (int remain = 0; remain < high_n[half_n-1]; ++remain) {
      half_num = h * high_n[half_n-1] + remain;
      half_s = std::to_string(half_num);
      for (int i = 0; i < half_n; ++i)
        s[i] = half_s[i];
      for (int i = n-1; i >= half_n; --i)
        s[i] = s[n-1-i];
      num = std::stoi(s);
      if (num > high)
        return;
      if (num >= low && is_prime(num))
        fout << num << endl;
    }
  }
}

int main()
{
  int nlow, nhigh;
  fin >> low >> high;
  nlow = std::to_string(low).size();
  nhigh = std::to_string(high).size();

  for (int i = nlow; i <= nhigh; ++i)
    gen_pal(i);

  return 0;
}
