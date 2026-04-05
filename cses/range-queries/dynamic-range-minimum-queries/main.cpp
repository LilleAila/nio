#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>
using namespace std;

struct SegmentTree {
  int n;
  vector<int> tree;

  SegmentTree(int n) : n(n), tree(2 * n, INT_MAX) {};

  void build(vector<int> &xs) {
    for (int i = 0; i < n; i++) {
      tree[i + n] = xs[i];
    }

    for (int i = n - 1; i > 0; --i) {
      tree[i] = min(tree[i << 1], tree[(i << 1) | 1]);
    }
  }

  void update(int i, int x) {
    for (tree[i += n] = x; i > 1; i >>= 1) {
      tree[i >> 1] = min(tree[i], tree[i ^ 1]);
    }
  }

  int query(int i, int j) const {
    int result = INT_MAX;

    for (i += n, j += n; i < j; i >>= 1, j >>= 1) {
      if (i & 1)
        result = min(result, tree[i++]);
      if (j & 1)
        result = min(result, tree[--j]);
    }

    return result;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q;
  cin >> n >> q;

  vector<int> xs(n);
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    xs[i] = x;
  }

  SegmentTree st(n);
  st.build(xs);

  while (q--) {
    int action, a, b;
    cin >> action >> a >> b;

    if (action == 1) {
      st.update(a - 1, b);
    } else {
      cout << st.query(a - 1, b) << endl;
    }
  }
}
