/*
  ID: blacksk2
  TASK: sprime
  LANG: C++11
*/
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

const vector<int> trailing = {1, 3, 7, 9};

bool is_prime(int num) {
  if (num & 1 == 0)
    return false;
  for (int i = 3; i*i <= num; i+=2) {
    if (num % i == 0)
      return false;
  }
  return true;
}

int main() {
  ifstream fin("sprime.in");
  ofstream fout("sprime.out");

  int n;
  fin >> n;

  vector<int> prev = {2, 3, 5, 7}, next;
  for (int i = 2; i <= n; ++i) {
    next.clear();
    for (auto &p: prev) {
      int p10 = p * 10;
      for (auto &t: trailing) {
        int num = p10 + t;
        if (is_prime(num))
          next.push_back(num);
      }
    }
    swap(prev, next);
  }

  for (auto &sprime: prev)
    fout << sprime << endl;

  return 0;
}
