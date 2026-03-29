#include <iostream>
#include <vector>
using namespace std;

struct FenwickTree {
  vector<int> bit;
  int n;

  FenwickTree(int n) : bit(n + 1, 0), n(n) {}

  void update(int i, int d) {
    for (; i <= n; i += i & -i)
      bit[i] += d;
  }

  int query(int i) const {
    int result = 0;
    for (; i > 0; i -= i & -i) {
      result += bit[i];
    }
    return result;
  }

  int query(int l, int r) const { return query(r) - query(l - 1); }
};

struct SegmentTreeRecursive {
  vector<int> tree;
  int n;

  SegmentTreeRecursive(int n) : tree(n * 4, 0), n(n) {}

  void build(const vector<int> &xs, int node, int l, int r) {
    if (l == r) {
      tree[node] = xs[l];
      return;
    }

    int mid = (l + r) / 2;
    build(xs, node * 2, l, mid);
    build(xs, node * 2 + 1, mid + 1, r);
    tree[node] = tree[2 * node] + tree[2 * node + 1];
  }

  void build(const vector<int> &xs) { build(xs, 1, 0, n - 1); }

  void update(int node, int l, int r, int i, int x) {
    if (l == r) {
      tree[node] = x;
      return;
    }

    int mid = (l + r) / 2;
    if (i <= mid)
      update(node * 2, l, mid, i, x);
    else
      update(node * 2 + 1, mid + 1, r, i, x);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
  }

  void update(int i, int x) { update(1, 0, n - 1, i, x); }

  int query(int node, int a, int b, int l, int r) const {
    if (r < a || b < l)
      return 0;
    if (l <= a && b <= r)
      return tree[node];

    int mid = (a + b) / 2;
    int p1 = query(2 * node, a, mid, l, r);
    int p2 = query(2 * node + 1, mid + 1, b, l, r);
    return p1 + p2;
  }

  int query(int l, int r) const { return query(1, 0, n - 1, l, r); }

  int query(int i) const { return query(i, i); }
};

struct SegmentTree {
  int n;
  vector<int> tree;

  SegmentTree(int n) : n(n), tree(2 * n, 0) {}

  void build(const vector<int> &xs) {
    for (int i = 0; i < n; i++) {
      tree[i + n] = xs[i];
    }

    for (int i = n - 1; i > 0; i--) {
      tree[i] = tree[i << 1] + tree[i << 1 | 1];
    }
  }

  void update(int i, int x) {
    for (tree[i += n] = x; i > 1; i /= 2) {
      tree[i >> 1] = tree[i] + tree[i ^ 1];
    }
  }

  int query(int l, int r) const {
    int acc = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1)
        acc += tree[l++];
      if (r & 1)
        acc += tree[--r];
    }
    return acc;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  vector<int> xs = {1, 4, 2, 5, 3};
  int n = xs.size();

  // NOTE: the fenwick tree is 1-indexed
  cout << "Fenwick Tree:" << endl;
  FenwickTree fw(n);
  for (int i = 0; i < n; i++) {
    fw.update(i + 1, xs[i]);
  }
  cout << fw.query(1) << endl;
  cout << fw.query(5) << endl;
  cout << fw.query(3, 5) << endl;
  cout << fw.query(2, 4) << endl;

  // NOTE: the segment tree is 0-indexed and uses closed intervals
  cout << "Segment Tree (recursive):" << endl;
  SegmentTreeRecursive st(n);
  st.build(xs);
  cout << st.query(0) << endl;
  cout << st.query(0, 4) << endl;
  cout << st.query(2, 4) << endl;
  cout << st.query(1, 3) << endl;

  // NOTE: this segment tree is 0-intexed and uses half-open intervals [l, r)
  cout << "Segment Tree (iterative):" << endl;
  SegmentTree st2(n);
  st2.build(xs);
  cout << "[ ";
  for (const auto &x : st2.tree)
    cout << x << " ";
  cout << "]" << endl;
  cout << st2.query(0, 1) << endl;
  cout << st2.query(0, 5) << endl;
  cout << st2.query(2, 5) << endl;
  cout << st2.query(1, 4) << endl;
}
