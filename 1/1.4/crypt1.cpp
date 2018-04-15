/*
ID: blacksk2
TASK: crypt1
LANG: C++11
*/
#include <fstream>
#include <vector>
#include <unordered_set>
#include <string>
#include <algorithm>

using namespace std;

static vector<int> nums;
static unordered_set<int> numset;

bool check_ans(const string &numa, const string &numb) {
  int a = stoi(numa), pb[] = {a*(numb[0]-'0'), a*(numb[1]-'0')},
    sum = pb[0]*10 + pb[1];
  auto is_valid = [] (const string &s) {
    for (auto &c: s) {
      if (!numset.count(c-'0'))
        return false;
    }
    return true;
  };

  for (int i = 0; i < 2; ++i) {
    if (pb[i] >= 1000 || pb[i] < 100)
      return false;
    if (!is_valid(to_string(pb[i])))
      return false;
  }

  if (sum >= 10000 || sum < 1000)
    return false;
  if (!is_valid(to_string(sum)))
    return false;

  return true;
}

int count_solutions(string &numa, string &numb, int level) {
  if (level == 5)
    return check_ans(numa, numb) ? 1 : 0;

  int cnt = 0;

  for (auto &i: nums) {
    if (level < 3)
      numa.push_back(i+'0');
    else
      numb.push_back(i+'0');

    cnt += count_solutions(numa, numb, level+1);

    if (level < 3)
      numa.pop_back();
    else
      numb.pop_back();
  }

  return cnt;
}

int main() {
  ifstream fin("crypt1.in");
  ofstream fout("crypt1.out");

  int n, t;

  fin >> n;
  while (n--) {
    fin >> t;
    nums.push_back(t);
    numset.insert(t);
  }
  sort(nums.begin(), nums.end());

  string numa, numb;
  fout << count_solutions(numa, numb, 0) << endl;

  return 0;
}
