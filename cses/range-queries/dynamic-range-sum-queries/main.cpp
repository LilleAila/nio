#include <iostream>
#include <vector>
using namespace std;

struct SegmentTree {
  int n;
  vector<long long> tree;

  SegmentTree(int n) : n(n), tree(2 * n, 0) {};

  void build(vector<long long> &xs) {
    for (int i = 0; i < n; ++i) {
      tree[i + n] = xs[i];
    }

    for (int i = n - 1; i > 0; --i) {
      tree[i] = tree[i << 1] + tree[(i << 1) | 1];
    }
  }

  void update(int i, long long x) {
    i += n;
    tree[i] = x;
    for (; i > 0; i >>= 1) {
      tree[i >> 1] = tree[i] + tree[i ^ 1];
    }
  }

  long long query(int i, int j) const {
    long long result = 0;
    for (i += n, j += n; i != j; i >>= 1, j >>= 1) {
      if (i & 1)
        result += tree[i++];
      if (j & 1)
        result += tree[--j];
    }
    return result;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q;
  cin >> n >> q;

  vector<long long> xs(n);
  for (int i = 0; i < n; i++) {
    long long x;
    cin >> x;
    xs[i] = x;
  }

  SegmentTree st(n);
  st.build(xs);

  while (q--) {
    int action;
    cin >> action;

    if (action == 1) {
      int k, u;
      cin >> k >> u;
      st.update(k - 1, u);
    } else {
      int a, b;
      cin >> a >> b;
      cout << st.query(a - 1, b) << endl;
    }
  }
}
