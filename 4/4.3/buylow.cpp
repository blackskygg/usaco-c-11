/*
  ID: blacksk2
  TASK: buylow
  LANG: C++11
*/
#include <algorithm>
#include <fstream>
#include <limits>
#include <unordered_set>
#include <vector>

class BigNum {
public:
  BigNum(int n = 0) {
    while (n) {
      arr_.push_back(n % 10);
      n /= 10;
    }
  }
  BigNum(const BigNum &bn) : arr_(bn.arr_) {}

  std::string ToString() const {
    if (arr_.empty()) {
      return "0";
    }
    std::string res;
    for (auto it = arr_.rbegin(); it != arr_.rend(); ++it) {
      res.push_back(*it + '0');
    }
    return res;
  }

  BigNum operator+(const BigNum &bn) const {
    BigNum result;
    const std::vector<uint8_t> *va = &arr_, *vb = &bn.arr_;
    if (va->size() < vb->size()) {
      std::swap(va, vb);
    }

    auto &res_vec = result.arr_;
    uint8_t carry = 0;
    for (int i = 0; i < va->size(); ++i) {
      uint8_t a = va->at(i), b = i < vb->size() ? vb->at(i) : 0;
      uint8_t sum = a + b + carry;
      carry = 0;
      if (sum > 9) {
        sum -= 10;
        carry = 1;
      }
      res_vec.push_back(sum);
    }
    if (carry) {
      res_vec.push_back(1);
    }

    return result.Normalize();
  }

private:
  BigNum &Normalize() {
    while (!arr_.empty() && arr_.back() == 0) {
      arr_.pop_back();
    }
    return *this;
  }

private:
  std::vector<uint8_t> arr_;
};

int main() {
  std::ifstream fin("buylow.in");
  std::ofstream fout("buylow.out");

  int n;
  fin >> n;

  std::vector<unsigned int> prices(n);
  for (auto &p : prices) {
    fin >> p;
  }

  std::vector<int> len(n, 0);
  std::vector<BigNum> num(n, BigNum(1));
  for (int i = 0; i < n; ++i) {
    len[i] = 0;
    std::unordered_set<int> max_set;

    for (int j = i - 1; j >= 0; --j) {
      if (prices[j] <= prices[i] || max_set.count(prices[j]) ||
          len[j] < len[i]) {
        continue;
      }
      if (len[j] > len[i]) {
        max_set.clear();
        num[i] = num[j];
        len[i] = len[j];
      } else {
        num[i] = num[i] + num[j];
      }
      max_set.insert(prices[j]);
    }
    len[i]++;
  }

  BigNum max_num;
  int max_len = 0;
  std::unordered_set<int> max_set;
  for (int i = n - 1; i >= 0; --i) {
    if (len[i] < max_len || max_set.count(prices[i])) {
      continue;
    }
    if (len[i] > max_len) {
      max_len = len[i];
      max_set.clear();
      max_num = num[i];
    } else {
      max_num = max_num + num[i];
    }
    max_set.insert(prices[i]);
  }

  fout << max_len << " " << max_num.ToString() << std::endl;

  return 0;
}
