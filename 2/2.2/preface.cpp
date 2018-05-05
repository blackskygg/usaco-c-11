/*
  ID: blacksk2
  TASK: preface
  LANG: C++11
*/

#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

static const string letters("IVXLCDM");

void count(int n, vector<int> &cnt) {
  for (int curr_i = letters.size()-1, curr_pow = 1000;
       n > 0;
       curr_i -= 2, curr_pow /= 10)
    {
      if (n < curr_pow)
        continue;

      int pow_cnt = n/curr_pow;
      if (pow_cnt == 9) {
        cnt[letters[curr_i+2]]++;
        cnt[letters[curr_i]]++;
      } else if (pow_cnt >= 4) {
        cnt[letters[curr_i+1]]++;
        cnt[letters[curr_i]] += std::abs(pow_cnt-5);
      } else {
        cnt[letters[curr_i]] += pow_cnt;
      }
      n -= curr_pow*pow_cnt;
    }
}

int main() {
    ifstream fin("preface.in");
    ofstream fout("preface.out");

    int n;
    fin >> n;

    vector<int> cnt(0xff, 0);
    for (int i = 1; i <= n; ++i)
      count(i, cnt);

    string valid_letters(letters);
    for (int i = valid_letters.size()-1; i >= 0; --i) {
      if (cnt[valid_letters[i]])
        break;
      else
        valid_letters.pop_back();
    }
    for (auto c: valid_letters)
      fout << c << " " << cnt[c] << endl;

    return 0;
}

