// YOUR SOLUTION GOES HERE -- YOU DON'T NEED TO ERASE THE REST
// -----------------------------------------------------------
// MAKE SURE THAT YOUR SUBMISSION COMPILES, OTHERWISE YOU WILL
// GET ZERO POINTS TODAY AND THAT WILL BE A PITY!
// ------------------------(snip)-----------------------------

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Tree {
public:
  Tree() : root(nullptr) {}
  ~Tree() { delete root; }

  void insert(int v);
  vector<int> lsum();

private:
  struct node {
    node(int d, node *l, node *r) : data(d), left(l), right(r) {}
    ~node() { delete left; delete right; }

    int data;
    node *left, *right;
  };

  static node *insert(node *t, int v);
  node *root;
  void lsum_aux(node *t,int level, vector<int> &v){
    if(t == nullptr) return;
    if(t != nullptr) v[level] += t->data;
    lsum_aux(t->left, level+1, v);
    lsum_aux(t->right, level+1, v);
  }
  int getHeight(node* root)
  {
    if (root->left == NULL && root->right == NULL)
        return 0;
    if(root->left == NULL)
        return getHeight(root->right) + 1;
    if(root->right == NULL)
        return getHeight(root->left) + 1;
    return max(getHeight(root->left), getHeight(root->right)) + 1;
  }
};

vector<int> Tree::lsum() {
  vector<int> result(getHeight(root)+1, 0);
  lsum_aux(root, 0, result);
  return result;
}


// YOU DON'T NEED TO CHANGE THE REST. IF YOU DO, YOU'D BETTER
// KNOW WHAT YOU'RE DOING...

void Tree::insert(int v) { root = insert(root, v); }

Tree::node *Tree::insert(node *t, int v) {
  if (t == nullptr)
    return new node(v, nullptr, nullptr);
  if (v < t->data)
    t->left = insert(t->left, v);
  else
    t->right = insert(t->right, v);
  return t;
}

// ------------------------(snip)-----------------------------
// YOUR SOLUTION ENDS HERE -- YOU DON'T NEED TO ERASE THE REST

#ifndef CONTEST

int main() {
  Tree t;
  int values[] = {42, 17, 57, 12, 34, 89, 16, 38, 5};
  for (int v : values) t.insert(v);
  cout << "t =     42" << endl;
  cout << "       /  \\" << endl;
  cout << "     17    57" << endl;
  cout << "    /  \\    \\" << endl;
  cout << "  12    34   89" << endl;
  cout << " /  \\    \\" << endl;
  cout << "5    16   38" << endl;
  cout << endl;
  vector<int> sums = t.lsum();
  for (int i = 0; i < sums.size(); ++i)
    cout << "Level " << i << " has sum " << sums[i] << endl;
}

#endif
