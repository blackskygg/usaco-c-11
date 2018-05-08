/*
  ID: blacksk2
  TASK: zerosum
  LANG: C++11
*/
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

int N;

ifstream fin("zerosum.in");
ofstream fout("zerosum.out");

void print(vector<char> &stack) {
  for (int i = 1; i < stack.size(); ++i)
    fout << stack[i];
  fout << endl;
}

int get_lastn(vector<char> &stack) {
  int i = stack.size()-1, lastn = 0, pow = 1;
  while (isdigit(stack[i]) || stack[i] == ' ') {
    if (stack[i] != ' ') {
      lastn = lastn + (stack[i]-'0')*pow;
      pow *= 10;
    }
    i--;
  }
  if (stack[i] == '-')
    lastn = -lastn;
  return lastn;
}

void calc(int sum, vector<char> &stack, int ndigits) {
  if (isdigit(stack.back())) {
    stack.push_back(' ');
    calc(sum, stack, ndigits);
    sum += get_lastn(stack);
    stack.back() = '+';
    calc(sum, stack, ndigits);
    stack.back() = '-';
    calc(sum, stack, ndigits);
    stack.pop_back();
  } else {
    if (ndigits == N-1) {
      stack.push_back(N+'0');
      if (sum + get_lastn(stack) == 0)
        print(stack);
    } else {
      stack.push_back(ndigits+1+'0');
      calc(sum, stack, ndigits+1);
    }
    stack.pop_back();
  }
}

int main () {
  fin >> N;
  vector<char> stack;
  stack.push_back('+');
  calc(0, stack, 0);

  return 0;
}
