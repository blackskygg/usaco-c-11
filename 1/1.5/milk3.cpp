/*
ID: blacksk2
TASK: milk3
LANG: C++11
*/
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int visited[32][32][32], reachable[32];
vector<int> ans;
int ca, cb, cc;

void dfs(int na, int nb, int nc) {
  if (visited[na][nb][nc])
    return;

  visited[na][nb][nc] = 1;
  if (na == 0 && !reachable[nc]) {
    reachable[nc] = 1;
    ans.push_back(nc);
  }

  if (na > 0) {
    if (cb-nb > 0) {
      if (cb-nb > na)
        dfs(0, nb+na, nc);
      else
        dfs(na-(cb-nb), cb, nc);
    }
    if (cc-nc > 0) {
      if (cc-nc > na)
        dfs(0, nb, nc+na);
      else
        dfs(na-(cc-nc), nb, cc);
    }
  }

  if (nb > 0) {
    if (ca-na > 0) {
      if (ca-na > nb)
        dfs(na+nb, 0, nc);
      else
        dfs(ca, nb-(ca-na), nc);
    }
    if (cc-nc > 0) {
      if (cc-nc > nb)
        dfs(na, 0, nc+nb);
      else
        dfs(na, nb-(cc-nc), nc+nb);
    }
  }

  if (nc > 0) {
    if (cb-nb > 0) {
      if (cb-nb > nc)
        dfs(na, nb+nc, 0);
      else
        dfs(na, cb, nc-(cb-nb));
    }
    if (ca-na > 0) {
      if (ca-na > nc)
        dfs(na+nc, nb, 0);
      else
        dfs(ca, nb, nc-(ca-na));
    }
  }
}

int main()
{
  ifstream fin("milk3.in");
  ofstream fout("milk3.out");

  fin >> ca >> cb >> cc;

  dfs(0, 0, cc);

  sort(ans.begin(), ans.end());
  fout << ans.front();
  for (int i = 1; i < ans.size(); ++i)
    fout << " " << ans[i];
  fout << endl;

  return 0;
}
