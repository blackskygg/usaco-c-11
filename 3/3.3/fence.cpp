/*
  ID: blacksk2
  TASK: fence
  LANG: C++11
*/
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

void euler_circuit(int curr, vector<vector<int>> &adj, vector<int> &circuit) {
  for (int i = 0; i < 500; ++i) {
    if (adj[curr][i]) {
      adj[curr][i]--;
      adj[i][curr]--;
      euler_circuit(i, adj, circuit);
    }
  }
  circuit.push_back(curr);
}

int main () {
  ifstream fin("fence.in");
  ofstream fout("fence.out");

  int f;
  fin >> f;

  vector<vector<int>> adj(500, vector<int>(500 , 0));
  vector<int> degree(500, 0);
  for (int i = 0; i < f; ++i) {
    int s, e;
    fin >> s >> e;
    s--;
    e--;
    adj[s][e]++;
    adj[e][s]++;
    degree[s]++;
    degree[e]++;
  }

  vector<int> circuit;
  int even_start = -1, odd_start = -1;
  for (int i  = 0; i < 500; ++i) {
    if (degree[i] == 0)
      continue;
    if (even_start == -1 && degree[i]%2 == 0)
      even_start = i;
    else if (odd_start == -1 && degree[i]%2 != 0)
      odd_start = i;
  }

  if (odd_start != -1)
    euler_circuit(odd_start, adj, circuit);
  else if (even_start != -1)
    euler_circuit(even_start, adj, circuit);

  for (auto it = circuit.rbegin(); it != circuit.rend(); ++it)
    fout << *it+1 << endl;

  return 0;
}
