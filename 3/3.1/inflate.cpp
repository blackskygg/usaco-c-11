/*
  ID: blacksk2
  TASK: inflate
  LANG: C++11
*/
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

int main () {
  ifstream fin("inflate.in");
  ofstream fout("inflate.out");

  int M, N;
  fin >> M >> N;

  vector<pair<int, int>> categories(N);
  for (int i = 0; i < N; ++i)
    fin >> categories[i].second >> categories[i].first;
  sort(categories.begin(), categories.end());

  {
  vector<pair<int, int>> temp_categories;
  temp_categories.reserve(N);
  int curr_point = 0;
  for (int i = 0; i < N; ++i) {
    if (categories[i].second > curr_point) {
      curr_point = categories[i].second;
      temp_categories.push_back(categories[i]);
    }
  }
  swap(temp_categories, categories);
  }

  int len = categories.size();
  vector<int> dp(M+1, 0);
  for (int i = 0; i < len; ++i) {
    for (int t = categories[i].first; t <= M; ++t) {
      dp[t] = max(dp[t-categories[i].first]+categories[i].second, dp[t]);
    }
  }

  fout << *max_element(dp.begin(), dp.end()) << endl;

  return 0;
}
