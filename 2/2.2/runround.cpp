/*
  ID: blacksk2
  TASK: runround
  LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <unordered_set>

using namespace std;

bool is_runround(const string &s) {
    std::vector<bool> used(s.size(),false);
    for (int i = 0, pos = 0, val = s[0]-'0'; i < s.size(); i++) {
        pos = (pos + val) % s.size();
        val = s[pos]-'0';
        if (used[pos] == true)
            return false;
        used[pos] = true;
    }
    return true;
}

void fill_smallest(string &s, const vector<int> &used, int n) {
    for (int i = 0, j = 0; i < n; ++i, ++j) {
        while (used[j])
            j++;
        s.push_back(j+'0');
    }
}

void get_next_perm(string &s) {
    vector<int> visited(10, 0);
    for (auto c: s)
        visited[c-'0']++;

    for (int i = s.size()-1; i >= 0; --i) {
        visited[s[i]-'0']--;
        for (int j = s[i]-'0'+1; j < 10; ++j) {
            if (visited[j])
                continue;

            s[i] = j+'0';
            visited[j]++;
            string ns = s.substr(0, i+1);
            fill_smallest(ns, visited, s.size()-(i+1));
            s = ns;
            return;
        }
    }

    string ns;
    for (int i = 0; i < s.size()+1; ++i)
        ns.push_back(i+1+'0');
    s = ns;
    return;
}

void round_to_good(string &s) {
    vector<int> idx(10, 0);
    for (int i = 0; i < s.size(); ++i) {
        if (!idx[s[i]-'0']) {
            idx[s[i]-'0']++;
            continue;
        }

        string half_s = s.substr(0, i+1);
        get_next_perm(half_s);
        idx.assign(10, 0);
        for (auto c: half_s)
            idx[c-'0']++;
        fill_smallest(half_s, idx, s.size()-(i+1));
        s = half_s;
        return;
    }
}

int main()
{
    ifstream fin("runround.in");
    ofstream fout("runround.out");

    unsigned long m;
    fin >> m;
    string ms = to_string(m);

    round_to_good(ms);
    if (ms == to_string(m))
        get_next_perm(ms);
    while (!is_runround(ms))
        get_next_perm(ms);

    fout << ms << endl;

    return 0;
}