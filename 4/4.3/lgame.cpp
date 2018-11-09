/*
  ID: blacksk2
  TASK: lgame
  LANG: C++11
*/
#include <algorithm>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

std::unordered_map<std::string, int> build_dict(std::ifstream &fdict) {
  static std::unordered_map<char, int> c2s = [] {
    std::unordered_map<char, int> c2s;
    static const char letters[] = "qwertyuiopasdfghjklzxcvbnm";
    static const int scores[] = {7, 6, 1, 2, 2, 5, 4, 1, 3, 5, 2, 1, 4,
                                 6, 5, 5, 7, 6, 3, 7, 7, 4, 6, 5, 2, 5};
    for (int i = 0; i < 26; ++i) {
      c2s[letters[i]] = scores[i];
    }
    return c2s;
  }();

  std::unordered_map<std::string, int> dict;
  std::string word;
  while (fdict >> word) {
    if (word[0] == '.') {
      break;
    }
    int score = 0;
    for (auto c : word) {
      score += c2s[c];
    }
    dict[word] = score;
  }
  dict[""] = 0;
  return dict;
}

void find_max(const std::unordered_map<std::string, int> &dict,
              std::vector<int> &letters, std::string &curr, int &max_score,
              std::unordered_set<std::string> &results) {
  for (int i = 0; i < 26; ++i) {
    if (letters[i] == 0) {
      continue;
    }
    letters[i]--;
    curr.push_back(i + 'a');

    find_max(dict, letters, curr, max_score, results);

    curr.pop_back();
    letters[i]++;
  }

  for (int i = 0; i < curr.size(); ++i) {
    std::vector<std::string> words = {curr.substr(0, i), curr.substr(i)};
    if (words[0] > words[1] || words[0].empty()) {
      std::swap(words[0], words[1]);
    }
    if (!dict.count(words[0]) || !dict.count(words[1])) {
      continue;
    }
    int score = dict.at(words[0]) + dict.at(words[1]);
    if (score > max_score) {
      max_score = score;
      results.clear();
      results.insert(words[0] + '#' + words[1]);
    } else if (score == max_score) {
      results.insert(words[0] + '#' + words[1]);
    }
  }
}

void output_results(int max_score,
                    const std::unordered_set<std::string> &results,
                    std::ofstream &fout) {
  std::vector<std::vector<std::string>> outputs;
  for (const auto &result : results) {
    int split = result.find('#');
    outputs.emplace_back(std::vector<std::string>{result.substr(0, split),
                                                  result.substr(split + 1)});
  }
  std::sort(outputs.begin(), outputs.end(),
            [](const std::vector<std::string> &va,
               const std::vector<std::string> &vb) {
              if (va[0] != vb[0]) {
                return va[0] < vb[0];
              } else {
                return va[1] < vb[1];
              }
            });
  fout << max_score << std::endl;
  for (const auto &vec : outputs) {
    fout << vec[0];
    if (!vec[1].empty()) {
      fout << " " << vec[1];
    }
    fout << std::endl;
  }
}

int main() {
  std::ifstream fin("lgame.in"), fdict("lgame.dict");
  std::ofstream fout("lgame.out");

  std::string input;
  fin >> input;

  std::vector<int> letters(26, 0);
  for (const char c : input) {
    letters[c - 'a']++;
  }

  std::unordered_set<std::string> results; // word1#word2
  int max_score = 0;
  auto dict = build_dict(fdict);
  std::string curr;

  find_max(dict, letters, curr, max_score, results);

  output_results(max_score, results, fout);

  return 0;
}