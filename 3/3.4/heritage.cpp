/*
  ID: blacksk2
  TASK: heritage
  LANG: C++11
*/
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

struct TreeNode {
  TreeNode *lc;
  TreeNode *rc;
  char val;
};

TreeNode *build_tree(int lo, int hi, const string &inorder, const vector<int> &rank) {
  if (lo > hi)
    return nullptr;

  TreeNode *node = new TreeNode();
  auto vit = std::min_element(inorder.begin()+lo, inorder.begin()+hi+1,
                              [&rank] (char a, char b) {
                                return  rank[a-'A'] < rank[b-'A'];
                              });
  node->val = *vit;
  node->lc = build_tree(lo, vit-inorder.begin()-1, inorder, rank);
  node->rc = build_tree(vit-inorder.begin()+1, hi, inorder, rank);
  return node;
}

void postorder(TreeNode *node, string &output) {
  if (node == nullptr)
    return;
  postorder(node->lc, output);
  postorder(node->rc, output);
  output.push_back(node->val);
}

int main() {
  ifstream fin("heritage.in");
  ofstream fout("heritage.out");

  string inorder, preorder;
  fin >> inorder >> preorder;

  int n = preorder.size();
  vector<int> rank(26);
  for (int i = 0; i < n; ++i)
    rank[preorder[i]-'A'] = i;

  auto root = build_tree(0, n-1, inorder, rank);
  string output;
  postorder(root, output);
  fout << output << endl;

  return 0;
}
