/*
  ID: blacksk2
  TASK: humble
  LANG: C++11
*/
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

int main () {
  ifstream fin("humble.in");
  ofstream fout("humble.out");

  int k, n;
  fin >> k >> n;

  vector<int> primes(k);
  for (int i = 0; i < n; ++i)
    fin >> primes[i];
  sort(primes.begin(), primes.end());

  vector<int> humbles;
  humbles.reserve(n+1);
  humbles.push_back(1);
  humbles.push_back(primes[0]);
  for (int i = 1; i < n; ++i) {
    int candidate = (1U<<31)-1;
    auto it = humbles.end();
    for (int j = 0; j < k; ++j) {
      int curr_prime = primes[j];
      it = std::upper_bound(humbles.begin(), it, humbles.back()/curr_prime);
      candidate = std::min(*it*curr_prime, candidate);
    }
    humbles.push_back(candidate);
  }

  fout << humbles[n] << endl;

  return 0;
}
