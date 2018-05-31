/*
  ID: blacksk2
  TASK: shopping
  LANG: C++11
*/
#include <fstream>
#include <algorithm>
#include <limits>
#include <vector>
#include <iterator>

using namespace std;

#define REP(i, end) for (int i = 0; i <= end; ++i)

struct item {
  int product = 0;
  int count = 0;
};

const int INF  = numeric_limits<int>::max();

int main () {
  ifstream fin("shopping.in");
  ofstream fout("shopping.out");

  int s;
  fin >> s;

  vector<vector<item>> offers(s);
  vector<int> prices(s);
  for (int i = 0; i < s; ++i) {
    int ni;
    fin >> ni;
    offers[i] = vector<item>(ni);
    for (int j = 0; j < ni; ++j)
      fin >> offers[i][j].product >> offers[i][j].count;
    fin >> prices[i];
  }

  int b;
  fin >> b;
  vector<item> wlst(5, item{});
  vector<vector<int>> valid_offers;
  vector<int>  prod2sub(1000, -1), valid_prices;
  for (int i = 0; i < b; ++i) {
    fin >> wlst[i].product >> wlst[i].count;
    prod2sub[wlst[i].product] = i;
    valid_offers.emplace_back(vector<int>(5, 0));
    valid_offers[i][i] = 1;
    valid_prices.push_back(int{});
    fin >> valid_prices.back();
  }


  for (int oi = 0; oi < offers.size(); ++oi) {
    auto &o = offers[oi];

    vector<int> newoffer(5, 0);
    bool flag = true;
    for (int i = 0; i < o.size(); ++i) {
      int sub = prod2sub[o[i].product];
      if (sub == -1) {
        flag = false;
        break;
      }
      newoffer[sub] = o[i].count;
    }
    if (flag) {
      valid_offers.emplace_back(std::move(newoffer));
      valid_prices.push_back(prices[oi]);
    }
  }


  int dp[6][6][6][6][6];
  dp[0][0][0][0][0] = 0;

  REP(i, wlst[0].count) {
    REP(j, wlst[1].count) {
      REP(k, wlst[2].count) {
        REP(l, wlst[3].count) {
          REP(m, wlst[4].count) {
            if (i == 0 && j == 0 && k == 0 && l == 0 && m == 0)
              continue;
            int best_curr = INF;
            for (int o = 0; o < valid_offers.size(); ++o) {
              auto &vo = valid_offers[o];
              int t;
              if (i-vo[0] >= 0 && j-vo[1] >= 0
                  && k-vo[2] >= 0 && l-vo[3] >= 0 && m-vo[4] >= 0
                  && dp[i-vo[0]][j-vo[1]][k-vo[2]][l-vo[3]][m-vo[4]] != INF)
                t = dp[i-vo[0]][j-vo[1]][k-vo[2]][l-vo[3]][m-vo[4]]+valid_prices[o];
              else
                t = INF;
              best_curr =std::min(t, best_curr);
            }
            dp[i][j][k][l][m] = best_curr;
          }
        }
      }
    }
  }

  fout << dp[wlst[0].count][wlst[1].count][wlst[2].count]
    [wlst[3].count][wlst[4].count] << endl;


  return 0;
}
