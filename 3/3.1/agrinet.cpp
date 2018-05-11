/*
  ID: blacksk2
  TASK: agrinet
  LANG: C++11
*/
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

const int INF = 1000000000;

int main () {
  ifstream fin("agrinet.in");
  ofstream fout("agrinet.out");

  int N;
  fin >> N;

  vector<vector<int>> adj(N, vector<int>(N, INF));
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j)
      fin >> adj[i][j];

  int total = 0;
  vector<int> intree(N, false), d(N, INF), p(N);
  d[0] = 0;
  p[0] = 0;
  for (int i = 0; i < N; ++i) {
    int curr = std::min_element(d.begin(), d.end())-d.begin();
    intree[curr] = true;
    d[curr] = INF;
    total += adj[p[curr]][curr];
    for (int j = 0; j < N; ++j) {
      if (!intree[j] && adj[curr][j] < d[j]) {
        p[j] = curr;
        d[j] = adj[curr][j];
      }
    }
  }

  fout << total << endl;

  return 0;
}
